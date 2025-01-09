/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:43:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/09 12:56:36 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errno_msg(char *program, char *desc)
{
	char	*basename;

	basename = ft_basename(program);
	ft_putstr_fd(basename, 2);
	free(basename);
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
	char	*program;

	if (function < 0)
	{
		if (data)
			program = data->program;
		else
			program = "minishell";
		errno_msg(program, name);
		exit(1);
	}
	return (function);
}
