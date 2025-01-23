/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:58:31 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/23 21:59:22 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	**subshell(t_command *command, t_list *current)
{
	t_list	**close;
	t_list	*temp;

	command->type = SUB_SHELL;
	close = get_close_subshell(&current);
	temp = *close;
	*close = NULL;
	command->tokens = ft_lstmap(current->next, dup_token, free_token);
	*close = temp;
	return (&(*close)->next);
}

// TODO: quotes on envp
static bool	redirect(t_data *data, t_command *command, t_list *current)
{
	char	*redirect_str;
	char	redirect;
	char	*file;

	redirect_str = ((t_token *) current->content)->value;
	file = ft_strdup(((t_token *) current->next->content)->value);
	if (ft_strcmp(redirect_str, "<<") == 0)
		redirect = HERE_DOC;
	else if (ft_strcmp(redirect_str, "<") == 0)
		redirect = INPUT;
	else if (ft_strcmp(redirect_str, ">>") == 0)
		redirect = APPEND;
	else
		redirect = OUTPUT;
	if (redirect != HERE_DOC)
	{
		t_list	*new_tokens = token_new(ARG, file);
		command_venvps(data, &new_tokens);
		if (!new_tokens || new_tokens->next)
			return (ft_lstclear(&new_tokens, free_token), error_msg(data, "%m: %s: ambiguous redirect", (char *[]){((t_token *) current->next->content)->value}), false);
		if (has_wildcards(((t_token *) new_tokens->content)->value))
		{
			wildcards(NULL, ((t_token *) new_tokens->content)->value, &new_tokens);
			if (new_tokens->next)
				return (ft_lstclear(&new_tokens, free_token), error_msg(data, "%m: %s: ambiguous redirect", (char *[]){((t_token *) current->next->content)->value}), false);
			file = ft_strdup(((t_token *) new_tokens->content)->value);
		}
		else
		{
			file = remove_quotes(((t_token *) new_tokens->content)->value);
			if (file == ((t_token *) new_tokens->content)->value)
				file = ft_strdup(file);
			else
				((t_token *) new_tokens->content)->value = NULL;
			//((t_token *) current->next->content)->value = NULL;
		}
		ft_lstclear(&new_tokens, free_token);
	}
	redirect_str = malloc((ft_strlen(file) + 2) * sizeof(char));
	redirect_str[0] = redirect;
	ft_strcpy(redirect_str + 1, file);
	free(file);
	ft_lstadd_back(&command->redirects, ft_lstnew(redirect_str));
	return (true);
}

// TODO: envp with quotes
static t_list	**arg(t_data *data, t_command *command, t_list **current)
{
	t_list	**lst;
	t_list	*post;
	char	**value;

	post = (*current)->next;
	command_venvps(data, current);
	lst = current;
	while (*lst != post)
	{
		value = &((t_token *) (*lst)->content)->value;
		if (has_wildcards(*value))
			lst = &wildcards(command, *value, lst)->next;
		else
		{
			*value = remove_quotes(*value);
			ft_lstadd_back(&command->args, ft_lstnew(*value));
			lst = &(*lst)->next;
		}
	}
	return (lst);
}

static bool	parse_token(t_data *data, t_command *command,
	t_list ***current)
{
	t_token	*token;

	token = (**current)->content;
	if (token->type == SUBSHELL)
		*current = subshell(command, **current);
	else if (token->type == REDIRECT)
	{
		if (!redirect(data, command, **current))
			return (false);
		*current = &(**current)->next->next;
	}
	else if (token->type == ARG)
		*current = arg(data, command, *current);
	else
	{
		command->pipe = parse_command(data, &(**current)->next);
		if (!command->pipe)
			return (false);
		*current = NULL;
	}
	return (true);
}

t_command	*parse_command(t_data *data, t_list **tokens)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	command->type = COMMAND;
	while (*tokens)
	{
		if (!parse_token(data, command, &tokens))
		{
			free_command(command);
			return (NULL);
		}
		if (tokens == NULL)
			break ;
	}
	return (command);
}
