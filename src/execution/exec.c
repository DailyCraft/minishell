/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/10 14:21:59 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data, t_command *command)
{
	int	backup_fds[2];
	int	status;

	if (!command->pipe)
	{
		backup_fds[0] = dup(STDIN_FILENO);
		backup_fds[1] = dup(STDOUT_FILENO);
		status = run_command(data, command, 1);
		dup2(backup_fds[0], STDIN_FILENO);
		dup2(backup_fds[1], STDOUT_FILENO);
		(close(backup_fds[0]), close(backup_fds[1]));
	}
	else
		status = execute_pipeline(data, command, 0);
	data->last_status = status;
	return (status);
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
