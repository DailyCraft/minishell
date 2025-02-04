/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:50:19 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/22 20:17:50 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(char *line, int index)
{
	return (line[index] == '\'' || line[index] == '"');
}

bool	in_quotes(char *line, int index, char to_find)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (line[i] && i <= index)
	{
		if (is_quote(line, i) && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		i++;
	}
	if (quote == 0 || line[index] == quote)
		return (0);
	while (line[i] && line[i] != quote)
		i++;
	return (!line[i] || (line[i] == quote && line[i] == to_find));
}

bool	is_in_quotes(char *line, int index)
{
	return (in_quotes(line, index, '\'') || in_quotes(line, index, '"'));
}

int	count_quotes(char *line)
{
	int	i;
	int	c_quotes;

	i = 0;
	c_quotes = 0;
	while (line[i])
	{
		if (is_quote(line, i) && !is_in_quotes(line, i))
			c_quotes++;
		i++;
	}
	return (c_quotes);
}

char	*remove_quotes(char *line)
{
	char	*new;
	int		c_quotes;
	int		i;
	int		j;

	c_quotes = count_quotes(line);
	if (!c_quotes)
		return (line);
	new = malloc((ft_strlen(line) - c_quotes + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_quote(line, i) && !is_in_quotes(line, i))
			i++;
		else
			new[j++] = line[i++];
	}
	new[j] = 0;
	free(line);
	return (new);
}
