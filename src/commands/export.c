/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:50:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/03 11:31:14 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp(void *env1, void *env2)
{
	return (ft_strcmp(((char **) env1)[0], ((char **) env2)[0]));
}

static int	no_args(t_data *data)
{
	t_list	*lst;

	ft_lstsort(data->envp, cmp);
	lst = data->envp;
	while (lst)
	{
		printf("declare -x %s=\"%s\"\n",
			((char **) lst->content)[0],
			((char **) lst->content)[1]);
		lst = lst->next;
	}
	return (0);
}

int	export_command(t_data *data, int argc, char **argv)
{
	int		i;

	if (argc == 1)
		return (no_args(data));
	i = 1;
	while (i < argc)
	{
		ft_setenv_parse(data, argv[i], 1);
		i++;
	}
	return (0);
}
