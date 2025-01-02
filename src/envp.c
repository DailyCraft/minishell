/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:45:10 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/02 13:46:49 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_data *data, char **envp)
{
	while (*envp)
	{
		ft_lstadd_back(&data->envp, ft_lstnew(ft_strdup(*envp)));
		envp++;
	}
}

static int	name_cmp(void *var, void *name)
{
	size_t	len;

	len = ft_strlen(name);
	return (ft_strncmp(var, name, len) != 0 || ((char *) var)[len] != '=');
}

char	*ft_getenv(t_data *data, char *name)
{
	t_list	*lst;

	lst = ft_lstgeti(data->envp, ft_lstindex(data->envp, name, name_cmp));
	if (lst)
		return (ft_strchr(lst->content, '=') + 1);
	else
		return (NULL);
}


void	r(void *c)
{
	ft_putendl_fd(c, 1);
}

int	ft_setenv(t_data *data, char *name, char *value, int overwrite)
{
	t_list	*lst;
	char	*content;
	
	if (name == NULL)
		return (-1);
	lst = ft_lstgeti(data->envp, ft_lstindex(data->envp, name, name_cmp));
	if (lst) 
	{
		if (overwrite)
			ft_unsetenv(data, name);
		else
			return (0);
	}
	content = ft_strjoin(name, "=");
	if (!content)
		return (-1);
	ft_free_set((void **) &content, ft_strjoin(content, value));
	if (!content)
		return (-1);
	lst = ft_lstnew(content);
	if (!lst)
		return (-1);
	ft_lstadd_back(&data->envp, lst);
	return (0);
}

int	ft_unsetenv(t_data *data, char *name)
{
	if (name == NULL)
		return (-1);
	ft_lstdeli(&data->envp, ft_lstindex(data->envp, name, name_cmp), free);
	return (0);
}
