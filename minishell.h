/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:39:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/13 11:16:37 by dvan-hum         ###   ########.fr       */
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
# define INPUT 3
# define HERE_DOC 4

typedef struct s_data
{
	char	*program;
	t_list	*envp;
	int		last_status;
	t_btree	*btree;
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

////////////////////////////////////////////////////////////////////////////////
/// -------------------------------- COMMON -------------------------------- ///
////////////////////////////////////////////////////////////////////////////////

// Environment variables
void		init_envp(t_data *data, char **envp);
char		*ft_getenv(t_data *data, char *name);
int			ft_setenv(t_data *data, char *name, char *value);
int			ft_setenv_parse(t_data *data, char *env);
int			ft_unsetenv(t_data *data, char *name);

int			env_name_valid(char *name);
int			env_cmp(void *content, void *name);
void		free_env(void *env);
char		**flat_envp(t_data *data);

// Error messages
void		error_msg(t_data *data, char *format, char **args);
int			errno_safe(t_data *data, char *name, int function);

// Utils
char		*ft_basename(char *path);
void		ft_lstsort(t_list *lst, int (*cmp)(void *, void *));
t_list		*ft_lstdup(t_list *lst);
char		**strsdup(char **strs);
void		free_data(t_data *data);

void		init_interactive(t_data *data);
char		*ft_readline(t_data *data, char *prompt);
void		free_gnl(void);

///////////////////////////////////////////////////////////////////////////////
/// ------------------------------ Execution ------------------------------ ///
///////////////////////////////////////////////////////////////////////////////

// Execution
void		iterate_btree(t_data *data);
int			execute(t_data *data, t_command *command);
int			execute_pipeline(t_data *data, t_command *command, int input_fd);
int			run_command(t_data *data, t_command *command, int in_fork);
int			run_external(t_data *data, t_command *command, int in_fork);
int			run_sub_shell(t_data *data, char *command_line, int in_fork);

// Redirections
int			open_output(t_data *data, t_command *command);
int			open_input(t_data *data, t_command *command);
char		*get_heredoc(t_data *data, t_command *command);

// Utils
int			isdir(char *path);
char		*resolve_path(t_data *data, char *child);

// Built-in commands
int			cd_command(t_data *data, int argc, char **argv);
int			echo_command(t_data *data, int argc, char **argv);
int			env_command(t_data *data, int argc, char **argv);
int			exit_command(t_data *data, int argc, char **argv);
int			export_command(t_data *data, int argc, char **argv);
int			pwd_command(t_data *data, int argc, char **argv);
int			unset_command(t_data *data, int argc, char **argv);

void		pwd(t_data *data);

///////////////////////////////////////////////////////////////////////////////
/// ------------------------------- Parsing ------------------------------- ///
///////////////////////////////////////////////////////////////////////////////

t_command	*command_new(char *command_line);

int			is_pipe(char *command_line);
int			find_pipe(char *command_line);

int			is_here_doc(char *command_line);
int			is_append(char *command_line);
int			is_input(char *command_line);
int			is_output(char *command_line);
int			is_redirection(char *command_line);

int			set_redirections(t_command *command, char *line);

void		clear_command(void *command);

t_btree		*parse_input(t_data *data, char *input);

#endif
