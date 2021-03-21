# minishell
Aussi mignon qu'un vrai shell
L’objectif de ce projet est de créer un simple shell. Ca sera votre propre petit bash, ou zsh. Vous en apprendrez beaucoup sur les process et les file descriptors.

## Tree rule
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

### Parser
- Create tree
- $ ' " \

### Expansion
- Handle double quotes
- Handle simple quote
- Handle baskslash
- Handle dolar

### Makefile
- remove fsanitize
- explicit files (remove wildcard)
- compile .o in folder

### Divers
- error function
- check leaks
- l'erreur ne quitte pas forcement le programme avec les ;
