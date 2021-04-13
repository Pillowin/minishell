/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 14:48:27 by agautier          #+#    #+#             */
/*   Updated: 2021/03/31 16:29:4 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_msg(char **err_msg)
{
	err_msg[NONE] = "No error\n";
	err_msg[MALLOC] = "Memory allocation failed.\n";
	err_msg[MULTILINE_QUOTE] = "Undefined case : multiline quote command.\n";
	err_msg[MULTILINE_DQUOTE] = "Undefined case : multiline double quote command.\n";
	err_msg[MULTILINE_BSLASH] = "Undefined case : multiline back slash command.\n";
	err_msg[SYNTAX_SEMI] = "bash: syntax error near unexpected token `;'\n";
	err_msg[SYNTAX_PIPE] = "bash: syntax error near unexpected token `|'\n";
	err_msg[SYNTAX_DGREAT] = "bash: syntax error near unexpected token `>>'\n";
	err_msg[SYNTAX_GREAT] = "bash: syntax error near unexpected token `>'\n";
	err_msg[SYNTAX_LESS] = "bash: syntax error near unexpected token `<'\n";
}

void	*error(t_err *err, t_err_code code, void **ptr, void (*free_fct)(void **))
{
	if (free_fct && ptr)
		free_fct(ptr);
	ft_putstr_fd(err->message[code], STDERR_FILENO);
	// set exit_status
		// TODO:
	return(NULL);
}

int	main(void)
{
	unsigned int	i;
	char			buf[4096];
	t_err			err;
	char 			*err_msg[10];	// TODO:

	init_msg(err_msg);
	err = (t_err){err_msg, 0};


	// (void)argv;
	// printf("test 1 = %d\n", test(&err, argc));
	// printf("test 2 = %s\n", test2(&err, argc));

	// // error(&err, NULL);
	// exit(EXIT_SUCCESS);

	// while (1)
	// {
		i = 0;
		while (i < 4096)
		{
			buf[i] = '\0';
			i++;
		}
		ft_putstr("prompt>");
		if (read(STDIN_FILENO, buf, 4096) > 0)
		{
			if(!(lexer(buf, &err)))
			{
				printf("lexer casse2\n");
				return (EXIT_FAILURE);
				// continue ;
			}
		}
		else
		{
			printf(" tu c pa fer d pro gramme idiot bete de moche\n");
			return (EXIT_FAILURE);
		}
	// }
	return (EXIT_SUCCESS);
}
