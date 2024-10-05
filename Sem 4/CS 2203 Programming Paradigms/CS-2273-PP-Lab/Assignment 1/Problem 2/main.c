#include <stdio.h>
#include <string.h> //for strlen()
#include <stdlib.h> // for exit()
#include "recursion.h"

void main()
{
    printf("Enter Choice: \n");
    printf("1) String Comparision\n");
    printf("2) Find largest among n integers\n");
    printf("3) Search num in list L\n");
    printf("4) Reverse List L\n");
    printf("5) Check Palindrome\n");
    printf("6) Replace occurrence in a string\n");
    printf("7) Sort Array\n\n");

    printf("Choice: ");
    int choice;
    scanf("%d", &choice);
    getc(stdin); //getting the \n out of stdin
    printf("\n");

    if (choice == 1)
    {
        char str1[20];
        printf("Enter str1(not more than 20 letters): ");
        fgets(str1, 20, stdin);

        char str2[20];
        printf("Enter str2(not more than 20 letters): ");
        fgets(str2, 20, stdin);

        printf("Output: %d ", string_comp_recur(str1, strlen(str1), str2, strlen(str2)));
        printf("(0 if str1 and str2 is same, 1 if str1>str2, else -1)\n");
    }
    else if (choice == 2)
    {
        printf("Enter number of elements: ");
        int n;
        scanf("%d", &n);

        int arr[n];
        printf("Enter Array: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        printf("Max Number: %d\n", largest_num_recur(arr, n, -1000));
    }
    else if (choice == 3)
    {
        printf("Enter number of elements: ");
        int n;
        scanf("%d", &n);

        int arr[n];
        printf("Enter Array: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        printf("Enter number to be searched: ");
        int num;
        scanf("%d", &num);

        printf("Output: %d (1 means found, 0 means not found)\n", num_search_recur(arr, n, num));
    }
    else if (choice == 4)
    {
        printf("Enter number of elements: ");
        int n;
        scanf("%d", &n);

        int arr[n];
        printf("Enter Array: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        printf("Reverse Array: ");
        print_reverse_recur(arr, n);
        printf("\n");
    }
    else if (choice == 5)
    {
        char str[20];
        printf("Enter string (not more than 20 characters): ");
        fgets(str, 20, stdin);
        str[strcspn(str, "\n")] = '\0';
        //strcspn() calculates the length of the number of characters before the 1st occurrence of character present in both the string.

        printf("Output: %d (1 means string is palindrome, 0 means not palindrome) \n", check_palindrome_recur(str, strlen(str), 0));
    }
    else if (choice == 6)
    {
        char str[20];
        printf("Enter string (not more than 20 characters): ");
        fgets(str, 20, stdin);

        printf("Enter character to be replaced: ");
        char c1;
        scanf("%c", &c1);
        getc(stdin); //getting the \n out of stdin

        printf("Enter new character: ");
        char c2;
        scanf("%c", &c2);

        replace_occurrences_recur(str, strlen(str), c1, c2);

        printf("Output: %s\n", str);
    }
    else if (choice == 7)
    {
        printf("Enter number of elements: ");
        int n;
        scanf("%d", &n);

        int arr[n];
        printf("Enter Array: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        sort_recur(arr, n);

        printf("Sorted Array: ");
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
    else
    {
        printf("Error: Wrong Input\n");
        exit(-1);
    }
}