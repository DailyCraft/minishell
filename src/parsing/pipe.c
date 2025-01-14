/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:43:18 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/10 16:28:18 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char *line, int index)
{
	if (line[index] == '|' && line[index + 1] != '|')
		return (!is_in_quotes(line, index));
	return (0);
}

int	find_pipe(char *command_line)
{
	int	i;

	i = 0;
	while (command_line[i] && !is_pipe(command_line, i))
		i++;
	return (i);
}
