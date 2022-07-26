/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 23:54:00 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 07:56:52 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error(char *str)
{
	ft_putstr("Error\n");
	ft_putstr(str);
	ft_putstr("\n");
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*get_extension(char *str)
{
	int	p;
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			p = i;
		i++;
	}
	return (str + p);
}

void	print_free_exit(char *str, t_var *var)
{
	if (var->map)
		free(var->map);
	free(var);
	print_error(str);
}
