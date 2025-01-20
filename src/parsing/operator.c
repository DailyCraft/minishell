/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:50:41 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 12:17:39 by dvan-hum         ###   ########.fr       */
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

bool	is_logical(char *line, int index)
{
	return (
		(operator_len(line + index, '&') == 2 && !is_in_quotes(line, index))
		|| (operator_len(line + index, '|') == 2 && !is_in_quotes(line, index))
	);
}

int	find_logical(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (!is_logical(line, i) || subshell_level(line, i) > 0))
		i++;
	return (i);
}
