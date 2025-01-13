/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:12:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/10 15:59:30 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_interactive(t_data *data)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		return ;
	errno_safe(data, "tcgetattr", tcgetattr(STDIN_FILENO, &term));
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	errno_safe(data, "tcsetattr", tcsetattr(STDIN_FILENO, TCSANOW, &term));
	printf("\n");
	printf(" ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n");
	printf(" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n");
	printf(" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n");
	printf(" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	printf(" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗█████");
	printf("██╗\n");
	printf(" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚════");
	printf("══╝\n                       ");
	printf("By \e[1mcgrasser\e[0m & \e[1mdvan-hum\e[0m\n\n");
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
		ft_strsjoin((const char *[]){"minishell:", result, "$ ", NULL}));
	return (result);
}

char	*ft_readline(t_data *data, char *prompt)
{
	char	*line;

	if (isatty(STDIN_FILENO))
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

void	free_gnl(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		return ;
	line = get_next_line(0);
	while (line)
		ft_free_set((void **) &line, get_next_line(0));
}
