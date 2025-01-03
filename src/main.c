/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 16:28:36 by dvan-hum         ###   ########.fr       */
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
	t_command cat_cmd = {.argc = 2, .argv = cat, .pipe = NULL, .redirects = NULL};
	t_redirect redirect = {.type = REDIRECT_OUTPUT, .value = "test.txt"};
	(void) redirect;
	t_command command = {.argc = argc - 1, .argv = argv + 1, .pipe = NULL, .redirects = NULL};
	(void) cat_cmd;
	execute(&data, &command, 0);
	ft_lstclear(&data.envp, free_env);
}
