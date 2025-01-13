/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:49:16 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/13 09:50:18 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: follow symlinks
void	pwd(t_data *data)
{
	//struct stat	pwd_dir;
	//struct stat	current_dir;
	char		*env;
	char		*cwd;

	env = ft_getenv(data, "PWD");
	cwd = getcwd(NULL, 0);
	/* if (stat(env, &pwd_dir) == 0 && lstat(cwd, &current_dir) == 0
		&& pwd_dir.st_ino == current_dir.st_ino
		&& pwd_dir.st_dev == current_dir.st_dev)
		{}
	else
		 */env = cwd;
	printf("%s\n", env);
	free(cwd);
}

int	pwd_command(t_data *data, int argc, char **argv)
{
	(void) argc;
	(void) argv;
	pwd(data);
	return (0);
}
