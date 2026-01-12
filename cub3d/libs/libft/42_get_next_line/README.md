# Get Next Line - 42 Porto
[![42 Porto](https://img.shields.io/badge/42%20Porto-School-blue?style=for-the-badge&logo=42)](https://www.42porto.com)
[![Language](https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))

> "We fell, but our arrows never missed."

# About the project
get_next_line is a fundamental project in the 42 Porto common core curriculum. The objective is to create a C function capable of reading and returning one line at a time from a file descriptor.

The project focuses on efficient dynamic memory management, use of static variables to track progress between function calls, and careful data manipulation.

This project is especially important because the ability to read data from a file descriptor line by line is essential for various future projects at 42, whether reading from a file, stdin, or even later from a network connection.

## Implemented Features

### Mandatory Part
| Function | Description |
|--------|-----------|
| get_next_line | Reads and returns one line at a time from a file descriptor |
| get_next_line_utils | Contains auxiliary functions for the operation of get_next_line |

### Technical Challenges
- Reading a predefined number of bytes (BUFFER_SIZE) until finding the end of a line
- Managing cases where the number of bytes in the line is not a multiple of BUFFER_SIZE
- Efficient dynamic memory manipulation (avoiding leaks)
- Using static variables to maintain state between function calls
