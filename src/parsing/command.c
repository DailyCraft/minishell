/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:58:31 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/22 15:59:16 by dvan-hum         ###   ########.fr       */
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

static void	redirect(t_data *data, t_command *command, t_list *current)
{
	char	*redirect_str;
	char	redirect;
	char	*file;

	redirect_str = ((t_token *) current->content)->value;
	file = ((t_token *) current->next->content)->value;
	if (ft_strcmp(redirect_str, "<<") == 0)
		redirect = HERE_DOC;
	else if (ft_strcmp(redirect_str, "<") == 0)
		redirect = INPUT;
	else if (ft_strcmp(redirect_str, ">>") == 0)
		redirect = APPEND;
	else
		redirect = OUTPUT;
	redirect_str = malloc((ft_strlen(file) + 2) * sizeof(char));
	redirect_str[0] = redirect;
	ft_strcpy(redirect_str + 1, file);
	if (redirect != HERE_DOC)
	{
		redirect_str = set_venvps(data, redirect_str);
		redirect_str = remove_quotes(redirect_str);
	}
	ft_lstadd_back(&command->redirects, ft_lstnew(redirect_str));
}

static void	arg(t_data *data, t_command *command, char **value)
{
	*value = set_venvps(data, *value, command);
	if (!*value)
		return ;
	if (has_wildcards(*value))
		wildcards(command, *value);
	else
	{
		*value = remove_quotes(*value);
		ft_lstadd_back(&command->args, ft_lstnew(*value));
	}
}

static t_list	**parse_token(t_data *data, t_command *command, t_list *current)
{
	t_token	*token;

	token = current->content;
	if (token->type == SUBSHELL)
	{
		return (subshell(command, current));
	}
	else if (token->type == REDIRECT)
	{
		redirect(data, command, current);
		return (&current->next->next);
	}
	else if (token->type == ARG)
	{
		arg(data, command, &token->value);
		return (&current->next);
	}
	else
	{
		command->pipe = parse_command(data, current->next);
		return (NULL);
	}
}

t_command	*parse_command(t_data *data, t_list *tokens)
{
	t_command	*command;
	t_list		**current;

	command = ft_calloc(1, sizeof(t_command));
	command->type = COMMAND;
	current = &tokens;
	while (*current)
	{
		current = parse_token(data, command, *current);
		if (current == NULL)
			break ;
	}
	return (command);
}
