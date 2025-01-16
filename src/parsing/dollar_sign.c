/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:08:58 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/16 15:00:41 by dvan-hum         ###   ########.fr       */
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

static char	*envp(t_data *data, char *venvp)
{
	char	*new;

	new = ft_or(ft_getenv(data, venvp), "");
	free(venvp);
	return (ft_strdup(new));
}

char	*set_venvps(t_data *data, char *line)
{
	char	*new_line;
	char	*venvp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	new_line = ft_calloc(1, 1);
	while (line[i])
	{
		if (line[i] == '$' && !in_quotes(line, i, '\'')
			&& ft_isalnum(line[i + 1]))
		{
			new_line = join_and_free(new_line, ft_substr(line, k, i - k));
			i++;
			j = 0;
			while (ft_isalnum(line[i + j]))
				j++;
			venvp = ft_substr(line, i, j);
			new_line = join_and_free(new_line, envp(data, venvp));
			i += j;
			k = i;
		}
		else
			i++;
	}
	new_line = join_and_free(new_line, ft_substr(line, k, i));
	return (free(line), new_line);
}
