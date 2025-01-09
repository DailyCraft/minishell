/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:48:39 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/07 09:42:40 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_command(t_data *data, int argc, char **argv)
{
	char	*path;

	if (argc == 1)
	{
		path = ft_getenv(data, "HOME");
		if (path && path[0] != 0 && chdir(path) == -1)
		{
			errno_msg("cd", path);
			return (1);
		}
	}
	else if (argc == 2 && chdir(argv[1]) == -1)
	{
		errno_msg("cd", argv[1]);
		return (1);
	}
	if (ft_getenv(data, "PWD"))
		ft_setenv(data, "OLDPWD", ft_getenv(data, "PWD"), 1);
	path = getcwd(NULL, 0);
	ft_setenv(data, "PWD", path, 1);
	free(path);
	return (0);
}
