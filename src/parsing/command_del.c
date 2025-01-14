/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:02:36 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/14 14:39:38 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_delone(t_command *command)
{
	t_command	*pipe;

	pipe = command->pipe;
	ft_lstclear(&command->redirects, free);
	if (command->type == SUB_SHELL)
		free(command->command_line);
	else if (command->argc > 0)
		ft_free_split(command->argv);
	free(command);
	return (pipe);
}

void	clear_command(void *command)
{
	while (command)
		command = command_delone(command);
}
