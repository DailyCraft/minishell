/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:46:52 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/20 16:19:00 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*token_new(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	return (ft_lstnew(token));
}

static int	add_operator(char *line, int i, char operator, int min, t_list **lst, int type)
{
	int	len;

	len = operator_len(line + i, operator);
	if (len >= min)
		ft_lstadd_back(lst, token_new(type, ft_substr(line, i, len)));
	if (len < min)
		return (0);
	return (len);
}

static int	add_arg(char *line, t_list **lst)
{
	size_t	i;
	int		in_quotes;

	i = 0;
	in_quotes = 0;
	while (line[i] && (!ft_isspace(line[i]) || in_quotes))
	{
		if (in_quotes)
		{
			if (ft_strncmp(line + i, "&&", 2) == 0)
				break ;
			if (line[i] == '|' || line[i] == '>' || line[i] == '<')
				break ;
			if (line[i] == '(' || line[i] == ')')
				break ;
		}
		if (line[i] == '"' && (in_quotes == 0 || in_quotes == 2))
			in_quotes = (in_quotes == 2 ? 0 : 2);
		if (line[i] == '\'' && (in_quotes == 0 || in_quotes == 1))
			in_quotes = (in_quotes == 1 ? 0 : 1);
		i++;
	}

	ft_lstadd_back(lst, token_new(ARG, ft_substr(line, 0, i)));
	return (i);
}

t_list	*tokenize(char *line)
{
	t_list	*lst;
	size_t	i;
	int		len;
	int		added;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		added = 0;
		added = add_operator(line, i, '&', 2, &lst, LOGICAL);
		if (added == 0)
			added = add_operator(line, i, '|', 2, &lst, LOGICAL);
		if (added == 0)
			added = add_operator(line, i, '|', 1, &lst, PIPE);
		if (added == 0)
			added = add_operator(line, i, '>', 1, &lst, REDIRECT);
		if (added == 0)
			added = add_operator(line, i, '<', 1, &lst, REDIRECT);
		if (added == 0 && line[i] == '(')
		{
			ft_lstadd_back(&lst, token_new(SUBSHELL, ft_strdup("(")));
			added = 1;
		}
		if (added == 0 && line[i] == ')')
		{
			ft_lstadd_back(&lst, token_new(SUBSHELL, ft_strdup(")")));
			added = 1;
		}
		if (added == 0 && !ft_isspace(line[i]) && !is_redirection(line + i) && !is_pipe(line, i) && !is_logical(line, i))
		{
			added = add_arg(line + i, &lst);
		}
		i++;
	}
}
