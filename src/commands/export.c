/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:50:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/13 11:55:13 by dvan-hum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp(void *env1, void *env2)
{
	return (ft_strcmp(((char **) env1)[0], ((char **) env2)[0]));
}

static int	no_args(t_data *data)
{
	t_list	*dup;
	t_list	*lst;

	dup = ft_lstdup(data->envp);
	ft_lstsort(dup, cmp);
	ft_lstdeli(&dup, ft_lstindex(dup, "_", env_cmp), NULL);
	lst = dup;
	while (lst)
	{
		printf("export %s=\"%s\"\n",
			((char **) lst->content)[0],
			((char **) lst->content)[1]);
		lst = lst->next;
	}
	ft_lstclear(&dup, NULL);
	return (0);
}

int	export_command(t_data *data, int argc, char **argv)
{
	int		error;
	int		i;

	if (argc == 1)
		return (no_args(data));
	error = 0;
	i = 1;
	while (i < argc)
	{
		if (ft_setenv_parse(data, argv[i]) == -1)
		{
			error_msg(data, "%m: export: '%s': not a valid identifier",
				(char *[]){argv[i]});
			error = 1;
		}
		i++;
	}
	return (error);
}
