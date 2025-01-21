/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/21 10:12:19 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	free(((t_token *) token)->value);
	free(token);
}

// TODO: 'fregrg && echo salut || erhger'
// TODO: subshells
t_btree	*new_btree(t_list *tokens)
{
	t_btree	*btree;
	t_list	**current;

	btree = ft_btree_new(tokens);
	current = &tokens;
	while (*current && ((t_token *) (*current)->content)->type != LOGICAL)
		current = &(*current)->next;
	if (!*current)
		return (btree);
	if (ft_strcmp(((t_token *) (*current)->content)->value, "&&") == 0)
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
		data->last_status = 2;
		data->btree = NULL;
		return ;
	}
	data->btree = new_btree(tokens);
}

t_command	*parse_command(t_list *tokens)
{
	t_command	*command;
	t_list		**current;
	t_token		*token;
	t_list		**temp;

	command = ft_calloc(1, sizeof(t_command));
	command->type = COMMAND;
	current = &tokens;
	while (*current)
	{
		token = (*current)->content;
		if (token->type == SUBSHELL)
		{
			command->type = SUB_SHELL;
			if (ft_strcmp(token->value, "(") == 0)
				command->tokens = (*current)->next;
			else
			{
				temp = &(*current)->next;
				*current = NULL;
				//ft_lstdelone(*current, free_token);
				//*current = NULL;
				current = temp;
				continue ;
			}
		}
		else if (token->type == REDIRECT)
		{
			//ft_lstadd_back(command->redirects, ft_lstnew(token->value) + tokens->next->content)
		}
		else if (token->type == ARG)
		{
			token->value = remove_extra_c(token->value);
			ft_lstadd_back(&command->args, ft_lstnew(token->value));
		}
		else if (token->type == PIPE)
		{
			command->pipe = parse_command(tokens->next);
			break ;
		}
		current = &(*current)->next;
	}
	return (command);
}
