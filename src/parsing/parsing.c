/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/21 12:38:47 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**get_close_subshell(t_list *tokens)
{
	t_list	**current;
	int		level;
	t_token	*token;

	current = &tokens;
	level = 0;
	while (*current)
	{
		token = (*current)->content;
		if (token->type == SUBSHELL && ft_strcmp(token->value, "(") == 0)
			level++;
		else if (token->type == SUBSHELL && ft_strcmp(token->value, ")") == 0)
		{
			level--;
			if (level == 0)
				return (current);
		}
		current = &(*current)->next;
	}
	return (NULL);
}

// TODO: 'fregrg && echo salut || erhger'
t_btree	*new_btree(t_list *tokens)
{
	t_btree	*btree;
	t_list	**current;

	btree = ft_btree_new(tokens);
	current = &tokens;
	while (*current && ((t_token *)(*current)->content)->type != LOGICAL)
	{
		if (((t_token *)(*current)->content)->type == SUBSHELL)
			current = &(*get_close_subshell(*current))->next;
		else
			current = &(*current)->next;
	}
	if (!*current)
		return (btree);
	if (ft_strcmp(((t_token *)(*current)->content)->value, "&&") == 0)
		btree->left = new_btree((*current)->next);
	else
		btree->right = new_btree((*current)->next);
	free_token((*current)->content);
	ft_free_set((void **) current, NULL);
	return (btree);
}

void	parse_btree(t_data *data, char *input)
{
	t_list	*tokens;

	tokens = tokenize(input);
	if (check_unexpected(data, tokens))
	{
		ft_lstclear(&tokens, free_token);
		data->last_status = 2;
		data->btree = NULL;
		return ;
	}
	data->btree = new_btree(tokens);
}
