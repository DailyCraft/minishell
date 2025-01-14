/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:26:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/14 16:46:27 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Ctrl+C
static int	request(t_data *data, char *limit)
{
	int		fds[2];
	char	*line;
	int		i;

	errno_safe(data, "pipe", pipe(fds));
	line = ft_readline(data, "> ");
	i = 1;
	while (line && ft_strcmp(line, limit) != 0)
	{
		line = set_venvps(data, line);
		ft_putendl_fd(line, fds[1]);
		ft_free_set((void **) &line, ft_readline(data, "> "));
		i++;
	}
	if (!line)
	{
		line = ft_itoa(i);
		error_msg(data, "%m: %s %s %s (wanted '%s')",
			(char *[]){"warning: here-document at line", line,
			"delimited by end-of-file", limit});
	}
	free(line);
	return (close(fds[1]), fds[0]);
}

static void	get_heredoc(t_data *data, t_command *command)
{
	t_list	*lst;

	lst = command->redirects;
	while (lst)
	{
		if (((char *) lst->content)[0] == HERE_DOC)
		{
			if (command->heredoc_fd != 0)
				close(command->heredoc_fd);
			command->heredoc_fd = request(data, lst->content + 1);
		}
		lst = lst->next;
	}
}

void	apply_heredocs(t_data *data, t_command *command)
{
	t_command	*current;

	current = command;
	while (current)
	{
		current->heredoc_fd = 0;
		get_heredoc(data, current);
		current = current->pipe;
	}
}
