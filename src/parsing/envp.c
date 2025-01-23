/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:08:58 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/23 14:12:10 by dvan-hum         ###   ########.fr       */
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
	while (ft_isalnum(line[i]) || line[i] == '_')
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
	return (join_and_free(new, ft_substr(line, last_envp, i - last_envp)));
}

t_list	*command_venvps(t_data *data, t_list **current)
{
	t_list	*next;
	t_list	*prev;
	char	*new;
	size_t	i;
	size_t	j;
	char	*sub;

	new = set_venvps(data, ((t_token *)(*current)->content)->value);
	next = (*current)->next;
	ft_lstdelone(*current, free_token);
	prev = NULL;
	i = 0;
	while (new[i])
	{
		if (!ft_isspace(new[i]))
		{
			j = i;
			while (new[j] && (!ft_isspace(new[j]) || is_in_quotes(new, j)))
				j++;
			sub = ft_substr(new, i, j - i);
			*current = token_new(ARG, sub);
			prev = *current;
			current = &(*current)->next;
			i = j;
		}
		else
			i++;
	}
	free(new);
	*current = next;
	return (prev);
}
