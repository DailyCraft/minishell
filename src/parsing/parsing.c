/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/07 11:56:13 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*parse_input(char *input)
{
	t_command	*command = ft_calloc(1, sizeof(t_command));
	command->type = COMMAND;
	command->argc = 0;
	command->argv = ft_split(input, ' ');
	while (command->argv[command->argc])
		command->argc++;
	t_btree		*btree = ft_btree_new(command);
	return (btree);
}
