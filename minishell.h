/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:39:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 15:43:42 by dvan-hum         ###   ########.fr       */
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
# include <string.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_data
{
	char	*program;
	t_list	*envp;
}	t_data;

enum	e_redirects
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	HERE_DOC
};

typedef struct s_redirect
{
	enum e_redirects	type;
	char				*value;
}	t_redirect;

typedef struct s_command
{
	int					argc;
	char				**argv;
	struct s_command	*pipe;
	t_list				*redirects;
}	t_command;

char	*ft_basename(char *path);
void	ft_lstsort(t_list *lst, int (*cmp)(void *, void *));
void	errno_msg(char *program, char *desc);
void	error_msg(char *name, char *desc);

int		env_cmp(void *content, void *name);
void	free_env(void *env);
char	**flat_envp(t_data *data);
void	init_envp(t_data *data, char **envp);
char	*ft_getenv(t_data *data, char *name);
int		ft_setenv(t_data *data, char *name, char *value, int overwrite);
int		ft_setenv_parse(t_data *data, char *env, int overwrite);
int		ft_unsetenv(t_data *data, char *name);

int		execute(t_data *data, t_command *command, int input_fd);

int		echo_command(t_data *data, int argc, char **argv);
int		cd_command(t_data *data, int argc, char **argv);
int		pwd_command(t_data *data, int argc, char **argv);
int		export_command(t_data *data, int argc, char **argv);
int		unset_command(t_data *data, int argc, char **argv);
int		env_command(t_data *data, int argc, char **argv);
int		exit_command(t_data *data, int argc, char **argv);

#endif
