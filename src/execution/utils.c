/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:47:24 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/10 14:28:39 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isdir(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

char	*resolve_path(t_data *data, char *child)
{
	char	*path;
	char	**paths;
	int		i;

	if (ft_strchr(child, '/') != NULL || !ft_getenv(data, "PATH"))
	{
		if (access(child, F_OK) == -1)
			return (errno = ENOENT, NULL);
		if (isdir(child))
			return (errno = EISDIR, NULL);
		return (ft_strdup(child));
	}
	paths = ft_split(ft_getenv(data, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strsjoin((const char *[]){paths[i], "/", child, NULL});
		if (!path || (access(path, F_OK) == 0 && !isdir(path)))
			return (ft_free_split(paths), path);
		free(path);
		i++;
	}
	return (ft_free_split(paths), errno = ESRCH, NULL);
}
