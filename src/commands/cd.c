/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:48:39 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/10 14:01:14 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	component_len(char *path)
{
	char	*chr;

	chr = ft_strchr(path, '/');
	if (chr)
		return (chr - path);
	return (ft_strlen(path));
}

static char	*resolve_cdpath(t_data *data, char *child)
{
	char	*path;
	char	**paths;
	int		i;

	if (ft_getenv(data, "CDPATH") && child[0] != '/'
		&& ft_strncmp(child, ".", component_len(child)) != 0
		&& ft_strncmp(child, "..", component_len(child)) != 0)
	{
		paths = ft_split(ft_getenv(data, "CDPATH"), ':');
		i = 0;
		while (paths[i])
		{
			path = ft_strsjoin((const char *[]){paths[i], "/", child, NULL});
			if (!path || (access(path, F_OK) == 0 && isdir(path)))
				return (ft_free_split(paths), path);
			free(path);
			i++;
		}
		ft_free_split(paths);
	}
	return (ft_strdup(child));
}

static char	*from_env(t_data *data, char *env, char *error)
{
	if (ft_getenv(data, env) == NULL)
	{
		err_ms_prog_msg(data, "cd", error);
		return (NULL);
	}
	return (ft_getenv(data, env));
}

static int	cd_chdir(t_data *data, char *arg)
{
	char	*path;

	if (!arg)
		path = from_env(data, "HOME", "HOME not set");
	else if (ft_strcmp(arg, "-") == 0)
		path = from_env(data, "OLDPWD", "OLDPWD not set");
	else
		path = resolve_cdpath(data, arg);
	if (!path)
		return (1);
	if (path[0] != 0 && chdir(path) == -1)
	{
		err_ms_prog_msg_no(data, "cd", path);
		if (arg && ft_strcmp(arg, "-") != 0)
			free(path);
		return (1);
	}
	if (arg && ft_strcmp(arg, "-") != 0)
		free(path);
	return (0);
}

int	cd_command(t_data *data, int argc, char **argv)
{
	char	*path;

	if (argc > 2)
	{
		err_ms_prog_msg(data, "cd", "too many arguments");
		return (1);
	}
	else if (cd_chdir(data, argv[1]) == 1)
		return (1);
	if (ft_getenv(data, "PWD"))
		ft_setenv(data, "OLDPWD", ft_getenv(data, "PWD"), 1);
	path = getcwd(NULL, 0);
	ft_setenv(data, "PWD", path, 1);
	free(path);
	return (0);
}
