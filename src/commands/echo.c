/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:29:29 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 11:34:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_command(t_data *data, int argc, char **argv)
{
	int	i;

	(void) data;
	i = 1;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}