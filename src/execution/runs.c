/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:05:54 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/24 11:44:25 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_external(t_data *data, t_command *command, char *path)
{
	char	**envp;
	char	**argv;
	char	*program;
	bool	is_tty;

	ft_setenv(data, "_", path);
	envp = ft_lsttoa(data->envp, flat_envp);
	argv = ft_lsttoa(command->args, (char *(*)(void *)) ft_strdup);
	program = data->program;
	is_tty = data->is_tty;
	free_data(data, data->command);
	execve(path, argv, envp);
	program = ft_basename(program);
	error_msg(NULL, "%s: %s: %n", (char *[]){program, path});
	free(program);
	free(path);
	ft_free_split(argv);
	ft_free_split(envp);
	free_gnl(is_tty);
	exit(126);
}

static int	check_path(t_data *data, char *arg, char **path)
{
	*path = resolve_path(data, arg);
	if (*path)
		return (0);
	if (errno == ESRCH)
		return (error_msg(data, "%m: %s: command not found",
				(char *[]){arg}), 127);
	if (errno == ENOENT)
		return (error_msg(data, "%m: %s: %n", (char *[]){arg}), 127);
	if (errno == EISDIR)
		return (error_msg(data, "%m: %s: %n", (char *[]){arg}), 126);
	return (error_msg(data, "%m: %s: %n", (char *[]){arg}), 1);
}

int	run_external(t_data *data, t_command *command, int in_fork)
{
	pid_t	pid;
	int		status;
	char	*path;

	status = check_path(data, command->args->content, &path);
	if (status != 0)
		return (status);
	if (in_fork)
	{
		pid = fork();
		if (pid != 0)
		{
			free(path);
			return (wait_process(pid, 1));
		}
		signals(0);
	}
	return (child_external(data, command, path));
}

int	run_sub_shell(t_data *data, t_command *command, int in_fork)
{
	pid_t		pid;
	int			last_status;

	if (in_fork)
	{
		pid = fork();
		if (pid != 0)
			return (wait_process(pid, 1));
	}
	free_line(&data->line);
	data->line = new_line(command->tokens, true);
	command->tokens = NULL;
	free_command(data->command);
	iterate_line(data);
	last_status = data->last_status;
	close(STDIN_FILENO);
	free_gnl(data->is_tty);
	free_data(data, NULL);
	exit(last_status);
}
