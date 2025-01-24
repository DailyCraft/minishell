/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/24 09:55:21 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iterate_line(t_data *data)
{
	t_line		*line;
	t_command	*command;
	int			status;

	line = data->line;
	status = 0;
	while (line)
	{
		if (line->is_and == (status == 0))
		{
			command = parse_command(data, (t_list **) &line->tokens);
			if (!command)
			{
				data->last_status = 1;
				return ;
			}
			data->command = command;
			status = execute(data, command);
			free_command(command);
		}
		line = line->next;
	}
}

static void	loop(t_data *data)
{
	char	*input;

	input = ft_readline(data, NULL);
	while (input)
	{
		if (data->is_tty && !is_empty_command_line(input))
			add_history(input);
		parse_line(data, input);
		free(input);
		if (data->line)
			iterate_line(data);
		else if (!data->is_tty)
			break ;
		free_line(&data->line);
		input = ft_readline(data, NULL);
	}
	if (data->is_tty)
	{
		rl_clear_history();
		printf("exit\n");
	}
	free_gnl(data->is_tty);
}

int	main(int argc __attribute__((unused)), char **argv, char **envp)
{
	t_data	data;
	int		last_status;

	data.program = argv[0];
	data.envp = NULL;
	data.last_status = 0;
	data.is_tty = isatty(STDIN_FILENO);
	data.line = NULL;
	init_envp(&data, envp);
	signals(1);
	print_header(&data);
	loop(&data);
	last_status = data.last_status;
	free_data(&data, NULL);
	return (last_status);
}
