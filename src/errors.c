/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:43:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/04 15:44:06 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errno_msg(char *program, char *desc)
{
	ft_putstr_fd(ft_basename(program), 2);
	ft_putstr_fd(": ", 2);
	error_msg(desc, strerror(errno));
}

void	error_msg(char *name, char *desc)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(desc, 2);
}

int	errno_safe(t_data *data, char *name, int function)
{
	if (function < 0)
	{
		errno_msg(data->program, name);
		exit(1);
	}
	return (function);
}
