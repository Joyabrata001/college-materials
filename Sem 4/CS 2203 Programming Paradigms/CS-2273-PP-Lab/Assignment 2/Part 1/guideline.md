## Guidelines by sir

1. It is advised not to use cpp STL structures as `string`, `vector`, etc.
    - use these when you are actually developing some application
    - in here we are here to learn, so its better if wee go all inside that structures, that would also be helpful in future
        - Eg: if we use `char*` instead of `string` we have to do some additional nuisances like deleting heap memory of `char*`. This solidifies our learning.
        - Eg: We `free() / delete` data just before the pointer in question is about to go out of scope. We will totally avoid this nuisance when we use STL.
            - Fun fact: OS automatically frees all heap memory after program execution

2. while making function which is not supposed to return anything, rather than returning `void`, we can return `bool` to signify if function has actually did it's job or not.

3. Don't ever use some arbitrary number like `10` inside a function, instead define a `const` parameter and use it.
    - when you have to change that `10` you will have to look into code again to change every instance of `10`, but if you had used `const`, you will just have to changes the value of that `const` to affect the whole function.

4. in if() or any other condition block, non zero numbers are considered as true