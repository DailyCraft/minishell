/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/14 16:11:44 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	print_argv(t_command *command)
{
	int	i;

	i = 0;
	while (command->argv[i])
	{
		printf("argv %d = %s\n",i , command->argv[i]);
		i++;
	}
}*/

t_btree	*parse_input(t_data *data, char *input)
{
	t_command	*command;
	t_btree		*btree;

	command = command_new(data, input);
	if (command->type == COMMAND && command->argc == 0)
		return (NULL);
	//print_argv(command);
	btree = ft_btree_new(command);
	data->btree = btree;
	return (btree);
}
