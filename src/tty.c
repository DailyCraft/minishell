/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:12:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/22 21:40:47 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_header(t_data *data)
{
	if (!data->is_tty)
		return ;
	printf("\n"
		" ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n"
		" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n"
		" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n"
		" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n"
		" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		"                       By \e[1mcgrasser\e[0m & \e[1mdvan-hum\e[0m\n\n"
		);
}

static char	*gen_prompt(t_data *data)
{
	char	*result;
	char	*home;

	result = ft_getenv(data, "PWD");
	if (result)
		result = ft_strdup(result);
	else
		result = getcwd(NULL, 0);
	home = ft_getenv(data, "HOME");
	if (home)
	{
		if (ft_strncmp(result, home, ft_strlen(home)) == 0
			&& (result[ft_strlen(home)] == '/' || result[ft_strlen(home)] == 0))
		{
			ft_free_set((void **) &result,
				ft_strjoin("~", result + ft_strlen(home)));
		}
	}
	ft_free_set((void **) &result,
		ft_strsjoin((const char *[]){RLP_CL1 "minishell" RLP_RST ":" RLP_CL2,
			result, RLP_RST "$ ", NULL}));
	return (result);
}

char	*ft_readline(t_data *data, char *prompt)
{
	char	*line;

	if (data->is_tty)
	{
		if (prompt == NULL)
		{
			prompt = gen_prompt(data);
			line = readline(prompt);
			free(prompt);
			return (line);
		}
		return (readline(prompt));
	}
	line = get_next_line(STDIN_FILENO);
	if (line != NULL && ft_strchr(line, '\n') != NULL)
		ft_free_set((void **) &line, ft_substr(line, 0, ft_strlen(line) - 1));
	return (line);
}

void	free_gnl(bool is_tty)
{
	char	*line;

	if (is_tty)
		return ;
	line = get_next_line(0);
	while (line)
		ft_free_set((void **) &line, get_next_line(0));
}
