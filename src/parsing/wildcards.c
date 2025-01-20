/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:13:28 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/20 11:22:53 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_wildcards(char *line, int index)
{
	return (operator_len(line + index, '*') == 1 && !is_in_quotes(line, index));
}

bool	have_wildcards(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_wildcards(line, i))
			return (true);
		i++;
	}
	return (false);
}

static int	cmp_wildcards(char *file, char *to_cmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (to_cmp[i])
	{
		if (to_cmp[i] == '*' && is_wildcards(to_cmp, i))
		{
			while (file[j] && file[j] != to_cmp[i + 1])
				j++;
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

static int	file_cmp(char *s1, char *s2)
{
	char	*originals[2];
	size_t	i;

	originals[0] = s1;
	originals[1] = s2;
	while (*s1 && !ft_isalnum(*s1))
		s1++;
	while (*s2 && !ft_isalnum(*s2))
		s2++;
	i = 0;
	while (ft_tolower(s1[i]) == ft_tolower(s2[i]) && s1[i])
		i++;
	if (s1[i] == 0 && s2[i] == 0)
		return (ft_strcmp(originals[0], originals[1]));
	return ((unsigned char) ft_tolower(s1[i])
		- (unsigned char) ft_tolower(s2[i]));
}

// TODO: .*
void	wildcards(t_command *command, char *wildcards)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*files;

	dir = opendir(".");
	entry = readdir(dir);
	files = NULL;
	while (entry)
	{
		if (entry->d_name[0] != '.' && cmp_wildcards(entry->d_name, wildcards))
			ft_lstadd_back(&files, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	if (files)
		ft_lstsort(files, (int (*)(void *, void *)) file_cmp);
	else
		files = ft_lstnew(wildcards);
	ft_lstadd_back(&command->args, files);
}
