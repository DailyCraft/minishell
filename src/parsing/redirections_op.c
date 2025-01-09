/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:24:56 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 14:18:14 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(char *command_line)
{
	if (ft_strlen(command_line) < 2)
		return (0);
	return (command_line[0] == '<'
		&& command_line[1] == '<'
		&& command_line[2] != '<');
}

int	is_append(char *command_line)
{
	if (ft_strlen(command_line) < 2)
		return (0);
	return (command_line[0] == '>'
		&& command_line[1] == '>'
		&& command_line[2] != '>');
}

int	is_input(char *command_line)
{
	return (command_line[0] == '<' && command_line[1] != '<');
}

int	is_output(char *command_line)
{
	return (command_line[0] == '>' && command_line[1] != '>');
}

int	is_redirection(char *command_line)
{
	return (is_here_doc(command_line)
		|| is_append(command_line)
		|| is_input(command_line)
		|| is_output(command_line));
}
