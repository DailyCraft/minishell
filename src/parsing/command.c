/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:15:55 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 22:20:21 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	link_argv(t_command *command, char *line)
{
	char	**previous;
	char	**link;
	int		i;

	previous = command->argv;
	link = ft_split(line, ' ');
	i = 0;
	while (link[i])
		i++;
	command->argv = malloc((command->argc + i + 1)*sizeof(char *));
	command->argc = 0;
	i = 0;
	while (previous[i])
		command->argv[command->argc++] = previous[i++];
	i = 0;
	while (link[i])
		command->argv[command->argc++] = link[i++];
	command->argv[command->argc] = NULL;
	free(previous);
	free(link);
}

static int	set_argv(t_command *command, char *command_line)
{
	char	*line;
	int		i;

	i = 0;
	while (command_line[i] && !is_redirection(command_line + i))
		i++;
	if (i == 0)
		return (0);
	line = ft_substr(command_line, 0, i);
	if (!command->argv)
	{
		command->argv = ft_split(line, ' ');
		command->argc = 0;
		while (command->argv[command->argc])
			command->argc++;
	}
	else
		link_argv(command, command_line);
	free(line);
	return (i);
}

static void	set_command(t_command *command, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_redirection(line + i))
			i += set_redirections(command, line + i);
		else if (line[i] != ' ')
			i += set_argv(command, line + i);
		else
			i++;
	}
}

t_command	*command_new(char *command_line)
{
	t_command	*command;
	char		*line;
	int			i;

	command = ft_calloc(1, sizeof(t_command));
	i = find_pipe(command_line);
	line = ft_substr(command_line, 0, i);
	set_command(command, line);
	free(line);
	if (command_line[i] == '|')
		command->pipe = command_new(command_line + i + 1);
	command->type = COMMAND;
	return (command);
}
