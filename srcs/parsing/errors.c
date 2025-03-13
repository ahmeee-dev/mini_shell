/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:58 by apintaur          #+#    #+#             */
/*   Updated: 2025/03/13 00:19:22 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	*ft_ssdestroy(char **ss);

int	ms_invalidinput(char *line, char **split, t_node *ast, int i)
{
	if (ms_isredir || ms_isop(split[i]))
		ft_printf("sintax error in '%s'", split[i]);
	else
		ft_printf("Command '%s' not found.\n", split[0]);
	if (line)
		free (line);
	ft_ssdestroy(split);
	ft_ast_destroy(ast);
	return (0);
}

void	ms_error(t_node *ast)
{
	ft_ast_destroy(ast);
	exit (EXIT_FAILURE);
}
