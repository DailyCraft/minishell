/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:19:19 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/07 09:06:57 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_command(t_data *data, int argc, char **argv)
{
	t_list	*lst;

	(void) argc;
	(void) argv;
	lst = data->envp;
	while (lst)
	{
		printf("%s=%s\n",
			((char **) lst->content)[0],
			((char **) lst->content)[1]);
		lst = lst->next;
	}
	return (0);
}
