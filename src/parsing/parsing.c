/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 09:23:43 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_argv(t_command *command)
// {
// 	int	i;

// 	i = 0;
// 	while (command->argv[i])
// 	{
// 		printf("argv %d = %s\n",i , command->argv[i]);
// 		i++;
// 	}
// }

t_btree	*parse_input(t_data *data, char *input)
{
	t_command	*command;

	if (command_new(data, &command, input) == -1)
	{
		data->last_status = 1;
		return (NULL);
	}
	data->btree = ft_btree_new(command);
	return (data->btree);
}
