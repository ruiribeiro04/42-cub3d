# ft_printf - 42 Porto
[![42 Porto](https://img.shields.io/badge/42%20Porto-School-blue?style=for-the-badge&logo=42)](https://www.42porto.com)
[![Language](https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen.svg?style=for-the-badge)](https://projects.intra.42.fr/)

My implementation of the C `printf` function as part of the 42 Porto common core curriculum.

## About the Project

`ft_printf` is a project in the 42 common core curriculum. The goal is to recreate the behavior of the standard C library function `printf`. This project involves understanding and implementing variadic functions to handle a variable number of arguments, and processing format specifiers to output data in various formats.

## Implemented Format Specifiers

The following format specifiers are handled by `ft_printf`:

| Specifier | Description |
|-----------|-------------|
| `%c`      | Prints a single character. |
| `%s`      | Prints a string (as defined by common C usage). |
| `%p`      | The `void *` pointer argument has to be printed in hexadecimal format. |
| `%d`      | Prints a decimal (base 10) number. |
| `%i`      | Prints an integer in base 10. |
| `%u`      | Prints an unsigned decimal (base 10) number. |
| `%x`      | Prints a number in hexadecimal (base 16) lowercase format. |
| `%X`      | Prints a number in hexadecimal (base 16) uppercase format. |
| `%%`      | Prints a percent sign. |

## Resources

- [C Library Manual (man printf)](https://man7.org/linux/man-pages/man3/printf.3.html)
