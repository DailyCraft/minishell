/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:43:18 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/14 16:17:49 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char *line, int index)
{
	return (operator_len(line + index, '|') == 1 && !is_in_quotes(line, index));
}

int	find_pipe(char *command_line)
{
	int	i;

	i = 0;
	while (command_line[i] && !is_pipe(command_line, i))
		i++;
	return (i);
}
