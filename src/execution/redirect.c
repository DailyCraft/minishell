/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:48:45 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/13 11:27:32 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_output(t_data *data, t_command *command)
{
	int		fd;
	t_list	*lst;
	int		flag;

	fd = 1;
	lst = command->outputs;
	while (lst)
	{
		if (fd != 1)
			close(fd);
		if (((char *) lst->content)[0] == 1)
			flag = O_TRUNC;
		else
			flag = O_APPEND;
		fd = open(lst->content + 1, O_CREAT | O_WRONLY | flag, 0664);
		if (fd < 0)
		{
			error_msg(data, "%m: %s", (char *[]){lst->content + 1});
			return (-1);
		}
		lst = lst->next;
	}
	return (fd);
}

int	open_input(t_data *data, t_command *command)
{
	int		fd;
	t_list	*lst;

	fd = 0;
	lst = command->inputs;
	while (lst)
	{
		if (((char *) lst->content)[0] == INPUT)
		{
			if (fd != 0)
				close(fd);
			fd = open(lst->content + 1, O_RDONLY);
			if (fd < 0)
			{
				error_msg(data, "%m: %s", (char *[]){lst->content + 1});
				return (-1);
			}
		}
		lst = lst->next;
	}
	return (fd);
}

static char	*heredoc(t_data *data, char *limit)
{
	char	*result;
	char	*line;

	result = ft_strdup("");
	line = ft_readline(data, "> ");
	while (line && ft_strcmp(line, limit) != 0)
	{
		ft_free_set((void **) &result,
			ft_strsjoin((const char *[]){result, line, "\n", NULL}));
		free(line);
		line = ft_readline(data, "> ");
	}
	return (result);
}

char	*get_heredoc(t_data *data, t_command *command)
{
	char	*result;
	t_list	*lst;

	result = NULL;
	lst = command->inputs;
	while (lst)
	{
		if (((char *) lst->content)[0] == HERE_DOC)
		{
			if (result)
				free(result);
			result = heredoc(data, lst->content + 1);
		}
		lst = lst->next;
	}
	return (result);
}
