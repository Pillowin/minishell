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

``ls -l | grep grw | wc -l > lsfile ; < lsfile cat | rev > itit > utut >> otot ; diff otot toto >> diff``
``ls -l | grep d'r'w | wc -l > lsf\\ile ; < ls"'f'i ile" c\at | rev \> itit > \u\t\u\t\ \>>> o't'ot \;; diff otot toto >> diff``

- mettre des return jusqu'au main en cas d'erreur
- fonctions de free
- fonctions pour les repetitions
- mise a la norme
