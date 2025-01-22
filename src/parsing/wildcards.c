/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:13:28 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/22 17:21:17 by cgrasser         ###   ########.fr       */
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

static int	cmp_wildcards(char *file, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (is_quote(arg, i))
		{
		}
		else if (arg[i] == '*' && !is_in_quotes(arg, i))
		{
			if (j == 0 && file[j] == '.')
				return (0);
			while (file[j] && (file[j] != arg[i + 1]
					|| arg[i + 1] == file[j + 1]))
				j++;
		}
		else if (arg[i] == file[j])
			j++;
		else
			return (0);
		i++;
	}
	return (file[j] == '\0');
}

int	file_cmp(char *s1, char *s2)
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

t_list	*add_tokens(t_list **current, t_list *files)
{
	t_list	*next;
	t_list	*prev;

	next = (*current)->next;
	//ft_lstdelone(*current, NULL);
	prev = NULL;
	while (files)
	{
		*current = token_new(ARG, files->content);
		prev = *current;
		current = &(*current)->next;
		files = files->next;
	}
	*current = next;
	return (prev);
}

// TODO: Leaks
// TODO: $*
// TODO: files with quotes?
t_list	*wildcards(t_command *command, char *wildcards, t_list **current)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*files;

	dir = opendir(".");
	entry = readdir(dir);
	files = NULL;
	while (entry)
	{
		if (cmp_wildcards(entry->d_name, wildcards))
			ft_lstadd_back(&files, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	if (files)
		ft_lstsort(files, (int (*)(void *, void *)) file_cmp);
	else
		files = ft_lstnew(remove_quotes(wildcards));
	ft_lstadd_back(&command->args, files);
	return (add_tokens(current, files));
}
