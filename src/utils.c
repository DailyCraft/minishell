/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:52:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/16 14:48:05 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_basename(char *path)
{
	char	*last_sep;
	char	*result;

	if (!path || path[0] == 0)
		return (ft_strdup("."));
	last_sep = ft_strrchr(path, '/');
	while (last_sep && (last_sep[1] == 0 || last_sep[1] == '/'))
		last_sep = ft_memrchr(path, '/', last_sep - path);
	if (!last_sep && path[0] == '/')
		return (ft_strdup("/"));
	if (!last_sep)
		result = ft_strdup(path);
	else
		result = ft_strdup(last_sep + 1);
	last_sep = ft_strchr(result, '/');
	if (last_sep)
		*last_sep = 0;
	return (result);
}

void	ft_lstsort(t_list *lst, int (*cmp)(void *, void *))
{
	int		modified;
	t_list	*temp;
	char	*content;

	modified = 1;
	while (modified)
	{
		modified = 0;
		temp = lst;
		while (temp && temp->next)
		{
			if (cmp(temp->content, temp->next->content) > 0)
			{
				content = temp->content;
				temp->content = temp->next->content;
				temp->next->content = content;
				modified = 1;
			}
			else
				temp = temp->next;
		}
	}
}

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*dup;

	dup = NULL;
	while (lst)
	{
		ft_lstadd_back(&dup, ft_lstnew(lst->content));
		lst = lst->next;
	}
	return (dup);
}

char	**strsdup(char **strs)
{
	char	**result;
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	result = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (strs[i])
	{
		result[i] = ft_strdup(strs[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	free_data(t_data *data)
{
	if (!data->program)
		return ;
	data->program = NULL;
	ft_lstclear(&data->envp, free_env);
	ft_btree_clear(&data->btree, free_command);
}
