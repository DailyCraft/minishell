/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:49:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/16 15:07:11 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_command(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
		ft_unsetenv(data, argv[i++]);
	return (0);
}
