/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 08:39:30 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 15:18:04 by cgrasser         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

# define RLP_CL1 "\001\e[1;33m\002"
# define RLP_CL2 "\001\e[1;34m\002"
# define RLP_RST "\001\e[0m\002"

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

enum	e_token
{
	ARG,
	PIPE,
	LOGICAL,
	SUBSHELL,
	REDIRECT
};

typedef struct s_token
{
	enum e_token	type;
	char			*value;
}	t_token;

enum	e_type
{
	SUB_SHELL,
	COMMAND
};

typedef struct s_fds
{
	int	last_input;
	int	heredoc;
	int	input;
	int	output;
}	t_fds;

typedef struct s_command	t_command;
struct	s_command
{
	enum e_type	type;
	union
	{
		t_list	*args;
		t_list	*tokens;
	};
	t_list		*redirects;
	t_fds		fds;
	t_command	*pipe;
};

////////////////////////////////////////////////////////////////////////////////
/// -------------------------------- COMMON -------------------------------- ///
////////////////////////////////////////////////////////////////////////////////

// Environment variables
void		init_envp(t_data *data, char **envp);
char		*ft_getenv(t_data *data, char *name);
bool		ft_setenv(t_data *data, char *name, char *value);
bool		ft_setenv_parse(t_data *data, char *env);
bool		ft_unsetenv(t_data *data, char *name);

bool		env_name_valid(char *name);
int			env_cmp(void *content, void *name);
void		free_env(void *env);
char		*flat_envp(void *content);

// Error messages
void		error_msg(t_data *data, char *format, char **args);
int			errno_safe(t_data *data, char *name, int function);

// Utils
char		*ft_basename(char *path);
void		ft_lstsort(t_list *lst, int (*cmp)(void *, void *));
t_list		*ft_lstdup(t_list *lst);
char		**ft_lsttoa(t_list *lst, char *(*conv)(void *));
void		free_data(t_data *data, t_command *command);

void		print_header(void);
char		*ft_readline(t_data *data, char *prompt);
void		free_gnl(void);

void		signals(int enable);
int			wait_process(pid_t pid, int ignore_sigint);

///////////////////////////////////////////////////////////////////////////////
/// ------------------------------ Execution ------------------------------ ///
///////////////////////////////////////////////////////////////////////////////

// Execution
void		iterate_btree(t_data *data);
int			execute(t_data *data, t_command *command);
int			execute_pipeline(t_data *data, t_command *command, int input_fd);
int			run_command(t_data *data, t_command *command, int in_fork);
int			run_external(t_data *data, t_command *command, int in_fork);
int			run_sub_shell(t_data *data, t_command *command, int in_fork);

// Redirections
bool		apply_redirections(t_data *data, t_command *command);
bool		apply_heredocs(t_data *data, t_command *command);

// Utils
bool		isdir(char *path);
char		*resolve_path(t_data *data, char *child);

// Built-in commands
int			cd_command(t_data *data, t_list *args);
int			echo_command(t_list *args);
int			env_command(t_data *data);
int			exit_command(t_data *data, t_command *command, t_list *args);
int			export_command(t_data *data, t_list *args);
int			pwd_command(void);
int			unset_command(t_data *data, t_list *args);

///////////////////////////////////////////////////////////////////////////////
/// ------------------------------- Parsing ------------------------------- ///
///////////////////////////////////////////////////////////////////////////////

// Command
/*t_command	*parse_command(t_data *data, char *command_line);
void		free_command(void *command);
bool		is_empty_command_line(char *command_line);
char		*set_venvps(t_data *data, char *line);

// Pipe
bool		is_pipe(char *line, int index);
int			find_pipe(char *line);

// Redirection
size_t		operator_len(char *line, char c);
int			get_redirection_op(char *line);
bool		is_redirection(char *command_line);
int			set_redirections(t_data *data, t_command *command, char *line);

// Backslash
bool		is_ignored(char *line, int index);
int			nb_backslash(char *line);
char		*remove_backslash(char *line);

// Utils
char		*remove_extra_c(char *line);

// Logical
bool		is_logical(char *line, int index);
int			find_logical(char *line);

// Quotes
bool		is_quote(char *line, int index);
bool		in_quotes(char *line, int index, char quote);
bool		is_in_quotes(char *line, int index);
char		*remove_quotes(char *line);
int			count_quotes(char *line);

// Parse
void		parse_btree(t_data *data, char *input);

// Error
bool		check_unexpected(t_data *data, t_list *lst);

void		unexpected_token(t_data *data, char *token);
bool		error_file(t_data *data, char *file);
bool		error_syntax(t_data *data, char *line);
bool		error_cmd(t_data *data, char *line);

// Wildcards
bool		have_wildcards(char *line);
void		wildcards(t_command *command, char *wildcards);

// Subshell
int			subshell_level(char *line, size_t index);
int			set_subshell(t_command *command, char *line);
bool 		subshell_errors(t_data *data, char *line, int index);*/

// Token
t_list		*tokenize(char *line);
t_btree		*new_btree(t_list *tokens);
void		free_token(void *token);
void		free_token_list(void *tokens);
void		*dup_token(void *token);
t_command	*parse_command(t_list *tokens);

void		free_command(void *command);
bool		is_empty_command_line(char *command_line);
void		parse_btree(t_data *data, char *input);
char		*set_venvps(t_data *data, char *line);
int			count_quotes(char *line);
int			nb_backslash(char *line);
char		*remove_extra_c(char *line);
bool		in_quotes(char *line, int index, char quote);
bool		is_in_quotes(char *line, int index);
char		*remove_backslash(char *line);
char		*remove_quotes(char *line);
bool		is_quote(char *line, int index);
size_t		operator_len(char *line, char c);
t_list		**get_close_subshell(t_list *tokens);
int			subshell_level(t_list *lst);


//	Eroor
void		unexpected_token(t_data *data, char *token);
bool		check_valid_type(t_data *data, t_list *lst, t_token *token);
bool		check_valid_subshell(t_data *data, t_list *lst, t_token *previous, t_token *token);
bool		check_unexpected(t_data *data, t_list *lst);

#endif
