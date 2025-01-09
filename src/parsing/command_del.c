/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:02:36 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 15:43:08 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_delone(t_command *command)
{
	t_command	*pipe;

	pipe = command->pipe;
	ft_lstclear(&command->inputs, free);
	ft_lstclear(&command->outputs, free);
	if (command->type == COMMAND)
		ft_free_split(command->argv);
	else
		free(command->command_line);
	free(command);
	return (pipe);
}

void	clear_command(void *command)
{
	while (command)
		command = command_delone(command);
}
