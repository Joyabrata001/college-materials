#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>   //ftok
#include <sys/shm.h>   //shmget, shmat, shmdt, shmctl
#include <stdlib.h>    // exit
#include <signal.h>    //signal
#include <sys/types.h> //open, lseek
#include <sys/stat.h>  //open
#include <fcntl.h>     //open
#include <unistd.h>    //lseek, write, close, read
#include <stdbool.h>   //for true and false

#define SHM_FILE_PATH "./q1.c"
#define SHM_PROJ_ID 1

#define NUM_FILES 5
#define FILE_UNINITIALIZED_FILE_NAME ""
#define FILE_UNINITIALIZED_BLOCK_SIZE -1
#define FILE_UNINITIALIZED_NUM_BLOCK -1

#define DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM 50

// #define DEFAULT_BLOCK_SIZE 4096
// #define DEFAULT_NUM_BLOCKS 1024

typedef void (*sighandler_t)(int);

int shmid; // will be set up by initProgram and will be used by vareiety of functions
// The functions that will use the shmid
// 1) initProgram()
// 2) closeProgram()
// 3) init_file_dd()
// 4) read_block_dd()
// 5) write_block_dd()
// 6) del_file_dd()

typedef struct FileInsideFile
{
    char name[50];
    int page_taken;
} FileInsideFile;

typedef struct FileInfo
{
    char filename[50];
    int blockSize;
    int numBlock;
    FileInsideFile files[DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM];
    bool taken[50];

} FileInfo;

// does shmat and error checking
void *shared_memory_attach(const int given_shm_id)
{
    void *returnVal = shmat(given_shm_id, NULL, 0);
    if (returnVal == (void *)-1)
    {
        perror("shmat fail");
        kill(0, SIGINT); // 0 here means process group
    }
    return returnVal;
}

// calls shmdt with error checking, will always return NULL to make the given pointer null
// use as follows
// abc = shared_memory_detach(abc)
// this will detach the shared memory and will also set the pointer as null to avoid any dangling pointer
void *shared_memory_detach(const void *shared_mem_addr)
{
    if (shmdt(shared_mem_addr) == -1)
    {
        perror("shmdt fail");
        kill(0, SIGINT);
    }
    return NULL;
}

// should be called at the first for making a shared memory
void initProgram()
{
    key_t fkey = ftok(SHM_FILE_PATH, SHM_PROJ_ID);
    shmid = shmget(fkey, sizeof(FileInfo) * NUM_FILES, IPC_CREAT | 0777); // set up permission for all users
    // TODO: add support for the situation where shared memory is already present

    if (shmid == -1)
    {
        // printf("%d\n", )
        perror("shmget fail");
        exit(EXIT_FAILURE);
    }

    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    for (int i = 0; i < NUM_FILES; i++) // setting defualt values for all the elements
    {
        strcpy(fileInfoArr[i].filename, FILE_UNINITIALIZED_FILE_NAME);
        fileInfoArr[i].blockSize = FILE_UNINITIALIZED_BLOCK_SIZE;
        fileInfoArr[i].numBlock = FILE_UNINITIALIZED_NUM_BLOCK;
    }
    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr); // will return NULL always
}

// should be attached to a signal handler and should be called at the end of main to remove the shared memory
void closeProgram(int signum)
{
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
        perror("shmctl fail");

    exit(signum);
}

// makes a file with given filename and given size
void makeFile(const char *filename, int size)
{
    int fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0777);
    if (fd == -1) // create file
    {
        perror("open fail");
        kill(0, SIGINT);
    }

    off_t offset = lseek(fd, size, SEEK_SET); // seek to the size bytes, size not increased yet
    if (offset == (off_t)-1)
    {
        perror("lseek fail");
        kill(0, SIGINT);
    }

    const char *data = "\0";
    ssize_t writeSize = write(fd, &data, strlen(data)); // now the size is increased

    if (writeSize == -1)
    {
        perror("write fail");
        kill(0, SIGINT);
    }

    // file with given size created, now close the file
    if (close(fd) == -1)
    {
        perror("close fail");
        kill(0, SIGINT);
    }
}

