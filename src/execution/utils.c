/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:47:24 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/04 17:25:03 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_output(t_data *data, t_command *command)
{
	int		fd;
	t_list	*lst;
	int		flag;

	lst = command->outputs;
	fd = 1;
	while (lst)
	{
		if (fd != 1)
			close(fd);
		if (((char *) lst->content)[0] == 1)
			flag = O_TRUNC;
		else
			flag = O_APPEND;
		fd = open(lst->content + 1, O_CREAT | O_WRONLY | flag, 0664);
		if (fd < 0)
		{
			errno_msg(data->program, lst->content + 1);
			return (-1);
		}
		lst = lst->next;
	}
	return (fd);
}

char	*resolve_path(t_data *data, char *bin)
{
	char	*path_env;
	char	*path;
	char	**paths;
	int		i;

	path_env = ft_getenv(data, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strsjoin((const char *[]){paths[i], "/", bin, NULL});
		if (!path || access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free_split(paths);
	if (access(bin, F_OK) == 0)
		return (bin);
	return (NULL);
}
