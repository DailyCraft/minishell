/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:13:28 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/18 16:05:40 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wildcards(char *line, int index)
{
	return (operator_len(line + index, '*') == 1 && !is_in_quotes(line, index));
}

int	have_wildcards(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_wildcards(line, i))
			return (1);
		i++;
	}
	return (0);
}

int	cmp_wildcards(char *file, char *to_cmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (to_cmp[i])
	{
		if (to_cmp[i] == '*' && is_wildcards(to_cmp, i))
		{
			if (to_cmp[i + 1] != '\0')
			{
				while (file[j] && file[j] != to_cmp[i + 1])
					j++;
			}
			i++;
		}
		else if (to_cmp[i] == file[j])
		{
			i++;
			j++;
		}
		else
			return (0);
	}
	return (file[j] == '\0');
}

void	wildcards(t_command *command, char *wildcards)
{
	DIR				*dir;
	struct dirent	*entry;
	int				find_dir;

	dir = opendir(".");
	entry = readdir(dir);
	find_dir = 0;
	while (entry)
	{
		if (cmp_wildcards(entry->d_name, wildcards))
		{
			link_argv_line(command, ft_strdup(entry->d_name));
			find_dir++;
		}
		entry = readdir(dir);
	}
	if (!find_dir)
		link_argv_line(command, wildcards);
	else
		free(wildcards);
	closedir(dir);
}
