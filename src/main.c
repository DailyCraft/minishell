/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/16 18:51:01 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	loop(t_data *data)
{
	char	*input;
	t_btree	*btree;

	input = ft_readline(data, NULL);
	while (input)
	{
		btree = parse_input(data, input);
		if (isatty(STDIN_FILENO) && !btree_is_empty(btree))
			add_history(input);
		free(input);
		if (btree)
			iterate_btree(data);
		ft_btree_clear(&data->btree, free_command);
		input = ft_readline(data, NULL);
	}
	if (isatty(STDIN_FILENO))
		rl_clear_history();
	printf("exit\n");
}

int	main(int argc __attribute__((unused)), char **argv, char **envp)
{
	t_data	data;
	int		last_status;

	data.program = argv[0];
	data.last_status = 0;
	data.envp = NULL;
	data.btree = NULL;
	init_envp(&data, envp);
	signals(1);
	print_header();
	loop(&data);
	last_status = data.last_status;
	free_data(&data);
	return (last_status);
}
