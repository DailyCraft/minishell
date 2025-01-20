/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:06:46 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/20 09:58:00 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_command(t_data *data, t_command *command, t_list *args)
{
	char	*trim;
	int		value;
	int		unclear;

	printf("exit\n");
	if (ft_lstsize(args) == 1)
		(free_data(data, command), exit(data->last_status));
	trim = ft_strtrim(ft_lstgeti(args, 1)->content, " \t\n\v\f\r");
	value = ft_clear_atoi(trim, &unclear);
	free(trim);
	if (unclear)
	{
		error_msg(data, "%m: exit: %s: numeric argument required",
			(char *[]){ft_lstgeti(args, 1)->content});
		(free_data(data, command), exit(2));
	}
	if (ft_lstsize(args) > 2)
	{
		error_msg(data, "%m: exit: too many arguments", NULL);
		return (EXIT_FAILURE);
	}
	(free_data(data, command), exit(value));
}
