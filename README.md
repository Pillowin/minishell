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

- comment all func

- '' => should return cmd not found
- echo | exit | echo => exit devrait pas s'afficher
- cat^C => casse historique
- cat ^C des fois affiche 2 fois ^C

<!-- - remove fsanitize (in libft too) -->
<!-- - exit avec nombre > LONG_LONG_MAX -->
<!-- - cd .. ; echo $PWD $OLDPWD => PWD et OLDPWD pas mis a jour -->
<!-- - env et unset si err => pas le bon exit val -->
<!-- - echo toto > dir => si dir est un dossier err => corriger quand < -->
<!-- - env -i ./minishell => erreur qui devrait pas -->
<!-- ```
user42@salty-VirtualBox:~/42/minishell$ ./minishell 
minishell>ls hiujkl
ls: impossible d'accéder à 'hiujkl': Aucun fichier ou dossier de ce type
minishell>echo $?
2
minishell>echo $?
2
minishell>echo ihjklm
ihjklm
minishell>echo $?
2
minishell>
``` -->
<!-- echo toto > plop > plip >plap => pas les bonnes permissions -->
<!-- - awk => mauvais exit status -->
<!-- - /bin/ls yghjk => pas le bon return val -->
<!-- - yftghjkn => mauvaise err donc mauvais exit status -->
<!-- - unset PATH ; ls => SEGV 0 0x5572badd7667 in check_paths src/exec/binary_path.c:90 -->
<!-- - minishell>echo toto > tata => FATAL, need to stat -->
<!-- - unset PATH ; ls => mauvaise err et surtout NOT_FOUND qui return 127.. -->
<!-- - leaks -->
<!-- - exit : verif si numeric en prio, numeric quitte alors que multiple non -->
<!-- - exit quitte pas si multiple arg numeric -->

<!-- - exit -->
<!-- - verif exit value des messages d'err -->
<!-- - check TODO: -->
<!-- - test export env unset -->
<!-- - explicit files (remove wildcard) in makefile -->
<!-- - ~~norm libft~~ -->
<!-- - ~~Remove useless libft file~~ -->
<!-- - ~~norm~~ -->
<!-- - ~~clean files~~ -->
<!-- - ~~func to print err message~~ -->
<!-- - si errno == errmalloc => gc_clean + exit	|||| => FATAL ERR -->
<!-- - differencer dans error errno qui relance un prompt et errno qui quitte tout -->

<!-- ``echo toto | cat -e > toto ; < toto cat | cat -e | wc -c`` -->

<!-- ```
export toto=toto
export toto
env | grep toto => toto should not be there
```

```
user42@salty-VirtualBox:~/42/minishell$ env | grep toto
toto=toto
user42@salty-VirtualBox:~/42/minishell$ export toto
user42@salty-VirtualBox:~/42/minishell$ env | grep toto
toto=toto
user42@salty-VirtualBox:~/42/minishell$ 
``` -->

<!-- - add gc_clean before each exit et toujours exit(g_exit_status & 0x00FF); -->

<!-- ``echo toto | sdf ;f`` => manque le 2e command not found -->
<!-- ``minishell>export nouvelle=new`` => SEGV
``export toto=`` => doit s'afficher dans export avec toto="" -->

<!-- ```
minishell>cd trucquiexit pas
minishell: cd: too many arguments
minishell>cd trucquiexit
minishell: cd: trucquiexit: No such file or directory
minishell>echo $?
0
``` -->
<!-- ```
minishell>echo toto < tata
minishell: tata: Bad file descriptor
user42@salty-VirtualBox:~/42/minishell$
```	=> mettre err en ERR_NO pour pas exit -->

<!-- - error messages -->
<!-- - exit status -->

<!-- - segv quand entree > BUF_SIZE -->
<!-- ```
env -i ./minishell
cd ..
env	=> pas OLDPWD	=> update env claqué
``` -->

<!-- ```cd Makefile => not a directory error``` -->

<!-- ```
export	coucou ca va
export	=> doit pas afficher =""
``` -->

<!-- ```not such file doit pas renvoyer 127``` -->

<!-- ```< plop | ls | echo``` -->

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
