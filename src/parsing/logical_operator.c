/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:50:41 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/08 17:13:37 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_logical_and(char *command_line)
{
	if (ft_strlen(command_line) < 2)
		return (0);
	return (command_line[0] == '&'
		&& command_line[1] == '&'
		&& command_line[2] != '&');
}

int	is_logical_or(char *command_line)
{
	if (ft_strlen(command_line) < 2)
		return (0);
	return (command_line[0] == '|'
		&& command_line[1] == '|'
		&& command_line[2] != '|');
}
