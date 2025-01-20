/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:43:18 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 12:17:32 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_pipe(char *line, int index)
{
	return (operator_len(line + index, '|') == 1 && !is_in_quotes(line, index));
}

int	find_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (!is_pipe(line, i) || subshell_level(line, i) > 0))
		i++;
	return (i);
}
