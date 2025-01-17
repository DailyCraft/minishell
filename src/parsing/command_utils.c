/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:02:36 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 14:00:10 by dvan-hum         ###   ########.fr       */
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
		else if (current->argc > 0)
			ft_free_split(current->argv);
		ft_free_set((void **) &current, current->pipe);
	}
}

int	is_empty_command_line(char *command_line)
{
	size_t	i;

	i = 0;
	while (ft_isspace(command_line[i]))
		i++;
	return (command_line[i] == 0);
}
