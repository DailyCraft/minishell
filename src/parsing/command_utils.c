/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:02:36 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/16 14:48:56 by dvan-hum         ###   ########.fr       */
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

int	btree_is_empty(t_btree *btree)
{
	t_command	*command;

	if (!btree)
		return (1);
	if (btree->left || btree->right)
		return (0);
	command = btree->content;
	return (command->type == COMMAND && command->argc == 0
		&& command->pipe == NULL && command->redirects == NULL);
}
