/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:46:52 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/23 13:19:40 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*token_new(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	return (ft_lstnew(token));
}

static int	add_operator(char *line, char *operator, t_list **tokens, int type)
{
	size_t	len;

	len = ft_strlen(operator);
	if (ft_strncmp(line, operator, len) != 0)
		return (0);
	ft_lstadd_back(tokens, token_new(type, ft_substr(line, 0, len)));
	return (len);
}

static int	add_arg(char *line, t_list **tokens)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i] && (!ft_isspace(line[i]) || quote != 0))
	{
		if (quote == 0)
		{
			if (ft_strncmp(line + i, "&&", 2) == 0
				|| line[i] == '|' || line[i] == '>' || line[i] == '<'
				|| line[i] == '(' || line[i] == ')')
				break ;
		}
		if ((line[i] == '"' || line[i] == '\'') && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		i++;
	}
	if (i > 0)
		ft_lstadd_back(tokens, token_new(ARG, ft_substr(line, 0, i)));
	return (i);
}

static int	add_operators(t_list **tokens, char *line)
{
	int	len;

	len = add_operator(line, "&&", tokens, LOGICAL);
	if (len == 0)
		len = add_operator(line, "||", tokens, LOGICAL);
	if (len == 0)
		len = add_operator(line, "|", tokens, PIPE);
	if (len == 0)
		len = add_operator(line, ">>", tokens, REDIRECT);
	if (len == 0)
		len = add_operator(line, "<<", tokens, REDIRECT);
	if (len == 0)
		len = add_operator(line, ">", tokens, REDIRECT);
	if (len == 0)
		len = add_operator(line, "<", tokens, REDIRECT);
	if (len == 0 && *line == '(')
		ft_lstadd_back(tokens, token_new(SUBSHELL, ft_strdup("(")));
	if (len == 0 && *line == ')')
		ft_lstadd_back(tokens, token_new(SUBSHELL, ft_strdup(")")));
	if (len == 0 && (*line == '(' || *line == ')'))
		len = 1;
	if (len == 0)
		len = add_arg(line, tokens);
	return (len);
}

t_list	*tokenize(char *line)
{
	t_list	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		i += add_operators(&tokens, line + i);
	}
	return (tokens);
}
