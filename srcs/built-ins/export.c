/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:14:35 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:51:40 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env_arg(char *name, char *value, t_minishell *ms)
{
	t_env	*tmp;

	tmp = ft_env_find(ms->envs, name);
	if (tmp && value)
	{
		if (tmp->value)
			free (tmp->value);
		tmp->value = value;
	}
	else
	{
		tmp = ft_env_find(ms->vars, name);
		if (tmp)
		{
			tmp = ft_new_env(tmp->name, tmp->value);
			ft_env_addordered(&ms->envs, tmp);
			return (0);
		}
		else
		{
			tmp = ft_new_env(name, value);
			ft_env_addordered(&ms->envs, tmp);
		}
	}
	return (1);
}

int	ms_export(t_node *node, t_minishell *ms)
{
	char	*name;
	char	*value;

	g_sgl = 0;
	if (node->cmd[1] == NULL)
		ft_env_print(ms->envs);
	else
	{
		name = ft_substr(node->cmd[1], 0, ft_findchr(node->cmd[1], '='));
		value = ft_substr(node->cmd[1], \
				ft_findchr(node->cmd[1], '=') + 1, ft_strlen(node->cmd[1]));
		ft_env_arg(name, value, ms);
		free (name);
		free (value);
	}
	return (0);
}
