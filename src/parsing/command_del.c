/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:02:36 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/06 21:21:52 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_delone(t_command *command)
{
	t_command	*pipe;

	pipe = command->pipe;
	/*if (command->command_line)
		free(command->command_line);
	else if (command->argv)
		ft_free_split(command->argv);*/
	ft_lstclear(&command->inputs, NULL);
	ft_lstclear(&command->outputs, NULL);
	free(command);
	return (pipe);
}

void	clear_command(void *command)
{
	t_command	*cmd;

	cmd = (t_command *)command;
	while (cmd)
		cmd = command_delone(cmd);
}

