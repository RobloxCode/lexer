# lexer

A simple, modular lexical analyzer built to tokenize source code into structured tokens. It handles basic syntax including identifiers, keywords, operators, and literals while stripping out whitespace and comments to prepare code for parsing.

# build

you can just simply clone the repo into your machine with 
-`git clone github.com/RobloxCode/lexer lexer`

you can just compile the program
- `make -C lexer`

you also have to include
- `#include "lexer/lexer.h"`
- `#include "lexer/token_arr.h"`


compile your program 
- `gcc file.c -Ilexer/include lexer/build/liblexer.a -o app`
  
the output binary will be placed in bin/out

there's also a `make clean` to remove the bin produced when compiling

# Requirements

- GCC with C11 support
- Compiled with `-fsanitize=address` for memory safety during development
