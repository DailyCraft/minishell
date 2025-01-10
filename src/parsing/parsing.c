/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/10 11:42:06 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	print_argv(t_command *command)
{
	int	i;

	i = 0;
	while (command->argv[i])
		printf("%s\n", command->argv[i++]);
}*/

t_btree	*parse_input(t_data *data, char *input)
{
	t_command	*command = command_new(input);
	if (command->type == COMMAND && command->argc == 0)
		return (NULL);
	//print_argv(command);
	t_btree		*btree = ft_btree_new(command);
	data->btree = btree;
	return (btree);
}
