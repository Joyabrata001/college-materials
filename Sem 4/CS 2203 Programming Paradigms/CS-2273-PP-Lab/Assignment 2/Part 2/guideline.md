-   Dont use `void*` in Q7

    -   It is very costly (8 byte)
    -   use `unsigned char*`

        -   can do

        ```cpp
        typedef unsigned char* byte
        ```

        -   size of this is one byte, hence can be used to save pointers but in a very less space compared to `void*`

            -   `int` is 4 byte
            -   `short` is 2 byte

        -   We are allowed to use `memcpy()` _It'S NeCeSsArY_

        -   use typecast (It's a hot garbage 😥)

-   Convert .cpp to txt file before submitting
    -   Easy to check in web
