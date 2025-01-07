/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:48:45 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/07 11:58:21 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		execute(data, btree->content);
		ft_btree_clear(&btree, clear_command);
	}
}
