/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:39:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/06 20:44:05 by cgrasser         ###   ########.fr       */
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

# define OUTPUT 1
# define APPEND 2
# define INPUT 1
# define HERE_DOC 2

typedef struct s_data
{
	char	*program;
	t_list	*envp;
	int		last_status;
}	t_data;

enum	e_type
{
	SUB_SHELL,
	COMMAND
};

typedef struct s_command	t_command;
struct	s_command
{
	enum e_type	type;
	union
	{
		char	*command_line;
		struct
		{
			int		argc;
			char	**argv;
		};	
	};
	t_list		*inputs;
	t_list		*outputs;
	t_command	*pipe;
};

char	*ft_basename(char *path);
void	ft_lstsort(t_list *lst, int (*cmp)(void *, void *));
void	free_data(t_data *data);
void	errno_msg(char *program, char *desc);
void	error_msg(char *name, char *desc);
int		errno_safe(t_data *data, char *name, int function);

int		env_cmp(void *content, void *name);
void	free_env(void *env);
char	**flat_envp(t_data *data);
void	init_envp(t_data *data, char **envp);
char	*ft_getenv(t_data *data, char *name);
int		ft_setenv(t_data *data, char *name, char *value, int overwrite);
int		ft_setenv_parse(t_data *data, char *env, int overwrite);
int		ft_unsetenv(t_data *data, char *name);

int		execute(t_data *data, t_command *process);
int		run_command(t_data *data, t_command *command, int in_fork);
int		execute_pipeline(t_data *data, t_command *command, int input_fd);
int		open_output(t_data *data, t_command *command);
char	*resolve_path(t_data *data, char *bin);

int		echo_command(t_data *data, int argc, char **argv);
int		cd_command(t_data *data, int argc, char **argv);
int		pwd_command(t_data *data, int argc, char **argv);
int		export_command(t_data *data, int argc, char **argv);
int		unset_command(t_data *data, int argc, char **argv);
int		env_command(t_data *data, int argc, char **argv);
int		exit_command(t_data *data, int argc, char **argv);

t_command	*command_new(enum e_type type, t_list *inputs, t_list *outputs);
void		set_command_line(t_command *command, char *command_line);
void		set_command_argv(t_command *command, char **argv);
void		command_add_pipe(t_command **command, t_command *pipe);

void		clear_command(void *command);

t_btree		*parse_input(char *input);

void		minishell(t_data *data);

#endif
