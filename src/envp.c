/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:45:10 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/02 11:27:40 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envp(t_data *data, char **envp)
{
	while (*envp)
	{
		ft_lstadd_back(&data->envp, ft_lstnew(*envp));
		envp++;
	}
}

// static int	find_name(const char *name)
// {
	
// }

// char	*ft_getenv(const char *name)
// {
	
// }

// int	ft_setenv(const char *name, const char *value, int overwrite)
// {
	
// }

// int ft_unsetenv(const char *name)
// {
	
// }
