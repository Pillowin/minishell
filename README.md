# minishell

Aussi mignon qu'un vrai shell
L’objectif de ce projet est de créer un simple shell. Ca sera votre propre petit bash, ou zsh. Vous en apprendrez beaucoup sur les process et les file descriptors.

## Tree

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

- Check leaks

### Expansion

- Handle dolar

### Makefile

- remove fsanitize
- explicit files (remove wildcard)
- compile .o in folder

### Divers

- Remove useless libft file

``ls -l | grep grw | wc -l > lsfile ; < lsfile cat | rev > itit > utut >> otot ; diff otot toto >> diff``
``ls -l | grep d'r'w | wc -l > lsf\\ile ; < ls"'f'i ile" c\at | rev \> itit > \u\t\u\t\ \>>> o't'ot \;; diff otot toto >> diff``
``< abc >> toto >> tata > ta  >ty >\> >>\>\> >'>>'``


prompt>echo a $
a $
prompt>echo a $cmd
a CMD
prompt>echo a $'cmd'
a cmd
prompt>echo a $'cmd'-toto
a cmd-toto
prompt>echo a $cmd-toto
a CMD-toto
prompt>echo a $'    cmd'
a     cmd
prompt>echo a $cmd'-toto' 
a CMD-toto
prompt>echo a $zboub
a
prompt>echo a $zboub-toto
a -toto
prompt>echo a $'zboub''-toto'
a zboub-toto
