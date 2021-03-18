/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:56:20 by agautier          #+#    #+#             */
/*   Updated: 2021/03/16 19:00:16 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	t_list *tokens                                                                    |
**	             0x0a                              0x0b                              0x0c                              0x0d
**	┌----------------------------┐    ┌----------------------------┐    ┌----------------------------┐    ┌----------------------------┐
**	|                            |    |                            |    |                            |    |                            |
**	|  - data = t_token          |    |  - data = t_token          |    |  - data = t_token          |    |  - data = t_token          |
**	|      - e_type = TOKEN_WORD | -► |      - e_type = TOKEN_WORD | -► |      - e_type = TOKEN_SEMI | -► |      - e_type = TOKEN_WORD |
**	|      - data = "echo"       |    |      - data = "antoine"    |    |      - data = ";"          |    |      - data = "ls"         |
**	|  - next = 0x0b             |    |  - next = 0x0c             |    |  - next = 0x0d             |    |  - next = NULL             |
**	|                            |    |                            |    |                            |    |                            |
**	└----------------------------┘    └----------------------------┘    └----------------------------┘    └----------------------------┘
*/

/*
**	Priorites:
**		- TOKEN_SEMI ;
**		- TOKEN_PIPE |
**		- TOKEN_DGREAT + TOKEN_WORD => TOKEN_REDIR [ >> , filename ]
**		- TOKEN_GREAT + TOKEN_WORD => TOKEN_REDIR [ > , filename ]
**		- TOKEN_LESS + TOKEN_WORD => TOKEN_REDIR [ < , filename ]
**		- TOKEN_WORD... => TOKEN_COMMAND [ TOKEN_WORD, TOKEN_WORD... ]
*/

static int	cmp_lstdata_data(t_token *lstdata, int *data)
{
	if ((int)(lstdata->e_type) == *data)
		return (0);
	return (1);
}

void	parse_tokens(t_list *tokens)
{
	const int		prios[5] = {TOKEN_SEMI, TOKEN_PIPE, TOKEN_DGREAT, TOKEN_GREAT, TOKEN_LESS};
	void			(*const check_f[5])(t_list*, void*, unsigned int) = {check_semi, check_pipe, check_dgreat, check_great, check_less};
	unsigned int	i;

	i = 0;
	while (i < 5)
	{
		my_list_foreach_if(tokens, check_f[i], (void *)&(prios[i]), cmp_lstdata_data);
		i++;
	}
}
