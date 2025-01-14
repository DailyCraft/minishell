/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:24:56 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/13 15:24:29 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_here_doc(char *command_line)
{
	return (operator_len(command_line, '<') == 2);
}

int	is_append(char *command_line)
{
	return (operator_len(command_line, '>') == 2);
}

int	is_input(char *command_line)
{
	return (operator_len(command_line, '<') == 1);
}

int	is_output(char *command_line)
{
	return (operator_len(command_line, '>') == 1);
}

int	is_redirection(char *command_line)
{
	return (is_here_doc(command_line)
		|| is_append(command_line)
		|| is_input(command_line)
		|| is_output(command_line));
}
