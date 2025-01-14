/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/14 16:31:36 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: Ctrl+C in ./minishell sub process
static void	catch_sigint(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	iterate_btree(t_data *data)
{
	t_btree	*btree;
	t_btree	*or;

	btree = data->btree;
	or = NULL;
	while (btree)
	{
		if (btree->right)
			or = btree->right;
		if (execute(data, btree->content) == 0)
			btree = btree->left;
		else
			btree = or;
	}
}

// TODO: add_history() with empty lines
static void	loop(t_data *data)
{
	char	*input;
	t_btree	*btree;

	input = ft_readline(data, NULL);
	while (input)
	{
		btree = parse_input(data, input);
		if (btree && isatty(STDIN_FILENO))
			add_history(input);
		free(input);
		if (btree)
			iterate_btree(data);
		ft_btree_clear(&data->btree, clear_command);
		input = ft_readline(data, NULL);
	}
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	printf("exit\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		last_status;

	(void) argc;
	data.program = argv[0];
	data.last_status = 0;
	data.envp = NULL;
	data.btree = NULL;
	init_envp(&data, envp);
	signal(SIGINT, catch_sigint);
	init_interactive(&data);
	loop(&data);
	last_status = data.last_status;
	free_data(&data);
	return (last_status);
}
