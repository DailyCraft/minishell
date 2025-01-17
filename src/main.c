/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/17 16:00:48 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iterate_btree(t_data *data)
{
	t_btree		*btree;
	t_btree		*or;
	t_command	*command;

	btree = data->btree;
	or = NULL;
	while (btree)
	{
		if (btree->right)
			or = btree->right;
		command = parse_command(data, btree->content);
		if (execute(data, command) == 0)
			btree = btree->left;
		else
			btree = or;
		free_command(command);
	}
}

static void	loop(t_data *data)
{
	char	*input;

	input = ft_readline(data, NULL);
	while (input)
	{
		if (isatty(STDIN_FILENO) && !is_empty_command_line(input))
			add_history(input);
		parse_btree(data, input);
		free(input);
		if (data->btree)
			iterate_btree(data);
		ft_btree_clear(&data->btree, free);
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
	free_data(&data, NULL);
	return (last_status);
}
