/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:43:18 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 17:05:35 by cgrasser         ###   ########.fr       */
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
