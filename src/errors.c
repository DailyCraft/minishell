/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:43:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/23 23:40:15 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_minishell(t_data *data, char *buf)
{
	char	*value;

	if (data && data->program)
		value = data->program;
	else
		value = "minishell";
	value = ft_basename(value);
	ft_strcat(buf, value);
	free(value);
}

/**
 * The format can contains:
 *   %m: print commonly 'minishell'
 *   %s: print an argument
 *   %n: print errno message
 * All others % format are not managed.
 */
void	error_msg(t_data *data, char *format, char **args)
{
	char	*percent;
	int		arg_i;
	char	buf[4096];

	arg_i = 0;
	percent = ft_strchr(format, '%');
	ft_bzero(buf, 4096);
	while (percent)
	{
		ft_strncat(buf, format, percent - format);
		format = percent + 2;
		if (percent[1] == 'm')
			add_minishell(data, buf);
		else if (percent[1] == 's')
			ft_strcat(buf, args[arg_i++]);
		else if (percent[1] == 'n')
			ft_strcat(buf, strerror(errno));
		percent = ft_strchr(format, '%');
	}
	ft_strcat(buf, format);
	ft_strcat(buf, "\n");
	ft_putstr_fd(buf, 2);
}

int	errno_safe(t_data *data, char *name, int function)
{
	if (function < 0)
	{
		error_msg(data, "%m: %s: %n", (char *[]){name});
		exit(1);
	}
	return (function);
}
