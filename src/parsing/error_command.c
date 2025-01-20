/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 07:28:12 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 15:17:10 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	unexpected_token(t_data *data, char *token)
{
	error_msg(data, "%m: syntax error near unexpected token `%s'",
		(char *[]){token});
	return (true);
}

bool	error_file_syntax(t_data *data, char *line)
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
	if (operator_len(line, '&') == 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "&&"));
	if (operator_len(line, '|') == 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "||"));
	return (false);
}

bool	error_file(t_data *data, char *line)
{
	char	*file;
	int		redirection;
	int		i;
	int		j;

	redirection = get_redirection_op(line);
	if (redirection == 0)
		return (false);
	file = line + 1 + (redirection == HERE_DOC || redirection == APPEND);
	redirection = 0;
	i = 0;
	while (file[i] && ft_isspace(file[i]))
		i++;
	if (is_redirection(file + i) || is_logical(file, i) || is_pipe(file, i))
		return (error_file_syntax(data, file + i));
	j = 0;
	while (file[i + j] && (!ft_isspace(file[i + j])
			|| is_in_quotes(file, i + j) || is_ignored(file, i + j)))
		j++;
	if (j == 0)
		return (unexpected_token(data, "newline"));
	return (false);
}

bool	error_syntax(t_data *data, char *line)
{
	if (operator_len(line, '|') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "||"));
	if (operator_len(line, '>') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, ">>"));
	if (operator_len(line, '<') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "<<"));
	if (operator_len(line, '&') > 2 && !is_in_quotes(line, 0))
		return (unexpected_token(data, "&&"));
	return (false);
}

// TODO: error message with ' | |'
// TODO: error message with ' echo '" '
// TODO: '&&' and line end by '&&'
bool	error_cmd(t_data *data, char *line)
{
	int	i;

	if (count_quotes(line) % 2 == 1)
	{
		error_msg(data, "%m: syntax error: unclosed quotes", NULL);
		return (true);
	}
	i = 0;
	while (line[i])
	{
		if (error_syntax(data, line + i) || error_file(data, line + i)
			|| subshell_errors(data, line, i))
			return (true);
		i++;
	}
	if (subshell_level(line, i) > 0)
	{
		error_msg(data, "%m: syntax error: unclosed parenthesis", NULL);
		return (true);
	}
	return (false);
}
