/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:28:12 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/17 15:50:54 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unexpected_token(t_data *data, char *token)
{
	error_msg(data, "%m: syntax error near unexpected token `%s'",
		(char *[]){token});
	return (1);
}

int	error_file_syntax(t_data *data, char *line)
{
	if (operator_len(line, '|') == 1 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "|"));
	if (operator_len(line, '>') == 1 && !is_in_quotes(line, 0))
		return (unexpected_token(data, ">"));
	if (operator_len(line, '>') == 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, ">>"));
	if (operator_len(line, '<') == 1 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "<"));
	if (operator_len(line, '<') == 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "<<"));
	if (operator_len(line, '&') == 1 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "&"));
	if (operator_len(line, '&') == 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "&&"));
	if (operator_len(line, '|') == 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "||"));
	return (0);
}

int	error_file(t_data *data, char *line)
{
	char	*file;
	int		redirection;
	int		i;
	int		j;

	redirection = get_redirection_op(line);
	if (redirection == 0)
		return (0);
	file = line + 1 + (redirection == HERE_DOC || redirection == APPEND);
	redirection = 0;
	i = 0;
	while (file[i] && ft_isspace(file[i]))
		i++;
	if (is_redirection(file + i) || is_logical(file + i) || is_pipe(file, i))
		return (error_file_syntax(data, file + i));
	j = 0;
	while (file[i + j] && (!ft_isspace(file[i + j])
			|| is_in_quotes(file, i + j) || is_ignored(file, i + j)))
		j++;
	if (j == 0)
		return (unexpected_token(data, "newline"));
	return (0);
}

int	error_syntax(t_data *data, char *line)
{
	if (operator_len(line, '|') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "||"));
	if (operator_len(line, '>') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, ">>"));
	if (operator_len(line, '<') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "<<"));
	if (operator_len(line, '&') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "&&"));
	return (0);
}

// TODO: error message with ' | |'
int	error_cmd(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (error_syntax(data, line + i))
			return (1);
		if (error_file(data, line + i))
			return (1);
		i++;
	}
	return (0);
}