// makes a file with a given name, with bno blocks each of size bsize and returns ddid of the file created, else return -1
int init_file_dd(const char *fname, int bsize, int bno)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    // search for any existing file
    for (int ddid = 0; ddid < NUM_FILES; ddid++)
        if (strcmp(fileInfoArr[ddid].filename, fname) == 0)
            return ddid;

    // now we know that file is not present, so we make it and add it to the FileInfo arrat (if place is present)
    // first we check if any place is empty or not
    int new_ddid = -1;

    for (int i = 0; i < NUM_FILES; i++)
    {
        if (fileInfoArr[i].blockSize == FILE_UNINITIALIZED_BLOCK_SIZE)
        {
            new_ddid = i;
            break;
        }
    }

    if (new_ddid == -1)
    {
        fprintf(stderr, "Error: file limit reached, please increse NUM_FILES in the code.\n");
        return -1;
    }

    if (bno > DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM)
    {
        fprintf(stderr, "error: num blocks too big, make DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM bigger");
        return -1;
    }

    // now we have a uninitialized place in the shared memory, now we will make a file and add its porperty in the shared memory array
    makeFile(fname, bsize * bno);
    strcpy(fileInfoArr[new_ddid].filename, fname);
    fileInfoArr[new_ddid].blockSize = bsize;
    fileInfoArr[new_ddid].numBlock = bno;

    for (int i = 0; i < DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM; i++)
    {
        strcpy(fileInfoArr[new_ddid].files[i].name, "");
        fileInfoArr[new_ddid].files[i].page_taken = -1;
        fileInfoArr[new_ddid].taken[i] = false;
    }

    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return new_ddid;
}

// accesses file given by ddid, reads the bno'th block and writes it into buffer
// bno is 1 indexed
int read_block_dd(int ddid, int bno, char *buffer)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int fd = open(fileInfoArr[ddid].filename, O_RDONLY);
    if (fd == -1) // create file
    {
        perror("open fail");
        return 0;
    }

    off_t offset = lseek(fd, (bno - 1) * fileInfoArr[ddid].blockSize, SEEK_SET); // seek to the size bytes, size not increased yet
    if (offset == (off_t)-1)
    {
        perror("lseek fail");
        return 0;
    }

    ssize_t sizeRead = read(fd, buffer, fileInfoArr[ddid].blockSize);
    if (sizeRead == -1)
    {
        perror("read error");
        return 0;
    }

    if (close(fd) == -1)
    {
        perror("close fail");
        return 0;
    }
    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return 1;
}

// accesses file given by ddid, writes the bno'th block the data of buffer
// bno is 1 indexed
int write_block_dd(int ddid, int bno, char *buffer)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int fd = open(fileInfoArr[ddid].filename, O_WRONLY);
    if (fd == -1) // create file
    {
        perror("open fail");
        return 0;
    }

    off_t offset = lseek(fd, (bno - 1) * fileInfoArr[ddid].blockSize, SEEK_SET); // seek to the size bytes, size not increased yet
    if (offset == (off_t)-1)
    {
        perror("lseek fail");
        return 0;
    }

    ssize_t sizeRead = write(fd, buffer, fileInfoArr[ddid].blockSize);
    if (sizeRead == -1)
    {
        perror("write error");
        return 0;
    }

    // fileInfoArr[ddid].taken[bno] = true;

    if (close(fd) == -1)
    {
        perror("close fail");
        return 0;
    }
    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return 1;
}

// deletes the file coressponding to the ddid
// return 0 if success, else -1
int del_file_dd(const int ddid)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    // delete the file
    if (remove(fileInfoArr[ddid].filename) == -1)
    {
        perror("remove fail");
        return -1;
    }

    // uninitialize the data in the ddid'th position of the fileInfoArr
    strcpy(fileInfoArr[ddid].filename, FILE_UNINITIALIZED_FILE_NAME);
    fileInfoArr[ddid].blockSize = FILE_UNINITIALIZED_BLOCK_SIZE;
    fileInfoArr[ddid].numBlock = FILE_UNINITIALIZED_NUM_BLOCK;

    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return 0;
}

// ------------------------------------------------------------------------------------

// mounts a file_system with name "mount_name" with size "file_system_size" with "page_size" pages, return ddid of the mount created or -1 of error
int mount(const char *mount_name, int file_system_size, int page_size)
{
    return init_file_dd(mount_name, page_size, file_system_size / page_size);
}

// unmounts (and deletes) the file system return 0 if success, else -1
int unmount(int ddid)
{
    return del_file_dd(ddid);
}

