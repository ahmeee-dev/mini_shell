/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabdelr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:06:56 by ahabdelr          #+#    #+#             */
/*   Updated: 2025/03/13 16:13:58 by ahabdelr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//da sistemare per display solo sullo standard error per il cambio dell'STDOUT
void	ft_output_error(char *command, char *info)
{
		rl_on_new_line();
		printf("%s: %s: %s", command, strerror(errno), info);
		rl_on_new_line();
		rl_redisplay();
}

void	ft_output(char *str)
{
		rl_on_new_line();
		rl_replace_line(str, 0);
		rl_redisplay();
		rl_on_new_line();
		rl_redisplay();
}