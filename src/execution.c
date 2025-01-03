/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 08:18:47 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 16:28:10 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_bin(t_data *data, char *bin)
{
	char	*path_env;
	char	*path;
	char	**paths;
	int		i;

	path_env = ft_getenv(data, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strsjoin((const char *[]){paths[i], "/", bin, NULL});
		if (!path || access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free_split(paths);
	if (access(bin, F_OK) == 0)
		return (bin);
	return (NULL);
}

static int	execute_external(t_data *data, char **argv)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	path = find_bin(data, argv[0]);
	if (path)
	{
		envp = flat_envp(data);
		ft_lstclear(&data->envp, free_env);
		execve(path, argv, envp);
		errno_msg(data->program, argv[0]);
		return (126);
	}
	else
	{
		ft_lstclear(&data->envp, free_env);
		error_msg(argv[0], "command not found");
		return (127);
	}
}

static int	execute_command(t_data *data, int argc, char **argv)
{
	int	status;

	// int fd = open("test.txt", O_WRONLY);
	// dup2(fd, 1);

	if (ft_strcmp(argv[0], "echo") == 0)
		status = echo_command(data, argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		status = cd_command(data, argc, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		status = pwd_command(data, argc, argv);
	else if (ft_strcmp(argv[0], "export") == 0)
		status = export_command(data, argc, argv);
	else if (ft_strcmp(argv[0], "unset") == 0)
		status = unset_command(data, argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0)
		status = env_command(data, argc, argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
		status = exit_command(data, argc, argv);
	else
		status = execute_external(data, argv);
	return (status);
}

static int	open_output(t_data *data, t_command *command)
{
	int			fd;
	t_list		*lst;
	t_redirect	*current;
	int			flag;

	lst = command->redirects;
	fd = 1;
	while (lst)
	{
		current = (t_redirect *) lst->content;
		if (current->type != REDIRECT_OUTPUT && current->type != REDIRECT_APPEND)
		{
			lst = lst->next;
			continue;
		}
		if (fd != 1)
			close(fd);
		if (current->type == REDIRECT_OUTPUT)
			flag = O_TRUNC;
		else
			flag = O_APPEND;
		fd = open(current->value, O_CREAT | O_WRONLY | flag, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR);
		if (fd < 0)
		{
			errno_msg(data->program, current->value);
			return (-1);
		}
		lst = lst->next;
	}
	return (fd);
}

int	execute(t_data *data, t_command *command, int input_fd)
{
	int	status;
	int	output_fd;
	int	fds[2];
	int	stdin_cpy;

	output_fd = open_output(data, command);
	if (output_fd == -1)
		return (1);
	dup2(output_fd, STDOUT_FILENO);
	stdin_cpy = dup(STDIN_FILENO);
	dup2(input_fd, stdin_cpy);
	if (command->pipe)
	{
		if (pipe(fds) != 0)
		{
			errno_msg(data->program, "pipe");
			return (1);
		}
		dup2(fds[0], STDOUT_FILENO);
	}
	status = execute_command(data, command->argc, command->argv);
	dup2(stdin_cpy, STDIN_FILENO);
	close(stdin_cpy);
	if (output_fd > 2)
		close(output_fd);
	if (command->pipe)
		return (execute(data, command->pipe, fds[1]));
	return (status);
}
