/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:48:45 by cgrasser          #+#    #+#             */
/*   Updated: 2025/01/09 15:27:10 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc(char *limit)
{
	char	*result;
	char	*line;

	result = ft_strdup("");
	line = ft_readline("> ");
	while (line && ft_strcmp(line, limit) != 0)
	{
		ft_free_set((void **) &result,
			ft_strsjoin((const char *[]){result, line, "\n", NULL}));
		free(line);
		line = ft_readline("> ");
	}
	return (result);
}
