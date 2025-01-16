/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:12:09 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/16 16:31:08 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redirection_file(t_data *data, t_command *command,
	char *line, char redirect)
{
	int		i;
	int		j;
	char	*file;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i + j] && (!ft_isspace(line[i + j])
			|| is_in_quotes(line, i + j) || is_ignored(line, i + j)))
		j++;
	file = malloc((j + 2) * sizeof(char));
	file[0] = redirect;
	ft_memcpy(file + 1, line + i, j);
	file[j + 1] = 0;
	file = set_venvps(data, file);
	file = remove_extra_c(file);
	ft_lstadd_back(&command->redirects, ft_lstnew(file));
	return (i + j);
}

static int	get_redirection_op(char *line)
{
	if (operator_len(line, '<') == 2)
		return (HERE_DOC);
	if (operator_len(line, '>') == 2)
		return (APPEND);
	if (operator_len(line, '<') == 1)
		return (INPUT);
	if (operator_len(line, '>') == 1)
		return (OUTPUT);
	return (0);
}

int	is_redirection(char *command_line)
{
	return (get_redirection_op(command_line) != 0);
}

int	set_redirections(t_data *data, t_command *command, char *line)
{
	int	redirection;

	redirection = get_redirection_op(line);
	if (redirection == HERE_DOC || redirection == APPEND)
		return (set_redirection_file(data, command, line + 2, redirection) + 2);
	return (set_redirection_file(data, command, line + 1, redirection) + 1);
}
