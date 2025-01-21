/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:27:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/21 13:05:11 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexpected_token(t_data *data, char *token)
{
	error_msg(data, "%m: syntax error near unexpected token `%s'",
		(char *[]){token});
}

// TODO: echo 1 && (echo 2)
bool	check_valid_type(t_data *data, t_list *lst)
{
	t_token	*token;

	if (!lst->next)
	{
		token = lst->content;
		if (token->type == REDIRECT)
			return (unexpected_token(data, "newline"), false);
		else
			return (unexpected_token(data, token->value), false);
	}
	else
	{
		token = lst->next->content;
		if (token->type != ARG)
			return (unexpected_token(data, token->value), false);
	}
	return (true);
}

bool	check_valid_subshell(t_data *data, t_list *lst, t_token *token)
{
	t_token	*token_next;

	if (lst->next)
		token_next = lst->next->content;
	else
		return (true);
	if (ft_strcmp(token->value, "(") == 0)
	{
		if (token_next->type != ARG && (token_next->type != SUBSHELL
				|| (token_next->type == SUBSHELL
					&& ft_strcmp(token_next->value, ")") == 0)))
			return (unexpected_token(data, token_next->value), false);
	}
	else
	{
		if (token_next->type == ARG)
			return (unexpected_token(data, token_next->value), false);
	}
	return (true);
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

bool	check_unexpected(t_data *data, t_list *lst)
{
	t_token	*token;

	if (!check_subshell_lvl(data, lst))
		return (true);
	while (lst)
	{
		token = (t_token *)lst->content;
		// if (token->type != ARG && token->type != SUBSHELL)
		// 	if (!check_valid_type(data, lst))
		// 		return (true);
		if (token->type == SUBSHELL)
			if (!check_valid_subshell(data, lst, token))
				return (true);
		lst = lst->next;
	}
	return (false);
}
