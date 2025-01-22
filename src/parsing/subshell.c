/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/22 08:10:19 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	subshell_level(t_list *lst)
{
	t_token	*token;
	int		level;

	level = 0;
	while (lst)
	{
		token = lst->content;
		if (token->type == SUBSHELL && ft_strcmp(token->value, "(") == 0)
			level++;
		else if (token->type == SUBSHELL && ft_strcmp(token->value, ")") == 0)
		{
			if (level == 0)
				return (-1);
			level--;
		}
		lst = lst->next;
	}
	return (level);
}

t_list	**get_close_subshell(t_list **tokens)
{
	int		level;
	t_token	*token;

	level = 0;
	while (*tokens)
	{
		token = (*tokens)->content;
		if (token->type == SUBSHELL && ft_strcmp(token->value, "(") == 0)
			level++;
		else if (token->type == SUBSHELL && ft_strcmp(token->value, ")") == 0)
		{
			level--;
			if (level == 0)
				return (tokens);
		}
		tokens = &(*tokens)->next;
	}
	return (NULL);
}
