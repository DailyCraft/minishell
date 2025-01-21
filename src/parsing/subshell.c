/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 12:19:11 by dvan-hum         ###   ########.fr       */
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
			level--;
		lst = lst->next;
	}
	return (level);
}
