/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/04 17:26:40 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.program = argv[0];
	data.envp = NULL;
	init_envp(&data, envp);

	char *cat[] = {"cat", "-e", NULL};
	t_command cat_cmd = {.type = COMMAND, .argc = 2, .argv = cat, .pipe = NULL};
	t_list output = {.content = "\001a", .next = NULL};
	t_command command = {.type = COMMAND, .argc = argc - 1, .argv = argv + 1, .pipe = &cat_cmd, .outputs = &output};
	(void) cat_cmd;
	execute(&data, &command);
	free_data(&data);
}
