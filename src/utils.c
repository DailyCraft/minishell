/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:52:37 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/04 16:08:10 by dvan-hum         ###   ########.fr       */
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

void	free_data(t_data *data)
{
	if (!data->program)
		return ;
	ft_lstclear(&data->envp, free_env);
	data->program = NULL;
}
