/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:25:52 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/02 15:41:48 by dvan-hum         ###   ########.fr       */
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
