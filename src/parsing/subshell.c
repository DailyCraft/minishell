/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 15:57:32 by cgrasser         ###   ########.fr       */
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
