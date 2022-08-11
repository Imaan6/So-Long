/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:21:27 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 01:43:09 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	len_a(unsigned long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (i = 1);
	while (nb > 0)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

void	ft_puthexadd(unsigned long nb)
{
	char	c;

	if (nb < 16)
	{
		if (nb < 10)
			c = nb + '0';
		else
			c = nb + ('a' - 10);
		write(1, &c, 1);
	}
	else
	{
		ft_puthexadd(nb / 16);
		ft_puthexadd(nb % 16);
	}
}

int	ft_putaddress(unsigned long nb)
{
	write (1, "0x", 2);
	ft_puthexadd(nb);
	return (len_a(nb) + 2);
}

int	ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}
