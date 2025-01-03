/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 08:18:47 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 11:53:02 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_bin(t_data *data, char *bin)
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

static char	**parse_args(char *command, int *len)
{
	char	**split;

	split = ft_split(command, ' ');
	*len = 0;
	while (split[*len])
		(*len)++;
	return (split);
}

static int	execute_external(t_data *data, char *bin, char **argv)
{
	char	*path;
	char	**envp;

	path = find_bin(data, bin);
	if (path)
	{
		envp = flat_envp(data);
		ft_lstclear(&data->envp, free_env);
		execve(path, argv, envp);
		errno_msg(data->program, bin);
		return (126);
	}
	else
	{
		ft_lstclear(&data->envp, free_env);
		error_msg(bin, "command not found");
		return (127);
	}
}

static int	execute_command(t_data *data, char *bin, int argc, char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (ft_strcmp(bin, "pwd") == 0)
			return (pwd_command(data, argc, argv));
		if (ft_strcmp(bin, "echo") == 0)
			return (echo_command(data, argc, argv));
		return (execute_external(data, bin, argv));
	}
	else
	{
		waitpid(pid, &status, 0);
		return (status);
	}
}

int	execute_line(t_data *data, char *command_line)
{
	int		argc;
	char	**argv;
	int		result;

	argv = parse_args(command_line, &argc);
	result = execute_command(data, argv[0], argc, argv);
	ft_free_split(argv);
	return (result);
}
