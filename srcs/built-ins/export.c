/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:14:35 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/14 13:54:32 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_export(t_node *node)
{
	int	i;

	i = 0;
	//export senza arguments
	if (node->cmd[1] == NULL)
	{
		while (environ[i] != NULL)
		{
			ft_printf("%s\n", environ[i]);
			i++;
		}
		return (0);
	}
}