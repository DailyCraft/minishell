/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:13:28 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/24 14:32:40 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_wildcards(char *file, char *arg);

static int	handle_star(char *file, char *arg, int *j, int i)
{
	if (arg[i + 1] == '\0')
		return (1);
	while (file[*j])
	{
		if (cmp_wildcards(file + *j, arg + i + 1))
			return (1);
		(*j)++;
	}
	return (0);
}

static int	cmp_wildcards(char *file, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (is_quote(arg, i) && !is_in_quotes(arg, i))
		{
		}
		else if (arg[i] == '*' && !is_in_quotes(arg, i))
		{
			if (j == 0 && file[j] == '.')
				return (0);
			if (handle_star(file, arg, &j, i))
				return (1);
		}
		else if (arg[i] == file[j])
			j++;
		else
			return (0);
		i++;
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

static t_list	*add_tokens(t_command *command, t_list **current, t_list *files)
{
	t_list	*first_file;
	t_list	*next;
	t_list	*prev;

	ft_lstsort(files, (int (*)(void *, void *)) file_cmp);
	first_file = files;
	if (command)
		ft_lstadd_back(&command->args, files);
	next = (*current)->next;
	ft_lstdelone(*current, free_token);
	prev = NULL;
	while (files)
	{
		*current = token_new(ARG, files->content);
		prev = *current;
		current = &(*current)->next;
		files = files->next;
	}
	*current = next;
	if (!command)
		ft_lstclear(&first_file, NULL);
	return (prev);
}

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
		return (add_tokens(command, current, files));
	wildcards = remove_quotes(wildcards);
	((t_token *)(*current)->content)->value = wildcards;
	if (command)
		ft_lstadd_back(&command->args, ft_lstnew(wildcards));
	return (*current);
}
