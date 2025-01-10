/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:12:27 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/10 14:12:53 by dvan-hum         ###   ########.fr       */
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

char	*ft_readline(char *prompt)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		return (readline(prompt));
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
