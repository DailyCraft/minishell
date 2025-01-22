/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 07:43:38 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/22 10:31:51 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_fd(int *fd, char *value, int flags)
{
	if (*fd != 0)
		close(*fd);
	*fd = open(value + 1, flags, 0664);
}

static bool	open_redirect(t_command *command, char *value)
{
	if (value[0] == HERE_DOC || value[0] == INPUT)
		command->fds.last_input = value[0];
	if (value[0] == HERE_DOC)
		return (true);
	if (value[0] == INPUT)
		open_fd(&command->fds.input, value, O_RDONLY);
	else if (value[0] == OUTPUT)
		open_fd(&command->fds.output, value, O_CREAT | O_WRONLY | O_TRUNC);
	else if (value[0] == APPEND)
		open_fd(&command->fds.output, value, O_CREAT | O_WRONLY | O_APPEND);
	if (command->fds.input < 0 || command->fds.output < 0)
		return (false);
	return (true);
}

bool	apply_redirections(t_data *data, t_command *command)
{
	t_list	*lst;

	command->fds.last_input = 0;
	command->fds.input = 0;
	command->fds.output = 0;
	lst = command->redirects;
	while (lst)
	{
		if (!open_redirect(command, lst->content))
		{
			error_msg(data, "%m: %s: %n", (char *[]){lst->content + 1});
			return (false);
		}
		lst = lst->next;
	}
	return (true);
}
