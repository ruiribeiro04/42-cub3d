# Libft - 42 Porto
[![42 Porto](https://img.shields.io/badge/42%20Porto-School-blue?style=for-the-badge&logo=42)](https://www.42porto.com)
[![Language](https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg?style=for-the-badge)](https://projects.intra.42.fr/)

My first C library implementation as part of the 42 Porto common core curriculum.

## About the Project

Libft is the first project in the 42 Porto common core curriculum. The goal is to recreate various functions from the standard C library (libc), as well as implement additional useful functions for future projects.

By recreating these fundamental functions, we develop a deeper understanding of data types, structures, and memory manipulation in C.

The resulting library, `libft.a`, will be used in many subsequent projects at 42, saving time and providing consistent tools for our development.

## Implemented Functions

### Libc Functions
| Function | Description |
|--------|-----------|
| ft_isalpha | Checks if the character is alphabetic |
| ft_isdigit | Checks if the character is a digit |
| ft_isalnum | Checks if the character is alphanumeric |
| ft_isascii | Checks if the character is in the ASCII table |
| ft_isprint | Checks if the character is printable |
| ft_strlen | Calculates the length of a string |
| ft_memset | Fills the first n bytes of memory with a value |
| ft_bzero | Fills the first n bytes of memory with zeros |
| ft_memcpy | Copies n bytes from memory area src to memory area dest |
| ft_memmove | Copies n bytes from memory area src to memory area dest (safe for overlapping) |
| ft_strlcpy | Copies the source string to dest with limited size |
| ft_strlcat | Concatenates the source string after dest with limited size |
| ft_toupper | Converts a lowercase character to uppercase |
| ft_tolower | Converts an uppercase character to lowercase |
| ft_strchr | Locates the first occurrence of c in string s |
| ft_strrchr | Locates the last occurrence of c in string s |
| ft_strncmp | Compares up to n characters of two strings |
| ft_memchr | Locates the first occurrence of c in the first n bytes of s |
| ft_memcmp | Compares the first n bytes of two memory areas |
| ft_strnstr | Locates a substring within a string with limited length |
| ft_atoi | Converts a string to an integer |
| ft_strdup | Duplicates a string |

### Additional Functions
| Function | Description |
|--------|-----------|
| ft_substr | Returns a substring from string s |
| ft_strjoin | Concatenates two strings |
| ft_strtrim | Removes specified characters from the beginning and end of the string |
| ft_split | Splits a string using a delimiter character |
| ft_itoa | Converts an integer to a string |
| ft_strmapi | Applies a function to each character of a string |
| ft_striteri | Applies a function to each character of a string with indexes |
| ft_putchar_fd | Writes a character to a file descriptor |
| ft_putstr_fd | Writes a string to a file descriptor |
| ft_putendl_fd | Writes a string followed by a newline to a file descriptor |
| ft_putnbr_fd | Writes a number to a file descriptor |

### Bonus Functions (Linked List Manipulation)
| Function | Description |
|--------|-----------|
| ft_lstnew | Creates a new list element |
| ft_lstadd_front | Adds an element to the beginning of the list |
| ft_lstsize | Counts the number of elements in the list |
| ft_lstlast | Returns the last element of the list |
| ft_lstadd_back | Adds an element to the end of the list |
| ft_lstdelone | Frees the memory of an element without freeing the next one |
| ft_lstclear | Frees the memory of the entire list |
| ft_lstiter | Applies a function to each element of the list |
| ft_lstmap | Creates a new list by applying a function to each element |

## Resources

- [C Library Manual (man)](https://www.man7.org/linux/man-pages/)
- [C Programming: A Modern Approach](http://knking.com/books/c2/)
