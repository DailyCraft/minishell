/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:29:29 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/20 09:57:41 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (i > 1 && arg[i] == 0);
}

static int	parse_options(t_list **args)
{
	int	i;

	i = 0;
	while (*args && is_n((*args)->content))
	{
		*args = (*args)->next;
		i++;
	}
	return (i);
}

int	echo_command(t_list *args)
{
	int		options_count;

	args = args->next;
	options_count = parse_options(&args);
	while (args)
	{
		printf("%s", (char *) args->content);
		if (args->next)
			printf(" ");
		args = args->next;
	}
	if (!options_count)
		printf("\n");
	return (EXIT_SUCCESS);
}
