/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:48:45 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/08 15:32:34 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
		printf("%s\n", split[i++]);
	printf("\n");
}

void	print_commands(t_command *command)
{
	int i;

	i = 1;
	while (command)
	{
		printf("command : %d\n", i);
		print_split(command->argv);
		command = command->pipe;
	}
}

void	minishell(t_data *data)
{
	(void) data;
	char	*input;
	t_btree	*btree;

	while (1)
	{
		input = readline("minishell$ ");
		btree = parse_input(input);
		free(input);
		//print_commands((t_command *)btree->content);
		execute(data, btree->content);
		ft_btree_clear(&btree, clear_command);
	}
}
