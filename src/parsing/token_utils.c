/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:00:22 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/21 14:15:04 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *token)
{
	free(((t_token *) token)->value);
	free(token);
}

void	free_token_list(void *tokens)
{
	ft_lstclear((t_list **) &tokens, free_token);
}

void	*dup_token(void *token)
{
	t_token	*dup;

	dup = ft_memdup(token, sizeof(t_token));
	dup->value = ft_strdup(dup->value);
	return (dup);
}
