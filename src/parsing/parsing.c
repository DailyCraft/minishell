/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 16:28:07 by dvan-hum         ###   ########.fr       */
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

void	parse_btree(t_data *data, char *input)
{
	if (error_cmd(data, input))
	{
		data->last_status = 2;
		data->btree = NULL;
	}
	else
		data->btree = ft_btree_new(ft_strdup(input));
}
