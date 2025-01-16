/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:12:09 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/16 11:01:02 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redirection_file(t_data *data, t_command *command,
	char *line, char redirect)
{
	int		i;
	int		j;
	char	*file;
	t_list	*node;

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
	node = ft_lstnew(file);
	ft_lstadd_back(&command->redirects, node);
	return (i + j);
}

int	set_redirections(t_data *data, t_command *command, char *line)
{
	if (is_here_doc(line))
		return (set_redirection_file(data, command, line + 2, HERE_DOC) + 2);
	else if (is_input(line))
		return (set_redirection_file(data, command, line + 1, INPUT) + 1);
	else if (is_output(line))
		return (set_redirection_file(data, command, line + 1, OUTPUT) + 1);
	else
		return (set_redirection_file(data, command, line + 2, APPEND) + 2);
}
