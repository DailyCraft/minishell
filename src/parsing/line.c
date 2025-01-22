/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/22 08:41:18 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*logical(t_line *line, t_list **current)
{
	t_list	*tokens;
	t_token	*token;
	int		is_and;

	token = (*current)->content;
	is_and = token->value[0] == '&';
	tokens = (*current)->next;
	ft_lstdelone(*current, free_token);
	*current = NULL;
	if (is_and)
		ft_lstadd_back(&line->ands, ft_lstnew(tokens));
	else
	{
		line->or = new_line(tokens);
		return (NULL);
	}
	return (tokens);
}

t_line	*new_line(t_list *tokens)
{
	t_line	*line;
	t_list	**current;

	line = ft_calloc(1, sizeof(t_line));
	line->ands = ft_lstnew(tokens);
	current = &tokens;
	while (*current)
	{
		if (((t_token *)(*current)->content)->type == SUBSHELL)
		{
			current = &(*get_close_subshell(current))->next;
			continue ;
		}
		if (((t_token *)(*current)->content)->type == LOGICAL)
		{
			tokens = logical(line, current);
			if (!tokens)
				break ;
			current = &tokens;
		}
		else
			current = &(*current)->next;
	}
	return (line);
}

void	parse_line(t_data *data, char *input)
{
	t_list	*tokens;

	if (count_quotes(input) % 2 == 1)
	{
		error_msg(data, "%m: syntax error: unclosed quotes", NULL);
		data->last_status = 2;
		data->line = NULL;
		return ;
	}
	tokens = tokenize(input);
	if (check_unexpected(data, tokens))
	{
		ft_lstclear(&tokens, free_token);
		data->last_status = 2;
		data->line = NULL;
		return ;
	}
	data->line = new_line(tokens);
}

static void	free_and(void *and)
{
	ft_lstclear((t_list **) &and, free_token);
}

void	free_line(t_line **line)
{
	if (!*line)
		return ;
	ft_lstclear(&(*line)->ands, free_and);
	free_line(&(*line)->or);
	free(*line);
	*line = NULL;
}
