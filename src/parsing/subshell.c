/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/20 13:04:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	subshell_level(char *line, int index)
{
	int	level;
	int	i;

	level = 0;
	i = 0;
	while (line[i] && i <= index)
	{
		if (i > 0 && line[i - 1] == '(' && !is_in_quotes(line, index - 1))
			level++;
		else if (line[i] == ')' && !is_in_quotes(line, index))
			level--;
		i++;
	}
	return (level);
}

int	set_subshell(t_command *command, char *line)
{
	size_t	i;

	command->type = SUB_SHELL;
	i = 1;
	while (line[i] != ')' || subshell_level(line, i) > 0)
		i++;
	command->command_line = ft_substr(line, 1, i - 1);
	return (i + 2);
}
