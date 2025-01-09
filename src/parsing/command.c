/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:15:55 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 15:41:32 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_argv(t_command *command, char *command_line)
{
	char	*line;
	int		i;

	i = 0;
	while (command_line[i] && !is_redirection(command_line + i))
		i++;
	if (i == 0)
		return (0);
	line = ft_substr(command_line, 0, i);
	command->argv = ft_split(line, ' ');
	command->argc = 0;
	while (command->argv[command->argc])
		command->argc++;
	free(line);
	return (i);
}

t_command	*command_new(char *command_line)
{
	t_command	*command;
	char		*line;
	int			j;
	int			i;

	command = ft_calloc(1, sizeof(t_command));
	j = find_pipe(command_line);
	line = ft_substr(command_line, 0, j);
	i = set_argv(command, line);
	free(line);
	line = ft_substr(command_line, i, j - i);
	set_redirections(command, line);
	free(line);
	if (command_line[i] == '|')
		command->pipe = command_new(command_line + i + 1);
	command->type = COMMAND;
	return (command);
}
