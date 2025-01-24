/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:33:52 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/24 12:49:21 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ambiguous(t_data *data, t_list *current, t_list *new_tokens)
{
	ft_lstclear(&new_tokens, free_token);
	error_msg(data, "%m: %s: ambiguous redirect",
		(char *[]){((t_token *) current->next->content)->value});
	return (false);
}

static bool	no_heredoc(t_data *data, t_list *current, char **file)
{
	t_list	*new_tokens;

	new_tokens = token_new(ARG, *file);
	command_venvps(data, &new_tokens);
	if (!new_tokens || new_tokens->next)
		return (ambiguous(data, current, new_tokens));
	if (has_wildcards(((t_token *) new_tokens->content)->value))
	{
		wildcards(NULL, ((t_token *) new_tokens->content)->value, &new_tokens);
		if (new_tokens->next)
			return (ambiguous(data, current, new_tokens));
		*file = ft_strdup(((t_token *) new_tokens->content)->value);
	}
	else
	{
		*file = remove_quotes(((t_token *) new_tokens->content)->value);
		if (*file == ((t_token *) new_tokens->content)->value)
			*file = ft_strdup(*file);
		else
			((t_token *) new_tokens->content)->value = NULL;
	}
	ft_lstclear(&new_tokens, free_token);
	return (true);
}

bool	parse_redirect(t_data *data, t_command *command, t_list *current)
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
	if (redirect != HERE_DOC && !no_heredoc(data, current, &file))
		return (false);
	redirect_str = malloc((ft_strlen(file) + 2) * sizeof(char));
	redirect_str[0] = redirect;
	ft_strcpy(redirect_str + 1, file);
	free(file);
	ft_lstadd_back(&command->redirects, ft_lstnew(redirect_str));
	return (true);
}
