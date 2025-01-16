/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/16 17:05:25 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data, t_command *command)
{
	int	backup_fds[2];
	int	status;

	if (apply_heredocs(data, command) == -1)
		return (130);
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
	{
		signal(SIGINT, SIG_IGN);
		status = execute_pipeline(data, command, 0);
		signals(1);
	}
	data->last_status = status;
	return (status);
}

static int	setup_redirects(t_data *data, t_command *command)
{
	if (apply_redirections(data, command) == -1)
		return (-1);
	if (command->fds.last_input == HERE_DOC)
		dup2(command->fds.heredoc, STDIN_FILENO);
	else if (command->fds.last_input == INPUT)
		dup2(command->fds.input, STDIN_FILENO);
	if (command->fds.output != 0)
		dup2(command->fds.output, STDOUT_FILENO);
	if (command->fds.input != 0)
		close(command->fds.input);
	if (command->fds.heredoc != 0)
		close(command->fds.heredoc);
	if (command->fds.output != 0)
		close(command->fds.output);
	return (0);
}

int	run_command(t_data *data, t_command *command, int in_fork)
{
	if (setup_redirects(data, command) == -1)
		return (1);
	if (command->argc == 0)
		return (0);
	if (command->type == SUB_SHELL)
		return (run_sub_shell(data, command->command_line, in_fork));
	if (ft_strcmp(command->argv[0], "cd") == 0)
		return (cd_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "echo") == 0)
		return (echo_command(command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "env") == 0)
		return (env_command(data));
	else if (ft_strcmp(command->argv[0], "exit") == 0)
		return (exit_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "export") == 0)
		return (export_command(data, command->argc, command->argv));
	else if (ft_strcmp(command->argv[0], "pwd") == 0)
		return (pwd_command());
	else if (ft_strcmp(command->argv[0], "unset") == 0)
		return (unset_command(data, command->argc, command->argv));
	return (run_external(data, command, in_fork));
}
