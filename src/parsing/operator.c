/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:50:41 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 13:12:25 by dvan-hum         ###   ########.fr       */
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

int	is_logical_and(char *command_line)
{
	return (operator_len(command_line, '&') == 2);
}

int	is_logical_or(char *command_line)
{
	return (operator_len(command_line, '|') == 2);
}

int	is_logical(char *line)
{
	return (operator_len(line, '&') == 2 || operator_len(line, '|') == 2);
}
