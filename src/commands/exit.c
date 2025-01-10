/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:06:46 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/10 08:18:51 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_command(t_data *data, int argc, char **argv)
{
	char	*trim;
	int		value;
	int		unclear;

	(void) data;
	if (argc > 2)
	{
		error_msg(data->program, "exit: too many arguments");
		return (1);
	}
	if (argc == 1)
		(free_data(data), exit(data->last_status));
	trim = ft_strtrim(argv[1], " \t\n\v\f\r");
	value = ft_clear_atoi(trim, &unclear);
	free(trim);
	if (unclear)
	{
		trim = ft_strsjoin((const char *[]){"exit: ", argv[1],
				": numeric argument required", NULL});
		error_msg(data->program, trim);
		free(trim);
		(free_data(data), exit(2));
	}
	(free_data(data), exit(value));
}
