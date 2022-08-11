/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:09:11 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 01:38:35 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	args_conditions(char c, va_list ap)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		i += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
		i += ft_putaddress(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		i += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		i += ft_putposnbr(va_arg(ap, unsigned int));
	else if (c == 'x')
		i += ft_puthexalow(va_arg(ap, unsigned int));
	else if (c == 'X')
		i += ft_puthexaup(va_arg(ap, unsigned int));
	else if (c == '%')
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *args, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, args);
	i = 0;
	while (*args)
	{
		if (*args == '%')
		{
			args++;
			i += args_conditions(*args, ap);
		}
		else
			i += ft_putchar(*args);
		args++;
	}
	va_end(ap);
	return (i);
}
