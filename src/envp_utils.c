/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:25:52 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 10:08:38 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_cmp(void *content, void *name)
{
	return (ft_strcmp(((char **) content)[0], name));
}

void	free_env(void *env)
{
	free(((char **) env)[0]);
	free(((char **) env)[1]);
	free(env);
}

char	**flat_envp(t_data *data)
{
	char	**envp;
	t_list	*lst;
	int		i;

	envp = malloc((ft_lstsize(data->envp) + 1) * sizeof(char *));
	lst = data->envp;
	i = 0;
	while (lst)
	{
		envp[i] = ft_strsjoin((const char *[]){((char **) lst->content)[0],
				"=", ((char **) lst->content)[1], NULL});
		lst = lst->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
