/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/04 17:36:16 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_external(t_data *data, t_command *command, int in_fork)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	if (in_fork)
	{
		pid = fork();
		if (pid != 0)
			return (waitpid(pid, &status, 0), status);
	}
	path = resolve_path(data, command->argv[0]);
	if (path)
	{
		envp = flat_envp(data);
		free_data(data);
		execve(path, command->argv, envp);
		return (errno_msg(data->program, command->argv[0]), 126);
	}
	else
	{
		free_data(data);
		return (error_msg(command->argv[0], "command not found"), 127);
	}
}

static int	run_sub_shell(t_data *data, char *command_line, int in_fork)
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
	// free_btree(data)
	// populate_btree(data, command_line);
	// read btree
	return (0);
}

int	run_command(t_data *data, t_command *command, int in_fork)
{
	int	output;

	output = open_output(data, command);
	if (output == -1)
		return (1);
	else if (output != 1)
		dup2(output, STDOUT_FILENO);
	// TODO: close output
	if (command->type == SUB_SHELL)
		return (run_sub_shell(data, command->command_line, in_fork));
	if (ft_strcmp(command->argv[0], "cd") == 0)
		return (cd_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "echo") == 0)
		return (echo_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "env") == 0)
		return (env_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "exit") == 0)
		return (exit_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "export") == 0)
		return (export_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "pwd") == 0)
		return (pwd_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "unset") == 0)
		return (unset_command(data, command->argc, command->argv));
	return (run_external(data, command, in_fork));
}

int	execute(t_data *data, t_command *command)
{
	int	status;

	if (!command->pipe)
		status = run_command(data, command, 1);
	else
		status = execute_pipeline(data, command, 0);
	data->last_status = status;
	return (status);
}
