/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:40:47 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 22:40:54 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	print_argv(t_command *command)
{
	int	i;

	i = 0;
	while (command->argv[i])
		printf("%s\n", command->argv[i++]);
}*/

t_btree	*parse_input(char *input)
{
	t_command	*command = command_new(input);
	print_argv(command);
	t_btree		*btree = ft_btree_new(command);
	return (btree);
}
