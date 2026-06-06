# lexer

This is a lexer written in C that tokenizes C source code

# build

you can just simply clone the repo into your machine with 
-`git clone github.com/RobloxCode/lexer`

you can just compile the program
- `make`

to compile and execute right away
- `make run`
  
the output binary will be placed in bin/out

there's also a `make clean` to remove the bin produced when compiling

# Requirements

- GCC with C11 support
- Compiled with `-fsanitize=address` for memory safety during development
