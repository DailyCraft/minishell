/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:15:55 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/07 09:54:05 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_new(enum e_type type, t_list *inputs, t_list *outputs)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->type = type;
	command->inputs = inputs;
	command->outputs = outputs;
	command->pipe = NULL;
	return (command);
}

void	set_command_line(t_command *command, char *command_line)
{
	command->command_line = command_line;
}

void	set_command_argv(t_command *command, char **argv)
{
	command->argv = argv;
}

t_command	*command_last(t_command *command)
{
	if (!command)
		return (NULL);
	while (command->pipe)
		command = command->pipe;
	return (command);
}

void	command_add_pipe(t_command **command, t_command *pipe)
{
	if (!*command)
		*command = pipe;
	else
		command_last(*command)->pipe = pipe;
}