// reuturns a float between 0 and 1 signifiing the amount of space consumed by files
float fileSystemStatus(int ddid)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int taken_count = 0;

    for (int i = 0; i < fileInfoArr[ddid].numBlock; i++)
        if (fileInfoArr[ddid].taken[i])
            taken_count++;

    int numBlock = fileInfoArr[ddid].numBlock;

    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return (float)taken_count / numBlock;
}

// returns -1 if fail, 0 if dsuccess
// maekes a file with
int addFile(int ddid, char *filename)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int page_idx = -1;

    for (int i = 0; i < fileInfoArr[ddid].numBlock; i++)
        if (!fileInfoArr[ddid].taken[i])
        {
            page_idx = i;
            break;
        }

    if (page_idx == -1)
    {
        fprintf(stderr, "error: file system fully consumed, aborting");
        return -1;
    }

    int file_idx = -1;

    for (int i = 0; i < DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM; i++)
        if (fileInfoArr[ddid].files[i].page_taken == -1)
        {
            file_idx = i;
            break;
        }

    if (file_idx == -1)
    {
        fprintf(stderr, "error: too much file created, aborting");
        return -1;
    }

    fileInfoArr[ddid].taken[page_idx] = true;
    strcpy(fileInfoArr[ddid].files[file_idx].name, filename);
    fileInfoArr[ddid].files[file_idx].page_taken = page_idx;

    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return 0;
}

// returns -1 if fail, return 0
int editFileContent(int ddid, char *filename, char *data)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int file_idx = -1;

    for (int i = 0; i < DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM; i++)
        if (strcmp(fileInfoArr[ddid].files[i].name, filename) == 0)
        {
            file_idx = i;
            break;
        }

    if (file_idx == -1)
    {
        fprintf(stderr, "error: file not found");
        return -1;
    }

    int page_idx = fileInfoArr[ddid].files[file_idx].page_taken;
    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return write_block_dd(ddid, page_idx + 1, data);
}

int readFileContent(int ddid, char *filename, char *data)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int file_idx = -1;

    for (int i = 0; i < DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM; i++)
        if (strcmp(fileInfoArr[ddid].files[i].name, filename) == 0)
        {
            file_idx = i;
            break;
        }

    if (file_idx == -1)
    {
        fprintf(stderr, "error: file not found");
        return -1;
    }

    int page_idx = fileInfoArr[ddid].files[file_idx].page_taken;
    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return read_block_dd(ddid, page_idx + 1, data);
}

int deleteFile(int ddid, char *filename)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int file_idx = -1;

    for (int i = 0; i < DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM; i++)
        if (strcmp(fileInfoArr[ddid].files[i].name, filename) == 0)
        {
            file_idx = i;
            break;
        }

    if (file_idx == -1)
    {
        fprintf(stderr, "error: file not found");
        return -1;
    }

    fileInfoArr[ddid].taken[fileInfoArr[ddid].files[file_idx].page_taken] = false;
    fileInfoArr[ddid].files[file_idx].page_taken = -1;
    strcpy(fileInfoArr[ddid].files[file_idx].name, "");
    fileInfoArr = (FileInfo *)shared_memory_detach(fileInfoArr);
    return 0;
}

int editFileName(int ddid, char *old_filename, char *new_filename)
{
    // attach the shared memorry segment
    FileInfo *fileInfoArr = (FileInfo *)shared_memory_attach(shmid);

    int file_idx = -1;

    for (int i = 0; i < DEFAULT_FILE_COUNT_INSIDE_FILESYSTEM; i++)
        if (strcmp(fileInfoArr[ddid].files[i].name, filename) == 0)
        {
            file_idx = i;
            break;
        }

    if (file_idx == -1)
    {
        fprintf(stderr, "error: file not found");
        return -1;
    }

    strcpy(fileInfoArr[ddid].files[file_idx].name, new_filename);
    return 0;
}

int main()
{
    signal(SIGINT, closeProgram);
    initProgram();

    int ddid = mount("C", 4096, 512); // can have 4096/512 = 8 files

    char buffer[4096];
    strcpy(buffer, "abhiroop");

    char fileName[100];
    strcpy(fileName, "data.txt");
    addFile(ddid, fileName);
    editFileContent(ddid, fileName, buffer);

    strcpy(buffer, "");
    readFileContent(ddid, fileName, buffer);
    printf("%s\n", buffer);

    printf("space consumption: %0.2f%% \n", fileSystemStatus(ddid) * 100);
    deleteFile(ddid, fileName);

    unmount(ddid);

    closeProgram(SIGINT);
}