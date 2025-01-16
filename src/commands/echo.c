/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:29:29 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/16 15:06:28 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (i > 1 && arg[i] == 0);
}

static int	parse_options(int *argc, char ***argv)
{
	int	i;

	i = 0;
	while (i < *argc && is_n((*argv)[i]))
		i++;
	*argc -= i;
	*argv += i;
	return (i);
}

int	echo_command(int argc, char **argv)
{
	int	options_count;
	int	i;

	argc--;
	argv++;
	options_count = parse_options(&argc, &argv);
	i = 0;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	if (!options_count)
		printf("\n");
	return (0);
}
