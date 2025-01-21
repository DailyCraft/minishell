/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:13:44 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 08:40:46 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	subshell_level(char *line, size_t index)
{
	int		level;
	size_t	i;

	level = 0;
	i = 0;
	while (i <= index && (line[i] || i == ft_strlen(line)))
	{
		if (i > 0 && line[i - 1] == '(' && !is_in_quotes(line, i - 1))
			level++;
		if (line[i] == ')' && !is_in_quotes(line, i))
			level--;
		i++;
	}
	return (level);
}

/* int	set_subshell(t_command *command, char *line)
{
	size_t	i;

	command->type = SUB_SHELL;
	i = 1;
	while (line[i] != ')' || subshell_level(line, i) > 0)
		i++;
	command->command_line = ft_substr(line, 1, i - 1);
	return (i + 1);
} */

bool subshell_errors(t_data *data, char *line, int index)
{
	int	i;

	if (subshell_level(line, index) < 0)
		return (unexpected_token(data, ")"));
	if (line[index] == ')' && !is_in_quotes(line, index))
	{
		i = index - 1;
		while (i >= 0 && ft_isspace(line[i]) && !is_in_quotes(line, i))
			i--;
		if (line[i] == '(')
			return (unexpected_token(data, ")"));
	}
	if (line[index] == '(' && !is_in_quotes(line, index))
	{
		i = index - 1;
		while (i >= 0 && ft_isspace(line[i]) && !is_in_quotes(line, i))
			i--;
		if (i == -1 || line[i] == '|' || (i > 0 && (ft_strncmp(line + i - 1, "&&", 2) == 0 || ft_strncmp(line + i - 1, "||", 2) == 0)))
		{	
		}
		else
			return (unexpected_token(data, "TODO"));
	}
	return (false);
}
