/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:06:46 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/17 16:01:01 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_command(t_data *data, t_command *command, int argc, char **argv)
{
	char	*trim;
	int		value;
	int		unclear;

	printf("exit\n");
	if (argc == 1)
		(free_data(data, command), exit(data->last_status));
	trim = ft_strtrim(argv[1], " \t\n\v\f\r");
	value = ft_clear_atoi(trim, &unclear);
	free(trim);
	if (unclear)
	{
		error_msg(data, "%m: exit: %s: numeric argument required",
			(char *[]){argv[1]});
		(free_data(data, command), exit(2));
	}
	if (argc > 2)
	{
		error_msg(data, "%m: exit: too many arguments", NULL);
		return (1);
	}
	(free_data(data, command), exit(value));
}
