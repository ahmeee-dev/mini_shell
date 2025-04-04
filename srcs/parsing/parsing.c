/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:29:14 by apintaur          #+#    #+#             */
/*   Updated: 2025/04/04 14:32:21 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

char	**ft_rearrange_line(t_minishell *ms, char **split);

static void	ft_get_vars(t_minishell *ms, char **split, int *i)
{
	t_env	*new_var;
	t_env	tmp;
	int		divisor;

	if (!ms || !split)
		return ;
	while (split[*i])
	{
		divisor = ft_findchr(split[*i], '=');
		if (divisor < 0)
			break ;
		tmp.name = ft_substr(split[*i], 0, divisor);
		tmp.value = ft_strdup(&split[*i][divisor + 1]);
		new_var = ft_new_env(tmp.name, tmp.value);
		if (new_var)
			ft_env_addordered(&ms->vars, new_var);
		free(tmp.name);
		free(tmp.value);
		(*i)++;
	}
}

void	ms_validate_line(t_minishell *ms, char *line)
{
	char	**split;
	int		i;

	i = 0;
	split = ms_split(line, ' ');
	ft_get_vars(ms, split, &i);
	split = ft_rearrange_line(ms, split);
	while (split[i])
	{
		if (ms_validate_cmd(ms, split, &i))
		{
			ft_printf("Validating cmd...\n");
			continue ;
		}
		else if (ms_validate_redir(ms, split, &i))
		{
			ft_printf("Validating redir...\n");
			continue ;
		}
		else if (ms_validate_op(ms, split, &i))
		{
			ft_printf("Validating op...\n");
			continue ;
		}
		else
			ft_input_error(line, ms, split, i);
	}
	ft_matrix_destroy((void **)split);
}
