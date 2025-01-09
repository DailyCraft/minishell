/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/09 14:06:08 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	run_external(t_data *data, t_command *command, int in_fork)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;
	char	*program;

	path = resolve_path(data, command->argv[0]);
	if (!path)
		return (error_msg(command->argv[0], "command not found"), 127);
	if (in_fork)
	{
		pid = fork();
		if (pid != 0)
		{
			free(path);
			return (waitpid(pid, &status, 0), status);
		}
	}
	envp = flat_envp(data);
	program = data->program;
	free_data(data);
	execve(path, command->argv, envp);
	exit((errno_msg(program, command->argv[0]), 126));
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

static int	setup_redirects(t_data *data, t_command *command)
{
	char	*heredoc;
	int		output;
	int		input;

	heredoc = get_heredoc(command);
	if (heredoc != NULL)
	{
		errno_safe(data, "write", write(0, heredoc, ft_strlen(heredoc)));
		free(heredoc);
	}
	input = open_input(data, command);
	if (input == -1)
		return (-1);
	else if (input != 0)
		(dup2(input, STDIN_FILENO), close(input));
	output = open_output(data, command);
	if (output == -1)
		return (-1);
	else if (output != 1)
		(dup2(output, STDOUT_FILENO), close(output));
	return (0);
}

int	run_command(t_data *data, t_command *command, int in_fork)
{
	if (setup_redirects(data, command) == -1)
		return (1);
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
