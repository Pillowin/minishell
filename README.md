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
- segv quand entree > BUF_SIZE
- exit


<!-- ```verif l'ordre d'execution du path``` -->

<!--
```bash
prompt>env | grep PWD
OLDPWD=jhgbnk
PWD=/home/user42/42/minishell
prompt>cd toto
prompt>env | grep PWD
OLDPWD=/home/user42/42/minishell
PWD=/home/user42/42/minishell/toto
prompt>cd ..
prompt>env | grep PWD
OLDPWD=/home/user42/42/minishell/toto
PWD=/home/user42/42/minishell
prompt>cd -
prompt>env | grep PWD
OLDPWD=/home/user42/42/minishell
PWD=/home/user42/42/minishell/toto
prompt>pwd
/home/user42/42/minishell/toto
prompt>cd
minishell (tree): cd: « HOME » not set
prompt>export HOME=$PWD/..
prompt>export HOME=$PWD/..
prompt>cd
minishell (tree): cd: No such file or directory
prompt>echo $HOME
```
-->
<!--
```export coucou ca va```	=> env doit pas afficher les valeur vide
```export est pas trie```
```export 2wefr coucou ca``` => pareil pour unset
-->

<!-- - ctrl d apres ctrl c au debut de minishell fonctionne pas la premiere fois -->

<!-- 
- builtin
- cd $USER$plop$USER => not found (err msg)
- cd -
-->

<!--
```<rien cat >coucou``` => rien existe pas
```>rien``` => loop
-->

<!-- - syntax redir dollar -->
<!-- - zombie quand ./toto alors que toto est un dossier -->

<!-- - ```dsfkgjd | ls -l``` -->

<!-- echo \a => 2 err msg -->
<!-- - fleche segv -->
<!-- env -i ./minishell demarre pas a cause de term -->

<!-- 
- signaux
- ctrl + c need to clean buf
- ctrl + c apres ./minishell retour a la ligne
- ctrl + c afficher ^C 
-->

<!--
```
0 prompt>echo | echo | echi
Not found error
minishell: echi: command not found
command not found
127 prompt>echo | echo | echi | echo

Not found error
0 minishell: prompt>No such file or directory
```
-->

<!-- ```ls coucou | export c=moi | grep -c``` -->
<!-- ```hrtgf | htg |jyhtg |jyhtgrf |jhtgr |jhfgd |jhgfd |jhgfd |jhfgd |jhgfd |jghfd``` => messages d'erreur melanges -->
