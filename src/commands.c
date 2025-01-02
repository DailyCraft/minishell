/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 09:31:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/02 13:49:32 by dvan-hum         ###   ########.fr       */
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
	char	*path;

	if (argc == 0)
	{
		path = ft_getenv(data, "HOME");
		if (path && path[0] != 0 && chdir(path) == -1)
			error_msg("cd", path);
	}
	else if (argc == 1)
	{
		if (chdir(argv[0]) == -1)
			error_msg("cd", argv[0]);
	}
	if (ft_getenv(data, "PWD"))
		ft_setenv(data, "OLDPWD", ft_getenv(data, "PWD"), 1);
	path = getcwd(NULL, 0);
	ft_setenv(data, "PWD", path, 1);
	free(path);
}
