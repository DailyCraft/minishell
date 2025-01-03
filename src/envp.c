/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:45:10 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 08:14:50 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_data *data, char **envp)
{
	while (*envp)
	{
		ft_setenv_parse(data, *envp, 0);
		envp++;
	}
	ft_unsetenv(data, "_");
}

char	*ft_getenv(t_data *data, char *name)
{
	t_list	*lst;

	lst = ft_lstgeti(data->envp, ft_lstindex(data->envp, name, env_cmp));
	if (lst)
		return (((char **) lst->content)[1]);
	else
		return (NULL);
}

int	ft_setenv(t_data *data, char *name, char *value, int overwrite)
{
	t_list	*lst;
	char	**content;

	if (name == NULL)
		return (-1);
	lst = ft_lstgeti(data->envp, ft_lstindex(data->envp, name, env_cmp));
	if (lst)
	{
		if (overwrite)
			ft_unsetenv(data, name);
		else
			return (0);
	}
	content = malloc(2 * sizeof(char *));
	if (!content)
		return (-1);
	content[0] = ft_strdup(name);
	content[1] = ft_strdup(value);
	lst = ft_lstnew(content);
	if (!lst)
		return (-1);
	ft_lstadd_back(&data->envp, lst);
	return (0);
}

int	ft_setenv_parse(t_data *data, char *env, int overwrite)
{
	int		sep;
	char	*name;
	int		result;

	sep = ft_strchr(env, '=') - env;
	name = ft_memdup(env, sep + 1);
	name[sep] = 0;
	result = ft_setenv(data, name, env + sep + 1, overwrite);
	free(name);
	return (result);
}

int	ft_unsetenv(t_data *data, char *name)
{
	if (name == NULL)
		return (-1);
	ft_lstdeli(&data->envp, ft_lstindex(data->envp, name, env_cmp), free_env);
	return (0);
}
