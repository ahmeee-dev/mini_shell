/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin@42.fr <ahabdelr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:55:37 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/04/14 13:51:46 by marvin@42.f      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_pwd(t_node *node)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path)
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
		free(path);
		g_sgl = 0;
		return (0);
	}
	write(1, "\n", 1);
	ft_output_error(node->cmd[0], " ");
	g_sgl = 1;
	free(path);
	return (-1);
}
