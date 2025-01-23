/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:06:46 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/22 21:37:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_clear_atoll(const char *str, int *unclear)
{
	unsigned long long	result;
	int					neg;

	result = 0;
	neg = 1;
	*unclear = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	if (!*str)
		return (*unclear = 1, 0);
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		if (result > (unsigned long long) LLONG_MAX + (neg == -1)
			&& *unclear == 0)
			*unclear = 2;
		str++;
	}
	return (*unclear += *str != 0, result * neg);
}

int	exit_command(t_data *data, t_command *command, t_list *args)
{
	char			*trim;
	long long		value;
	int				unclear;

	if (data->is_tty)
		printf("exit\n");
	if (ft_lstsize(args) == 1)
		(free_data(data, command), exit(data->last_status));
	trim = ft_strtrim(ft_lstgeti(args, 1)->content, " \t\n\v\f\r");
	value = ft_clear_atoll(trim, &unclear);
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
