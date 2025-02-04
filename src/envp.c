/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:45:10 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/24 14:41:34 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_data *data, char **envp)
{
	char	*temp;

	while (*envp)
	{
		ft_setenv_parse(data, *envp);
		envp++;
	}
	if (ft_getenv(data, "SHLVL") && data->is_tty)
	{
		temp = ft_itoa(ft_atoi(ft_getenv(data, "SHLVL")) + 1);
		ft_setenv(data, "SHLVL", temp);
		free(temp);
	}
	else
		ft_setenv(data, "SHLVL", "1");
	temp = getcwd(NULL, 0);
	ft_setenv(data, "PWD", temp);
	free(temp);
	ft_setenv(data, "OLDPWD", NULL);
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

bool	ft_setenv(t_data *data, char *name, char *value)
{
	char	**content;

	if (!env_name_valid(name))
		return (false);
	ft_unsetenv(data, name);
	content = malloc(2 * sizeof(char *));
	content[0] = ft_strdup(name);
	if (value)
		content[1] = ft_strdup(value);
	else
		content[1] = NULL;
	ft_lstadd_back(&data->envp, ft_lstnew(content));
	return (true);
}

bool	ft_setenv_parse(t_data *data, char *env)
{
	size_t	sep;
	char	*name;
	bool	result;

	sep = (size_t) ft_strchr(env, '=');
	if (sep == 0)
		sep = ft_strlen(env);
	else
		sep -= (size_t) env;
	name = ft_memdup(env, sep + 1);
	name[sep] = 0;
	if (env[sep] != 0)
		result = ft_setenv(data, name, env + sep + 1);
	else
		result = ft_setenv(data, name, NULL);
	free(name);
	return (result);
}

bool	ft_unsetenv(t_data *data, char *name)
{
	int	i;

	if (!env_name_valid(name))
		return (false);
	i = ft_lstindex(data->envp, name, env_cmp);
	if (i != -1)
		ft_lstdeli(&data->envp, i, free_env);
	return (true);
}
