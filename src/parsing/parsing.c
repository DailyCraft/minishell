/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 16:28:39 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_btree	*set_btree(char *input)
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
	t_list	*tokens;
	

	tokens = tokenize(input);
	/* if (check_unexpected(tokens))
	{
		data->last_status = 2;
		data->btree = NULL;
		return ;
	} */

	data->btree = set_btree(input);
}

t_command	*parse_command(t_list *tokens)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	command->type = SUBSHELL;
	while (tokens)
	{
		if (((t_token *) tokens->content)->type == SUBSHELL)
		{
			// TODO
		}
		else if (((t_token *) tokens->content)->type == REDIRECT)
		{
			//ft_lstadd_back(command->redirects, ft_lstnew(((t_token *) tokens->content)->value) + tokens->next->content)
		}
		else if (((t_token *) tokens->content)->type == ARG)
		{
			ft_lstadd_back(command->args, ft_lstnew(((t_token *) tokens->content)->value));
		}
		else if (((t_token *) tokens->content)->type == PIPE)
		{
			command->pipe = parse_command(tokens->next);
			break ;
		}
		tokens = tokens->next;
	}
	
}
