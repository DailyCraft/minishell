/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:50:21 by dvan-hum          #+#    #+#             */
/*   Updated: 2025/01/22 14:52:18 by dvan-hum         ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}

static bool	check_key(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (false);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (str[i] == 0 || str[i] == '=');
}

int	export_command(t_data *data, t_list *args)
{
	int		status;
	t_list	*lst;

	if (ft_lstsize(args) == 1)
		return (no_args(data));
	status = EXIT_SUCCESS;
	lst = args->next;
	while (lst)
	{
		if (!check_key(lst->content) || !ft_setenv_parse(data, lst->content))
		{
			error_msg(data, "%m: export: `%s': not a valid identifier",
				(char *[]){lst->content});
			status = EXIT_FAILURE;
		}
		lst = lst->next;
	}
	return (status);
}
