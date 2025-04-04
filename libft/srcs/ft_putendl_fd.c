/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apintaur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:05:10 by apintaur          #+#    #+#             */
/*   Updated: 2024/12/11 15:11:13 by apintaur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			write (fd, &(s[i]), 1);
			i++;
		}
	}
	write (fd, "\n", 1);
}
