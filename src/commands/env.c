/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:19:19 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/24 14:02:35 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_command(t_data *data)
{
	t_list	*lst;

	lst = data->envp;
	while (lst)
	{
		if (((char **) lst->content)[1])
		{
			printf("%s=%s\n",
				((char **) lst->content)[0],
				((char **) lst->content)[1]);
		}
		lst = lst->next;
	}
	return (EXIT_SUCCESS);
}
