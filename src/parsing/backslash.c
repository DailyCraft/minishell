/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:36:49 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 10:39:23 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_ignored(char *line, int index)
{
	if (index == 0 || in_quotes(line, index, '\''))
		return (false);
	return (line[index - 1] == '\\');
}

int	nb_backslash(char *line)
{
	int	i;
	int	b_count;

	i = 0;
	b_count = 0;
	while (line[i])
	{
		if (line[i] == '\\' && !is_in_quotes(line, i))
			b_count++;
		i++;
	}
	return (b_count);
}

// TODO: echo "salut\' salut"
// TODO: echo 'salut \' ''
char	*remove_backslash(char *line)
{
	int		i;
	int		j;
	char	*new;

	new = malloc((ft_strlen(line) - nb_backslash(line) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != '\\' || is_in_quotes(line, i))
			new[j++] = line[i++];
		else
			i++;
	}
	new[j] = 0;
	free(line);
	return (new);
}
