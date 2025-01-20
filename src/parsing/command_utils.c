/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:02:36 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 09:55:41 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(void *command)
{
	t_command	*current;

	current = command;
	while (current)
	{
		ft_lstclear(&current->redirects, free);
		if (current->type == SUB_SHELL)
			free(current->command_line);
		else
			ft_lstclear(&current->args, free);
		ft_free_set((void **) &current, current->pipe);
	}
}

bool	is_empty_command_line(char *command_line)
{
	size_t	i;

	i = 0;
	while (ft_isspace(command_line[i]))
		i++;
	return (command_line[i] == 0);
}
