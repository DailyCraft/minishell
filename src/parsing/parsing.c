/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/19 13:52:49 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_btree(t_btree *btree)
// {
// 	printf("base content = %s\n", (char *)btree->content);
// 	if (btree->left)
// 		printf("left content = %s\n", (char *)btree->left->content);
// 	else
// 		printf("left = %s\n", (char *)btree->left);
// 	if (btree->right)
// 		printf("right content = %s\n", (char *)btree->right->content);
// 	else
// 		printf("right = %s\n", (char *)btree->right);
// }

t_btree	*set_btree(char *input)
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
