/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/09 13:49:34 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	catch_sigint(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	iterate_btree(t_data *data, t_btree *btree)
{
	t_btree	*or;

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

static void	loop(t_data *data)
{
	char	*input;
	t_btree	*btree;

	input = ft_readline("minishell$ ");
	while (input)
	{
		btree = parse_input(input);
		if (btree)
			iterate_btree(data, btree);
		if (btree && isatty(STDIN_FILENO))
			add_history(input);
		else
			free(input);
		ft_btree_clear(&btree, clear_command);
		input = ft_readline("minishell$ ");
	}
	if (isatty(STDIN_FILENO))
		rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	data.program = argv[0];
	data.envp = NULL;
	init_envp(&data, envp);
	signal(SIGINT, catch_sigint);
	init_interactive(&data);
	loop(&data);
	free_data(&data);
}
