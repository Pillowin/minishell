# minishell

Aussi mignon qu'un vrai shell
L’objectif de ce projet est de créer un simple shell. Ca sera votre propre petit bash, ou zsh. Vous en apprendrez beaucoup sur les process et les file descriptors.

## Tree rules

Parcours en prefix
Priorites :

- SEMI
- PIPE
- DGREAT GREAT LESS
- WORD

Regles de creation d'arbre :

- Semi : tout ce qui est a gauche va a gauche && tout ce qui est a droite va a droite
- Pipe : tout ce qui est a gauche va a gauche && tout ce qui est a droite va a droite
- Redir : tout ce qui est a gauche va a droite && tout ce qui est a droite va a gauche
- Command : a la suite en prefix

## TODO

### Lexer

- Rajoute un token \
- Checks de quotes
- Expansion des " ' et \

### Parser

- Finisse le regroupement des token
- Create tree
- $ ' " \

### Expansion

- Handle dolar

### Makefile

- remove fsanitize
- explicit files (remove wildcard)
- compile .o in folder

### Divers

- check leaks
- error function (l'erreur ne quitte pas forcement le programme avec les ;)
- Remove useless libft file

## Parsing (lexer, parser, expander)

1. Création des tokens
2. Expansion des backslashs - quotes
3. Création des t_command

---
command = ``echo Je m\'appelle   Antoine``

1.
	- TOK_WORD		= echo
	- TOK_SPACE		= ` `
	- TOK_WORD		= Je
	- TOK_SPACE		= ` `
	- TOK_WORD		= m
	- TOK_BSLASH	= \
	- TOK_QUOTE		= '
	- TOK_WORD		= appelle
	- TOK_SPACE		= ` `
	- TOK_SPACE		= ` `
	- TOK_SPACE		= ` `
	- TOK_WORD		= Antoine

2.
	- TOK_WORD		= echo
	- TOK_SPACE		= ` `
	- TOK_WORD		= Je
	- TOK_SPACE		= ` `
	- TOK_WORD		= m
	- TOK_WORD		= '
	- TOK_WORD		= appelle
	- TOK_SPACE		= ` `
	- TOK_SPACE		= ` `
	- TOK_SPACE		= ` `
	- TOK_WORD		= Antoine

3.
- TOK_CMD		= [echo, Je, m'appelle, Antoine]

out = `Je m'appelle Antoine`

---
command = `echo "J\'ai dis : 'Je m\"appelle    $USER'"' GAUTIER' et   '$USER c\"est moi'`
expected `J\'ai dis : 'Je m"appelle    antoine' GAUTIER et $USER c\"est moi`

1.
TOK_WORD	=	`echo`
TOK_SPACE	=	` `
TOK_DQUOTE	=	`"`
TOK_WORD	=	`J`
TOK_BSLASH	=	`\`
TOK_QUOTE	=	`'`
TOK_WORD	=	`ai`
TOK_SPACE	=	` `
TOK_WORD	=	`dis`
TOK_SPACE	=	` `
TOK_WORD	=	`:`
TOK_SPACE	=	` `
TOK_QUOTE	=	`'`
TOK_WORD	=	`Je`
TOK_SPACE	=	` `
TOK_WORD	=	`m`
TOK_BSLASH	=	`\`
TOK_DQUOTE	=	`"`
TOK_WORD	=	`appelle`
TOK_SPACE	=	` `
TOK_SPACE	=	` `
TOK_SPACE	=	` `
TOK_SPACE	=	` `
TOK_DOLAR	=	`$`
TOK_WORD	=	`USER`
TOK_QUOTE	=	`'`
TOK_DQUOTE	=	`"`
TOK_QUOTE	=	`'`
TOK_SPACE	=	` `
TOK_WORD	=	`GAUTIER`
TOK_QUOTE	=	`'`
TOK_SPACE	=	` `
TOK_WORD	=	`et`
TOK_SPACE	=	` `
TOK_SPACE	=	` `
TOK_SPACE	=	` `
TOK_QUOTE	=	`'`
TOK_DOLAR	=	`$`
TOK_WORD	=	`USER`
TOK_SPACE	=	` `
TOK_WORD	=	`c`
TOK_BSLASH	=	`\`
TOK_DQUOTE	=	`"`
TOK_WORD	=	`est`
TOK_SPACE	=	` `
TOK_WORD	=	`moi`
TOK_QUOTE	=	`'`
TOK_NL		=	`\n`


2.
TOK_WORD	=	`echo`
TOK_SPACE	=	` `

TOK_WORD	=	`J`
TOK_WORD	=	`\`
TOK_WORD	=	`'`
TOK_WORD	=	`ai`
TOK_WORD	=	` `
TOK_WORD	=	`dis`
TOK_WORD	=	` `
TOK_WORD	=	`:`
TOK_WORD	=	` `
TOK_WORD	=	`'`
TOK_WORD	=	`Je`
TOK_WORD	=	` `
TOK_WORD	=	`m`

TOK_WORD	=	`"`
TOK_WORD	=	`appelle`
TOK_WORD	=	` `
TOK_WORD	=	` `
TOK_WORD	=	` `
TOK_WORD	=	` `
TOK_DOLAR	=	`$`
TOK_WORD	=	`USER`
TOK_WORD	=	`'`


TOK_WORD	=	` `
TOK_WORD	=	`GAUTIER`

TOK_SPACE	=	` `
TOK_WORD	=	`et`
TOK_SPACE	=	` `
TOK_SPACE	=	` `
TOK_SPACE	=	` `

TOK_WORD	=	`$`
TOK_WORD	=	`USER`
TOK_WORD	=	` `
TOK_WORD	=	`c`
TOK_WORD	=	`\`
TOK_WORD	=	`"`
TOK_WORD	=	`est`
TOK_WORD	=	` `
TOK_WORD	=	`moi`

TOK_NL		=	`\n`

3.
TOK_CMD = [echo, J\'ai dis : 'Je m"appelle    antoine' GAUTIER, et, $USER c\"est moi]

out = 		`J\'ai dis : 'Je m"appelle    antoine' GAUTIER et $USER c\"est moi`
