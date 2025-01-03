/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:49:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 12:49:05 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_data *data, int argc, char **argv)
{
	int	i;
	int	failed;

	i = 1;
	failed = 0;
	while (i < argc)
	{
		ft_unsetenv(data, argv[i]);
	}
	return (failed);
}
