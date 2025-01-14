/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:48:45 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/14 14:39:19 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_fd(int *fd, char *value, int flags)
{
	if (*fd != 0)
		close(*fd);
	*fd = open(value + 1, flags, 0664);
}

static int	open_redirect(t_command *command, char *value)
{
	if (value[0] == HERE_DOC || value[0] == INPUT)
		command->last_input = value[0];
	if (value[0] == HERE_DOC)
		return (0);
	if (value[0] == INPUT)
		open_fd(&command->input_fd, value, O_RDONLY);
	else if (value[0] == OUTPUT)
		open_fd(&command->output_fd, value, O_CREAT | O_WRONLY | O_TRUNC);
	else if (value[0] == APPEND)
		open_fd(&command->output_fd, value, O_CREAT | O_WRONLY | O_APPEND);
	if (command->input_fd < 0 || command->output_fd < 0)
		return (-1);
	return (0);
}

int	apply_redirections(t_data *data, t_command *command)
{
	t_list	*lst;

	command->last_input = 0;
	command->input_fd = 0;
	command->output_fd = 0;
	lst = command->redirects;
	while (lst)
	{
		if (open_redirect(command, lst->content) == -1)
		{
			error_msg(data, "%m: %s: %n", (char *[]){lst->content + 1});
			return (-1);
		}
		lst = lst->next;
	}
	return (0);
}
