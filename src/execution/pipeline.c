/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:51:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/23 23:17:02 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_process(t_data *data, t_command *command, int input, int *fds)
{
	int	status;

	if (input != 0)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (command->pipe)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	status = run_command(data, command, 0);
	free_gnl(data->is_tty);
	free_data(data, data->command);
	exit(status);
}

void	close_heredocs(t_command *except)
{
	t_command	*command;

	command = except;
	while (command)
	{
		if (command != except && command->fds.heredoc > 0)
			close(command->fds.heredoc);
		command = command->pipe;
	}
}

int	execute_pipeline(t_data *data, t_command *command, int input_fd)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (command->pipe)
		errno_safe(data, "pipe", pipe(fds));
	pid = fork();
	if (pid == 0)
	{
		close_heredocs(command);
		signals(0);
		return (child_process(data, command, input_fd, fds));
	}
	if (command->fds.heredoc > 0)
		close(command->fds.heredoc);
	if (input_fd != 0)
		close(input_fd);
	if (!command->pipe)
		return (wait_process(pid, 0));
	close(fds[1]);
	status = execute_pipeline(data, command->pipe, fds[0]);
	waitpid(pid, NULL, 0);
	return (status);
}
