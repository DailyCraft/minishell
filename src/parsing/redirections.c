/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:12:09 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 15:46:54 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redirection_file(t_command *command, char *line, char redirect)
{
	int		i;
	int		j;
	char	*file;
	t_list	*node;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i + j] && !ft_isspace(line[i + j]))
		j++;
	file = malloc((j + 2) * sizeof(char));
	file[0] = redirect;
	ft_memcpy(file + 1, line + i, j);
	file[j + 1] = 0;
	node = ft_lstnew(file);
	if (redirect == HERE_DOC || redirect == INPUT)
		ft_lstadd_back(&command->inputs, node);
	else
		ft_lstadd_back(&command->outputs, node);
	return (i + j);
}

int	set_redirections(t_command *command, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_here_doc(line + i))
			i += set_redirection_file(command, line + i + 2, HERE_DOC) + 2;
		else if (is_input(line + i))
			i += set_redirection_file(command, line + i + 1, INPUT) + 1;
		else if (is_output(line + i))
			i += set_redirection_file(command, line + i + 1, OUTPUT) + 1;
		else if (is_append(line + i))
			i += set_redirection_file(command, line + i + 2, APPEND) + 2;
		else
			i++;
	}
	return (i);
}
