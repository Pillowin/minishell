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

// echo "Je \ suis ant\"oine"

int	main(void)
{
	char buf[4096];
	unsigned int i;

	i = 0;
	while (i < 4096)
	{
		buf[i] = '\0';
		i++;
	}
	ft_putstr("prompt>");
	if (read(STDIN_FILENO, buf, 4096) > 0)
		lexer(buf);
	else
	{
		printf(" tu c pa fer d pro gramme idiot bete de moche\n");
		return (EXIT_FAILURE);
	}
	// read sur stdin
	return (EXIT_SUCCESS);
}
