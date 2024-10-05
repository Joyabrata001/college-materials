# Common Mistakes To Avoid In this Experiment

1. Don't use `extern` in these `.h` files

    - `extern` makes variable or function global, which is of no use here.
    - `extern int a = 0` makes `a` global variable.

2. use `#ifndef`, `#define`, and `#endif` in `.h` file

    - This avoids multiple definition of same `.h` file if defined in some other files, which may cause problem.
    - Example of how to use these preprocessor directives :

    ```c
    #ifndef RECURSION_H
    #define RECURSION_H
    int string_comp_recur(char *s1, int len1, char *s2, int len2);
    int largest_num_recur(int *arr, int n, int max);
    int num_search_recur(int *L, int n, int num);
    void print_reverse_recur(int *L, int n);
    int check_palindrome_recur(char *s, int len, int pos);
    void replace_occurrences_recur(char *s, int len, char c1, char c2);
    void sort_recur(int *arr, int n);
    #endif
    ```

    - Macro-Name ( `RECURSION_H` above ) should be file name, to avoid having Macro-Name collision in case of multiple `.h` file usage.

3. General Code Convention to follow

-   Always write preprocessor directives in CAPS where possible
-   Give understandable names to variables and functions

4. Write only function Definition in `.h` files
-   Generally Client works with functions defined in `.h` file, he doesn't need to know what actually happens in function. [Its a OOP Concept]
-   `gcc` can find function implementation from `.a` files, which can't be read by user, which provides code secrecy and Non-edibility.