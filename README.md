# lexer

A C library that tokenizes source files into a `TokenArr`. It recognizes
identifiers, keywords, operators, delimiters, and literals, and skips
whitespace and comments.

## Build the library

Clone the repository and build the static library:

```sh
git clone https://github.com/RobloxCode/lexer.git
cd lexer
make
```

This creates `build/liblexer.a`. `make run` builds and runs the demonstration
program. GCC or Clang with C11 support and GNU-compatible extensions is
required.

## Use it from a C project

Include the public lexer header. `lexer/lexer.h` also includes the token-array
and token definitions:

```c
#include "lexer/lexer.h"

#include <stdio.h>

int main(void) {
	Lexer *lexer = lexer_lex("input.c");
	if (!lexer) {
		fprintf(stderr, "Could not open or tokenize input.c\n");
		return 1;
	}

	const TokenArr *tokens = lexer_tokens(lexer);
	for (size_t i = 0; i < token_arr_len(tokens); ++i) {
		const Token *token = &tokens->items[i];
		printf("%s: %s at %d:%d\n",
			   token_type_to_str(token->type), token->lexeme,
			   token->line, token->col);
	}

	lexer_deinit(&lexer);
	return 0;
}
```

Compile your source against the public headers and static library:

```sh
cc -std=c11 -Ilexer/include app.c lexer/build/liblexer.a -o app
./app
```

The returned `TokenArr` is owned by the `Lexer`; treat it as read-only and keep
using it only until `lexer_deinit(&lexer)`. That call releases the token array
and sets `lexer` to `NULL`.

## Install system-wide or to a prefix

```sh
make install PREFIX="$HOME/.local"
```

Then compile with:

```sh
cc -std=c11 -I"$HOME/.local/include" app.c \
   -L"$HOME/.local/lib" -llexer -o app
```

The default install prefix is `/usr/local`.
