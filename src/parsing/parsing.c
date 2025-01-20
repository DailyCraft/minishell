/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 12:03:26 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_btree	*set_btree(char *input)
{
	t_btree	*btree;
	char	*command;
	int		i;

	i = find_logical(input);
	command = ft_substr(input, 0, i);
	btree = ft_btree_new(command);
	if (input[i] == '&')
		btree->left = set_btree(input + i + 2);
	else if (input[i] == '|')
		btree->right = set_btree(input + i + 2);
	return (btree);
}

void	parse_btree(t_data *data, char *input)
{
	if (error_cmd(data, input))
	{
		data->last_status = 2;
		data->btree = NULL;
		return ;
	}
	data->btree = set_btree(input);
}
