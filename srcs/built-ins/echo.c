/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:37:22 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:29:00 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_echo(t_node *node)
{
	int	i;
	int	type;

	i = 1;
	sgl = 0;
	type = ft_strncmp(node->cmd[1], "-n", 3);
	if (type == 0)
		i++;
	while (node->cmd[i])
	{
		if ((type != 0 && i > 1) || (type == 0 && i > 2))
			write(1, " ", 1);
		ft_printf("%s", node->cmd[i]);
		i++;
	}
	if (type != 0)
		write(1, "\n", 1);
	sgl = 0;
	return (0);
}
