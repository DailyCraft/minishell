/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:26:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/23 11:39:06 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_interrupted;

static int	empty_event(void)
{
	return (0);
}

static void	catch_sigint(int sig __attribute__((unused)))
{
	g_interrupted = 1;
	rl_done = 1;
}

static int	request(t_data *data, char *limit, int interpret)
{
	int		fds[2];
	char	*line;
	int		i;

	errno_safe(data, "pipe", pipe(fds));
	line = ft_readline(data, "> ");
	i = 1;
	while (line && ft_strcmp(line, limit) != 0)
	{
		if (g_interrupted)
			return (free(line), close(fds[0]), close(fds[1]), -1);
		if (interpret)
			ft_free_set((void **) &line, set_venvps(data, line));
		ft_putendl_fd(line, fds[1]);
		ft_free_set((void **) &line, ft_readline(data, "> "));
		i++;
	}
	if (!line)
	{
		line = ft_itoa(i);
		error_msg(data, "%m: warning: here-document at line %s delimited by "
			"end-of-file (wanted `%s')", (char *[]){line, limit});
	}
	free(line);
	return (close(fds[1]), fds[0]);
}

static bool	get_heredoc(t_data *data, t_command *command)
{
	t_list	*lst;
	int		interpret;

	lst = command->redirects;
	while (lst)
	{
		if (((char *) lst->content)[0] == HERE_DOC)
		{
			if (command->fds.heredoc != 0)
				close(command->fds.heredoc);
			interpret = count_quotes(lst->content + 1) == 0;
			lst->content = remove_quotes(lst->content);
			command->fds.heredoc = request(data, lst->content + 1, interpret);
			if (command->fds.heredoc == -1)
				return (false);
		}
		lst = lst->next;
	}
	return (true);
}

bool	apply_heredocs(t_data *data, t_command *command)
{
	t_command	*current;

	g_interrupted = 0;
	rl_event_hook = empty_event;
	signal(SIGINT, catch_sigint);
	current = command;
	while (current)
	{
		current->fds.heredoc = 0;
		if (!get_heredoc(data, current))
		{
			rl_event_hook = NULL;
			signals(1);
			return (false);
		}
		current = current->pipe;
	}
	rl_event_hook = NULL;
	signals(1);
	return (true);
}
