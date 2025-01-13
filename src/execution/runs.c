/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:05:54 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/13 11:52:26 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_external(t_data *data, t_command *command, char *path)
{
	char	**envp;
	char	**argv;
	char	*program;

	envp = flat_envp(data);
	argv = strsdup(command->argv);
	program = data->program;
	free_data(data);
	execve(path, argv, envp);
	error_msg(NULL, "%s: %s: %n", (char *[]){program, path});
	free(path);
	ft_free_split(argv);
	ft_free_split(envp);
	free_gnl();
	exit(126);
}

int	run_external(t_data *data, t_command *command, int in_fork)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = resolve_path(data, command->argv[0]);
	if (!path)
	{
		if (errno == ESRCH)
			return (error_msg(data, "%s: command not found",
					(char *[]){command->argv[0]}), 127);
		if (errno == ENOENT)
			return (error_msg(data, "%m: %s: %n",
					(char *[]){command->argv[0]}), 127);
		if (errno == EISDIR)
			return (error_msg(data, "%m: %s: %n",
					(char *[]){command->argv[0]}), 126);
	}
	if (in_fork)
	{
		pid = fork();
		if (pid != 0)
		{
			free(path);
			return (waitpid(pid, &status, 0), status);
		}
	}
	return (child_external(data, command, path));
}

int	run_sub_shell(t_data *data, char *command_line, int in_fork)
{
	pid_t	pid;
	int		status;

	if (in_fork)
	{
		pid = fork();
		if (pid != 0)
			return (waitpid(pid, &status, 0), status);
	}
	(void) data;
	(void) command_line;
	ft_btree_clear(&data->btree, clear_command);
	parse_input(data, command_line);
	iterate_btree(data);
	free_data(data);
	exit(0);
}
