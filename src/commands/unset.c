/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:49:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/20 09:59:13 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_data *data, t_list *args)
{
	args = args->next;
	while (args)
	{
		ft_unsetenv(data, args->content);
		args = args->next;
	}
	return (EXIT_SUCCESS);
}
