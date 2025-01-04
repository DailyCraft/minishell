/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:51:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/04 17:36:46 by dvan-hum         ###   ########.fr       */
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
	free_data(data);
	exit(status);
}

int	execute_pipeline(t_data *data, t_command *command, int input_fd)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	if (command->pipe)
		errno_safe(data, "pipe", pipe(fds));
	pid = fork();
	if (pid != 0)
	{
		if (input_fd != 0)
			close(input_fd);
		if (command->pipe)
		{
			close(fds[1]);
			return (execute_pipeline(data, command->pipe, fds[0]));
		}
		waitpid(pid, &status, 0);
		return (status);
	}
	return (child_process(data, command, input_fd, fds));
}
