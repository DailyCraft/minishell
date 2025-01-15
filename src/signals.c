/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:41:00 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/15 13:30:17 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	catch_sigint(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals(int enable)
{
	if (enable)
	{
		signal(SIGINT, catch_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

int	wait_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	signals(1);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			error_msg(NULL, "Quit (core dumped)", NULL);
		else
			ft_putchar_fd('\n', 1);
	}
	return (status);
}
