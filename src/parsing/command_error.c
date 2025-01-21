/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:27:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/21 16:12:41 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexpected_token(t_data *data, char *token)
{
	error_msg(data, "%m: syntax error near unexpected token `%s'",
		(char *[]){token});
}

bool	check_subshell_lvl(t_data *data, t_list *lst)
{
	int	level;

	level = subshell_level(lst);
	if (level > 0)
	{
		error_msg(data, "%m: syntax error: unclosed parenthesis", NULL);
		return (false);
	}
	else if (level < 0)
		return (unexpected_token(data, ")"), false);
	return (true);
}

bool	check_tokens(t_data *data, t_list *lst)
{
	t_token	*token;
	t_token	*previous;

	previous = NULL;
	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type != ARG && token->type != SUBSHELL)
			if (!check_valid_type(data, lst, token))
				return (false);
		if (token->type == SUBSHELL)
			if (!check_valid_subshell(data, lst, previous, token))
				return (false);
		previous = token;
		lst = lst->next;
	}
	return (true);
}

bool	check_unexpected(t_data *data, t_list *lst)
{
	if (!check_tokens(data, lst))
		return (true);
	if (!check_subshell_lvl(data, lst))
		return (true);
	return (false);
}
