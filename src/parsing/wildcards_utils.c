/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:48:33 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/24 11:52:34 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_wildcards(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '*' && !is_in_quotes(line, i))
			return (true);
		i++;
	}
	return (false);
}
