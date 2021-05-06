# minishell

Aussi mignon qu'un vrai shell
L’objectif de ce projet est de créer un simple shell. Ca sera votre propre petit bash, ou zsh. Vous en apprendrez beaucoup sur les process et les file descriptors.

## Tokens

| TOKEN       | Character |
| :---------- | :-------: |
| TOK_SEMI    | ;         |
| TOK_PIPE    | \|        |
| TOK_LESS    | <         |
| TOK_GREAT   | >         |
| TOK_DGREAT  | >>        |
| TOK_BSLASH  | \\        |
| TOK_DOLLAR  | $         |
| TOK_QUOTE   | '         |
| TOK_DQUOTE  | "         |
| TOK_NEWLINE | \\n       |
| TOK_SPACE   |           |
| TOK_WORD    | xxx       |

```C
/*
**		-- The Grammar --
**
**	program        : command NEWLINE
**	               |         NEWLINE
**	               ;
**	command        : simple_command separator command
**	               | simple_command SEMI
**	               | simple_command
**	               ;
**	simple_command : cmd_prefix WORD cmd_suffix
**	               | cmd_prefix WORD
**	               | cmd_prefix
**	               |            WORD cmd_suffix
**	               |            WORD
**	               ;
**	cmd_prefix     : io_file cmd_prefix
**	               | io_file
**	               ;
**	word           : WORD
**	               ;
**	cmd_suffix     : io_file cmd_suffix
**	               | io_file
**	               | WORD    cmd_suffix
**	               | WORD
**	               ;
**	io_file        : LESS   WORD
**	               | GREAT  WORD
**	               | DGREAT WORD
**	               ;
**	separator      : PIPE
**	               | SEMI
**	               ;
*/
```

## TODO

- Remove useless libft file
- remove fsanitize
- explicit files (remove wildcard) in makefile
- leaks
- norm
- clean files
- exit status
- error messages
- syntax redir dollar
- zombie quand ./toto alors que toto est un dossier
