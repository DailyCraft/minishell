/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:42:11 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/24 12:28:03 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_valid_type(t_data *data, t_list *lst,
	t_token *previous, t_token *token)
{
	t_token	*token_next;

	if (!previous && (token->type == LOGICAL || token->type == PIPE))
		return (unexpected_token(data, token->value), false);
	if (!lst->next)
	{
		if (token->type == REDIRECT)
			return (unexpected_token(data, "newline"), false);
		else
			return (error_msg(data,
					"%m: syntax error: unexpected end of file", NULL), false);
	}
	else
	{
		token_next = lst->next->content;
		if (token->type == REDIRECT && token_next->type != ARG)
			return (unexpected_token(data, token_next->value), false);
		else if (token_next->type == LOGICAL || token_next->type == PIPE)
			return (unexpected_token(data, token_next->value), false);
	}
	return (true);
}

bool	open_sub(t_data *data, t_token *previous, t_token *token_next)
{
	if (previous && previous->type == ARG)
	{
		if (token_next)
			return (unexpected_token(data, token_next->value), false);
		else
			return (unexpected_token(data, "newline"), false);
	}
	if (token_next && token_next->type != ARG && (token_next->type != SUBSHELL
			|| (token_next->type == SUBSHELL
				&& ft_strcmp(token_next->value, ")") == 0)))
		return (unexpected_token(data, token_next->value), false);
	return (true);
}

bool	check_valid_subshell(t_data *data, t_list *lst,
	t_token *previous, t_token *token)
{
	t_token	*token_next;

	token_next = NULL;
	if (lst->next)
		token_next = lst->next->content;
	if (ft_strcmp(token->value, "(") == 0)
	{
		if (!open_sub(data, previous, token_next))
			return (false);
	}
	else
	{
		if (!previous || (previous->type != ARG && previous->type != SUBSHELL))
			return (unexpected_token(data, token->value), false);
		if (token_next && (token_next->type == ARG
				|| (token_next->type == SUBSHELL
					&& ft_strcmp(token_next->value, "(") == 0)))
			return (unexpected_token(data, token_next->value), false);
	}
	return (true);
}
