/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:43:53 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/16 18:56:01 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_minishell(t_data *data)
{
	char	*value;

	if (data && data->program)
		value = data->program;
	else
		value = "minishell";
	value = ft_basename(value);
	ft_putstr_fd(value, 2);
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

	arg_i = 0;
	percent = ft_strchr(format, '%');
	while (percent)
	{
		errno_safe(data, "write", write(2, format, percent - format));
		format = percent + 2;
		if (percent[1] == 'm')
			print_minishell(data);
		else if (percent[1] == 's')
			ft_putstr_fd(args[arg_i++], 2);
		else if (percent[1] == 'n')
			ft_putstr_fd(strerror(errno), 2);
		percent = ft_strchr(format, '%');
	}
	ft_putendl_fd(format, 2);
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
