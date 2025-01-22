/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:08:58 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/22 11:49:56 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free(char *line, char *to_join)
{
	char	*new;

	new = ft_strjoin(line, to_join);
	free(line);
	free(to_join);
	return (new);
}

static int	envp(t_data *data, char *line, char **new_line)
{
	int		i;
	char	*env;

	i = 0;
	while (ft_isalnum(line[i]))
		i++;
	if (i == 0)
	{
		*new_line = join_and_free(*new_line, ft_strdup("$"));
		return (0);
	}
	env = ft_substr(line, 0, i);
	env = ft_free_set((void **) &env, ft_or(ft_getenv(data, env), ""));
	*new_line = join_and_free(*new_line, ft_strdup(env));
	return (i);
}

char	*final_value(char *new, char *line)
{
	free(line);
	if (new[0] == 0)
		return (free(new), NULL);
	return (new);
}

char	*set_venvps(t_data *data, char *line)
{
	char	*new;
	int		i;
	int		last_envp;

	new = ft_strdup("");
	i = 0;
	last_envp = 0;
	while (line[i])
	{
		if (ft_strncmp(line + i, "$?", 2) == 0 && !in_quotes(line, i, '\''))
		{
			new = join_and_free(new, ft_substr(line, last_envp, i - last_envp));
			new = join_and_free(new, ft_itoa(data->last_status));
			last_envp = ++i + 1;
		}
		else if (line[i] == '$' && !in_quotes(line, i, '\''))
		{
			new = join_and_free(new, ft_substr(line, last_envp, i - last_envp));
			i += envp(data, line + i + 1, &new);
			last_envp = i + 1;
		}
		i++;
	}
	new = join_and_free(new, ft_substr(line, last_envp, i - last_envp));
	return (final_value(new, line));
}
