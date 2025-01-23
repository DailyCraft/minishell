/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/23 14:52:22 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*new_line(t_list *tokens, bool is_and)
{
	t_line	*line;
	t_list	**current;

	line = ft_calloc(1, sizeof(t_line));
	line->is_and = is_and;
	line->tokens = tokens;
	current = &line->tokens;
	while (*current)
	{
		if (((t_token *)(*current)->content)->type == SUBSHELL)
		{
			current = &(*get_close_subshell(current))->next;
			continue ;
		}
		if (((t_token *)(*current)->content)->type == LOGICAL)
		{
			line->next = new_line((*current)->next,
					((t_token *)(*current)->content)->value[0] == '&');
			ft_lstdelone(*current, free_token);
			*current = NULL;
			break ;
		}
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
	data->line = new_line(tokens, true);
}

void	free_line(t_line **line)
{
	if (!*line)
		return ;
	ft_lstclear(&(*line)->tokens, free_token);
	free_line(&(*line)->next);
	free(*line);
	*line = NULL;
}
