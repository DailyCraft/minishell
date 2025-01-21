/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:15:55 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/21 08:38:23 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_argv_line(t_command *command, char *line)
{
	ft_lstadd_back(&command->args, ft_lstnew(line));
}

char	*remove_extra_c(char *line)
{
	line = remove_quotes(line);
	line = remove_backslash(line);
	return (line);
}

/* static int	set_argv(t_data *data, t_command *command, char *line)
{
	char	*line_argv;
	int		i;

	i = 0;
	while (line[i] && (!ft_isspace(line[i])
			|| is_in_quotes(line, i) || is_ignored(line, i)))
		i++;
	line_argv = ft_substr(line, 0, i);
	line_argv = set_venvps(data, line_argv);
	if (have_wildcards(line_argv))
	{
		line_argv = remove_backslash(line_argv);
		return (wildcards(command, line_argv), i);
	}
	line_argv = remove_extra_c(line_argv);
	link_argv_line(command, line_argv);
	return (i);
} */

/* void	set_command(t_data *data, t_command *command, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_redirection(line + i))
			i += set_redirections(data, command, line + i);
		else if (line[i] == '(' && !is_in_quotes(line, i))
			i += set_subshell(command, line + i);
		else if (!ft_isspace(line[i]))
			i += set_argv(data, command, line + i);
		else
			i++;
	}
} */

/* t_command	*parse_command(t_data *data, char *command_line)
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
} */
