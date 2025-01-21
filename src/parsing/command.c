/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:58:31 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 13:30:18 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	subshell(t_command *command, t_list ***current)
{
	t_list	**close;
	t_list	*temp;

	command->type = SUB_SHELL;
	close = get_close_subshell(**current);
	temp = *close;
	*close = NULL;
	command->tokens = ft_lstmap((**current)->next, dup_token, free_token);
	*close = temp;
	*current = &(*close)->next;
	return (true);
}

static void	redirect(t_command *command, t_token *token, t_list ***current)
{
	(void) command;
	(void) token;
	*current = &(**current)->next->next;
	//ft_lstadd_back(command->redirects,
	//	ft_lstnew(token->value) + tokens->next->content)
}

t_command	*parse_command(t_list *tokens)
{
	t_command	*command;
	t_list		**current;
	t_token		*token;

	command = ft_calloc(1, sizeof(t_command));
	command->type = COMMAND;
	current = &tokens;
	while (*current)
	{
		token = (*current)->content;
		if (token->type == SUBSHELL)
		{
			subshell(command, &current);
			continue ;
		}
		else if (token->type == REDIRECT)
		{	redirect(command, token, &current); continue ;}
		else if (token->type == ARG)
			ft_lstadd_back(&command->args,
				ft_lstnew(token->value = remove_extra_c(token->value)));
		else if (token->type == PIPE)
		{
			command->pipe = parse_command((*current)->next);
			break ;
		}
		current = &(*current)->next;
	}
	return (command);
}
