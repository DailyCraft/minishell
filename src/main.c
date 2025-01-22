/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:38:42 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 16:01:53 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iterate_line(t_data *data)
{
	t_line		*line;
	t_list		*tokens;
	t_command	*command;

	line = data->line;
	tokens = line->ands;
	while (tokens)
	{
		command = parse_command(data, tokens->content);
		if (execute(data, command) == 0)
			tokens = tokens->next;
		else
		{
			line = line->or;
			if (line)
				tokens = line->ands;
			else
			{
				free_command(command);
				break ;
			}
		}
		free_command(command);
	}
}

static void	loop(t_data *data)
{
	char	*input;

	input = ft_readline(data, NULL);
	while (input)
	{
		if (isatty(STDIN_FILENO) && !is_empty_command_line(input))
			add_history(input);
		parse_line(data, input);
		free(input);
		if (data->line)
			iterate_line(data);
		free_line(&data->line);
		input = ft_readline(data, NULL);
	}
	if (isatty(STDIN_FILENO))
	{
		rl_clear_history();
		printf("exit\n");
	}
}

int	main(int argc __attribute__((unused)), char **argv, char **envp)
{
	t_data	data;
	int		last_status;

	data.program = argv[0];
	data.last_status = 0;
	data.envp = NULL;
	data.line = NULL;
	init_envp(&data, envp);
	signals(1);
	print_header();
	loop(&data);
	last_status = data.last_status;
	free_data(&data, NULL);
	return (last_status);
}
