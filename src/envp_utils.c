/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:25:52 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/20 10:32:56 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_name_valid(char *name)
{
	bool	valid;

	if (name == NULL)
		return (0);
	valid = 1;
	name = ft_strtrim(name, " \t\n\v\f\r");
	if (*name == 0)
		valid = 0;
	free(name);
	return (valid);
}

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

char	*flat_envp(void *content)
{
	return (ft_strsjoin((const char *[]){((char **) content)[0],
		"=", ((char **) content)[1], NULL}));
}
