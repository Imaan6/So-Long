/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_continued.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:33:02 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 08:18:15 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	valid_element(char c, t_var *var)
{
	if (c != '0' && c != '1' && c != 'C' \
	&& c != 'E' && c != 'P')
	{
		print_free_exit("arg->Map can only be \
composed of 1, 0, C, E and P.", var);
	}
}

void	valid_line(t_var *var, int i)
{
	int	k;

	k = 0;
	if (i > 0 && var->map[i + 1])
	{
		if (var->map[i][0] != '1' || \
			var->map[i][ft_strlen(var->map[i]) - 1] != '1')
			print_free_exit("Map is not surrounded by ones", var);
	}
	else
	{
		while (var->map[i][k])
		{
			if (var->map[i][k] != '1')
				print_free_exit("Map is not surrounded by ones", var);
			k++;
		}
	}
}

void	check_map(t_var *var)
{
	var->i = -1;
	var->p = 0;
	var->c = 0;
	var->e = 0;
	if (!var->map)
		print_free_exit("Empty file.", var);
	check_map_continued(var);
	if (var->p > 1 || var->e > 1)
		print_free_exit("There should be only 1 Player and 1 Exit", var);
	else if (var->p < 1 || var->c < 1 || var->e < 1)
		print_free_exit("There should be at least 1 Player, \
		1 Exit and 1 Collectible", var);
}

void	check_map_continued(t_var *var)
{
	var->i = -1;
	while (var->map[++(var->i)])
	{
		if (var->i == 0)
			var->f_line = ft_strlen(var->map[var->i]);
		else
			if (var->f_line != ft_strlen(var->map[var->i]))
				print_free_exit("Map is not rectangular", var);
		var->j = -1;
		valid_line(var, var->i);
		while (var->map[var->i][++(var->j)])
		{
			valid_element(var->map[var->i][var->j], var);
			if (var->map[var->i][var->j] == 'P')
			{
				(var->p)++;
				var->px = var->j;
				var->py = var->i;
			}
			else if (var->map[var->i][var->j] == 'C')
				(var->c)++;
			else if (var->map[var->i][var->j] == 'E')
				(var->e)++;
		}
	}
}
