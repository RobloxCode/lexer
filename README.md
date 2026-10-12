# lexer

A C library that tokenizes C source files into a `TokenArr`. It recognizes
identifiers, keywords, operators, delimiters, and literals, and skips
whitespace and comments.

The library is built as a static archive (`liblexer.a`) with a small public
API, so you can clone it, build it, and use it from your own `main.c`.

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

```sh
git clone https://github.com/RobloxCode/lexer.git
cd lexer
make
```

This creates `build/liblexer.a`. To try the included demonstration program,
run `make run`.

For a debug build with AddressSanitizer, run `make clean && make DEBUG=1`. If
you build the library this way, link your own program with
`-fsanitize=address` as well.

## Quick example

Save this as `app.c`. It lexes the file given on the command line and prints
every token:

```c
#include <lexer/lexer.h>

#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file.c>\n", argv[0]);
        return 1;
    }

    Lexer *lexer = lexer_lex(argv[1]);
    if (!lexer) {
        fprintf(stderr, "Could not open or tokenize %s\n", argv[1]);
        return 1;
    }

    const TokenArr *tokens = lexer_tokens(lexer);
    for (size_t i = 0; i < token_arr_len(tokens); ++i) {
        const Token *token = &tokens->items[i];
        printf("%d:%d %s '%s'\n", token->line, token->col,
               token_type_to_str(token->type), token->lexeme);
    }

    lexer_deinit(&lexer);
    return 0;
}
```

`lexer/lexer.h` is the only header you need to include: it also pulls in the
token array and token definitions.

The returned `TokenArr` is owned by the `Lexer`. Treat it as read-only and only
use it until you call `lexer_deinit(&lexer)`, which releases the tokens and sets
`lexer` to `NULL`.

## Using the library

There are two ways to use the library. Pick one.

### Option 1: use it in place (no installation)

Build the library inside the cloned folder as shown above, then point the
compiler at the headers and the archive. Assuming the repository was cloned
into a folder called `lexer` next to your `app.c`:

```sh
cc -std=c11 -Ilexer/include app.c lexer/build/liblexer.a -o app
./app some_file.c
```

- `-Ilexer/include` is the include root. It is what makes
  `#include <lexer/lexer.h>` resolve to `lexer/include/lexer/lexer.h`.
- `lexer/build/liblexer.a` is the library itself. Put it after your source
  file on the command line.

This option needs no permissions and always uses your latest build. It is the
best choice while you are still changing the lexer.

### Option 2: install it

Installing copies the library and headers into a standard location so you can
use them by name, without spelling out paths to the clone.

System-wide (needs root, default prefix is `/usr/local`):

```sh
sudo make install
cc -std=c11 app.c -llexer -o app
```

Only for your user (no root needed):

```sh
make install PREFIX="$HOME/.local"
cc -std=c11 -I"$HOME/.local/include" app.c \
   -L"$HOME/.local/lib" -llexer -o app
```

`PREFIX` is a make variable. Setting it on the command line overrides the
default of `/usr/local`. Any prefix you can write to works the same way.

Because `liblexer.a` is a static library, it is linked into your executable.
You do not need to set any runtime library path.

If you change the lexer later, run `make install` again, otherwise your
projects keep linking the old copy.

## Where the files are installed

Everything is placed under the prefix:

| What                  | Location                          |
|-----------------------|-----------------------------------|
| Static library        | `$PREFIX/lib/liblexer.a`          |
| Public headers        | `$PREFIX/include/lexer/*.h`       |

With the default prefix this is `/usr/local/lib/liblexer.a` and
`/usr/local/include/lexer/`. With `PREFIX="$HOME/.local"` it is
`~/.local/lib/liblexer.a` and `~/.local/include/lexer/`.

The headers go inside a `lexer/` subfolder on purpose, so that
`#include <lexer/lexer.h>` does not collide with headers from other projects.

The compiler automatically searches `/usr/local/include` and `/usr/local/lib`,
which is why the system-wide install needs no `-I` or `-L` flags. A custom
prefix such as `~/.local` is not searched by default, so you must pass those
flags yourself. To see the directories your compiler searches for
`#include <...>`, run:

```sh
echo | cc -E -Wp,-v -x c -
```

The `#include <...> search starts here:` section of the output lists them.

To remove an installation, delete those files by hand (the Makefile has no
uninstall target):

```sh
rm -f "$PREFIX/lib/liblexer.a"
rm -rf "$PREFIX/include/lexer"
```

## Editor setup

Compiling from the terminal works as described above, but your editor may
still show errors such as `'lexer/token_arr.h' file not found`, `Unknown type
name 'Token'`, or `Call to undeclared function 'token_type_to_str'`. These come
from the editor's language server, not from the compiler. The server cannot
see the `-I` flag you pass on the command line, so it does not know where the
lexer headers live.

If you use the in-place option (Option 1) with a custom include path, create a
file named `compile_flags.txt` in the same folder as your `app.c`, with one
flag per line:

```
-std=c11
-Ilexer/include
```

Paths in this file are relative to the folder that contains it. Restart the
language server or reopen the file afterwards. The compiler never reads this
file, so it has no effect on how your program builds.

Editors that use clangd as their language server will read
`compile_flags.txt` automatically, and are the ones that may need it:

- Neovim (for example through `nvim-lspconfig`)
- Vim (with a clangd client such as `vim-lsp` or `coc.nvim`)
- Helix
- Emacs (with `eglot` or `lsp-mode`)
- Sublime Text (with the LSP-clangd package)
- Zed
- VS Code with the clangd extension

Some setups behave differently:

- VS Code with Microsoft's C/C++ extension does not read this file. Add the
  include path to `includePath` in `.vscode/c_cpp_properties.json` instead.
- If you installed the library system-wide (Option 2 with the default
  prefix), the headers are already in the default search path and you do not
  need this file. With a custom prefix such as `~/.local`, add
  `-I/home/your_user/.local/include` to `compile_flags.txt` (use the full
  path, since variables like `$HOME` are not expanded in this file).
- If your project already generates a `compile_commands.json` (for example
  with `bear -- make`, or CMake with `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON`),
  clangd uses that instead and you do not need `compile_flags.txt`.

## Example Makefiles for your project

If you do not want to type the compile command each time, here are two minimal
Makefiles for a project containing `app.c`. Recipe lines must start with a tab.

Using the lexer in place, with the repository cloned into `lexer/`:

```make
CC      = cc
CFLAGS  = -std=c11 -Wall -Wextra
LEXER   = lexer

app: app.c $(LEXER)/build/liblexer.a
	$(CC) $(CFLAGS) -I$(LEXER)/include app.c $(LEXER)/build/liblexer.a -o $@

$(LEXER)/build/liblexer.a:
	$(MAKE) -C $(LEXER)

clean:
	rm -f app

.PHONY: clean
```

Using an installed lexer (system-wide or a custom prefix):

```make
CC      = cc
CFLAGS  = -std=c11 -Wall -Wextra
PREFIX ?= /usr/local

app: app.c
	$(CC) $(CFLAGS) -I$(PREFIX)/include app.c -L$(PREFIX)/lib -llexer -o $@

clean:
	rm -f app

.PHONY: clean
```

Run `make` for the default prefix, or `make PREFIX="$HOME/.local"` if you
installed to your home directory.he default install prefix is `/usr/local`.
