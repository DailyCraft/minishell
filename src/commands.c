/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:31:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/02 10:15:37 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_msg(char *program, char *desc)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(desc, 2);
}

void	cd_command(t_data *data, int argc, char **argv)
{
	char	*home;

	(void) data;
	if (argc == 0)
	{
		home = getenv("HOME");
		if (home && home[0] != 0 && chdir(home) == -1)
			error_msg("cd", home);
	}
	else if (argc == 1)
	{
		if (chdir(argv[0]) == -1)
			error_msg("cd", argv[0]);
	}
}
