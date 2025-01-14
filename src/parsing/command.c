/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:15:55 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/14 15:55:03 by cgrasser         ###   ########.fr       */
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

void	link_last_argv(t_command *command)
{
	char	**old_argv;
	int		i;

	old_argv = command->argv;
	command->argv = malloc(command->argc * sizeof(char *));
	i = 0;
	command->argc--;
	while (i < command->argc - 1)
	{
		command->argv[i] = old_argv[i];
		i++;
	}
	command->argv[i] = ft_strjoin(old_argv[i], old_argv[i + 1]);
	command->argv[command->argc] = NULL;
	free(old_argv[i]);
	free(old_argv[i + 1]);
	free(old_argv);
}

static int	set_argv(t_data *data, t_command *command, char *line)
{
	char	*line_argv;
	int		i;

	i = 0;
	while (line[i] && (line[i] != ' ' || is_in_quotes(line, i)))
		i++;
	line_argv = ft_substr(line, 0, i);
	line_argv = set_venvps(data, line_argv);
	line_argv = remove_quotes(line_argv);
	link_argv_line(command, line_argv);
	return (i);
}

void	set_command(t_data *data, t_command *command, char *line)
{
	int	i;

	i = 0;
	command->argc = 0;
	while (line[i])
	{
		if (is_redirection(line + i))
			i += set_redirections(command, line + i);
		else if (line[i] != ' ')
			i += set_argv(data, command, line + i);
		else
			i++;
	}
}

t_command	*command_new(t_data *data, char *command_line)
{
	t_command	*command;
	char		*line;
	int			i;

	command = ft_calloc(1, sizeof(t_command));
	i = find_pipe(command_line);
	line = ft_substr(command_line, 0, i);
	set_command(data, command, line);
	free(line);
	if (command_line[i] == '|')
		command->pipe = command_new(data, command_line + i + 1);
	command->type = COMMAND;
	return (command);
}
