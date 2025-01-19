/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:50:41 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/19 13:33:26 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	operator_len(char *line, char c)
{
	size_t	i;

	i = 0;
	while (line[i] == c)
		i++;
	return (i);
}

int	is_logical_and(char *line, int index)
{
	return (operator_len(line + index, '&') == 2 && !is_in_quotes(line, index));
}

int	is_logical_or(char *line, int index)
{
	return (operator_len(line + index, '|') == 2 && !is_in_quotes(line, index));
}

int	is_logical(char *line, int index)
{
	return (is_logical_or(line, index) || is_logical_and(line, index));
}

int	find_logical(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !is_logical(line, i))
		i++;
	return (i);
}
