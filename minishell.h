/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:39:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/02 11:27:12 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <term.h>
//# include <termios.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_data
{
	t_list	*envp;
}	t_data;

void	init_envp(t_data *data, char **envp);

void	echo_command(t_data *data, int argc, char **argv);
void	cd_command(t_data *data, int argc, char **argv);
void	pwd_command(t_data *data, int argc, char **argv);
void	export_command(t_data *data, int argc, char **argv);
void	unset_command(t_data *data, int argc, char **argv);
void	env_command(t_data *data, int argc, char **argv);
void	exit_command(t_data *data, int argc, char **argv);

#endif