/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:50:15 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/23 22:22:20 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_data *data, t_command *command)
{
	int	status;

	if (!apply_heredocs(data, command))
		return (130);
	if (!command->pipe)
	{
		command->fds.backups[0] = dup(STDIN_FILENO);
		command->fds.backups[1] = dup(STDOUT_FILENO);
		status = run_command(data, command, 1);
		dup2(command->fds.backups[0], STDIN_FILENO);
		dup2(command->fds.backups[1], STDOUT_FILENO);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		status = execute_pipeline(data, command, 0);
		signals(1);
	}
	if (command->type != COMMAND || command->args || command->redirects)
		data->last_status = status;
	if (command->type == COMMAND && command->args)
		ft_setenv(data, "_", ft_lstlast(command->args)->content);
	else if (command->type == COMMAND)
		ft_setenv(data, "_", NULL);
	return (status);
}

static bool	setup_redirects(t_data *data, t_command *command)
{
	bool	result;
	
	result = apply_redirections(data, command);
	if (result)
	{
		if (command->fds.last_input == HERE_DOC)
			dup2(command->fds.heredoc, STDIN_FILENO);
		else if (command->fds.last_input == INPUT)
			dup2(command->fds.input, STDIN_FILENO);
		if (command->fds.output > 0)
			dup2(command->fds.output, STDOUT_FILENO);
	}
	if (command->fds.input > 0)
		close(command->fds.input);
	if (command->fds.heredoc > 0)
		close(command->fds.heredoc);
	if (command->fds.output > 0)
		close(command->fds.output);
	return (result);
}

int	run_command(t_data *data, t_command *command, int in_fork)
{
	if (!setup_redirects(data, command))
		return (EXIT_FAILURE);
	if (command->args == NULL)
		return (EXIT_SUCCESS);
	if (command->type == SUB_SHELL)
		return (run_sub_shell(data, command, in_fork));
	if (ft_strcmp(command->args->content, "cd") == 0)
		return (cd_command(data, command->args));
	else if (ft_strcmp(command->args->content, "echo") == 0)
		return (echo_command(command->args));
	else if (ft_strcmp(command->args->content, "env") == 0)
		return (env_command(data));
	else if (ft_strcmp(command->args->content, "exit") == 0)
		return (exit_command(data, command, command->args));
	else if (ft_strcmp(command->args->content, "export") == 0)
		return (export_command(data, command->args));
	else if (ft_strcmp(command->args->content, "pwd") == 0)
		return (pwd_command());
	else if (ft_strcmp(command->args->content, "unset") == 0)
		return (unset_command(data, command->args));
	return (run_external(data, command, in_fork));
}
