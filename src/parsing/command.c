/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:15:55 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 15:50:44 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_argv_line(t_command *command, char *line)
{
	char	**old_argv;

	if (command->argc != 0)
	{
		old_argv = command->argv;
		command->argv = malloc((command->argc + 2) * sizeof(char *));
		command->argc = 0;
		while (old_argv[command->argc])
		{
			command->argv[command->argc] = old_argv[command->argc];
			command->argc++;
		}
		free(old_argv);
	}
	else
		command->argv = malloc(2 * sizeof(char *));
	command->argv[command->argc++] = line;
	command->argv[command->argc] = NULL;
}

char	*remove_extra_c(char *line)
{
	line = remove_backslash(line);
	line = remove_quotes(line);
	return (line);
}

static int	set_argv(t_data *data, t_command *command, char *line)
{
	char	*line_argv;
	int		i;

	i = 0;
	while (line[i] && (line[i] != ' '
			|| is_in_quotes(line, i) || is_ignored(line, i)))
		i++;
	line_argv = ft_substr(line, 0, i);
	line_argv = set_venvps(data, line_argv);
	line_argv = remove_extra_c(line_argv);
	link_argv_line(command, line_argv);
	return (i);
}

int	set_command(t_data *data, t_command *command, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_redirection(line + i))
			i += set_redirections(data, command, line + i);
		else if (line[i] != ' ')
			i += set_argv(data, command, line + i);
		else
			i++;
	}
	return (0);
}

t_command	*parse_command(t_data *data, char *command_line)
{
	t_command	*command;
	char		*line;
	int			i;

	command = ft_calloc(1, sizeof(t_command));
	command->type = COMMAND;
	i = find_pipe(command_line);
	line = ft_substr(command_line, 0, i);
	set_command(data, command, line);
	free(line);
	if (command_line[i] == '|')
		command->pipe = parse_command(data, command_line + i + 1);
	return (command);
}
