/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:52:57 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 12:48:27 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO:
 * 	- Special caracters (like \")
 *  - Invalid token (like >>>)
 */
t_list	*parse_command_line(char *command_line)
{
	t_list		*commands;
	t_command	*current;
	size_t		i;
	int			is_simple_quote;
	int			is_double_quote;
	
	command_line = ft_strtrim(command_line, " \t\n\v\f\r");
	commands = NULL;
	current = ft_calloc(1, sizeof(t_command));
	i = 0;
	is_simple_quote = 0;
	is_double_quote = 0;
	while (command_line[i])
	{
		if (command_line[i] == '"' && !is_simple_quote)
			is_double_quote = !is_simple_quote;
		else if (command_line[i] == '\'' && !is_double_quote)
			is_simple_quote = !is_simple_quote;
		else if (command_line[i] == '$' && !is_simple_quote)
		{
		
		}
		else if (!is_simple_quote && !is_double_quote)
		{
			if (command_line[i] == '<' && command_line[i + 1] == '<')
			{
				
			}
			else if (command_line[i] == '>' && command_line[i + 1] == '>')
			{
				
			}
			else if (command_line[i] == '<')
			{
				
			}
			else if (command_line[i] == '>')
			{
				
			}
		}
	}
	free(command_line);
}
