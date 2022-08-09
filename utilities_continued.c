/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_continued.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:33:02 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/09 05:35:43 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void valid_element(char c, t_var *var)
{
	if(c != '0' && c != '1' && c != 'C' 
			&& c != 'E' && c != 'P')
	{
		print_free_exit("arg->Map can only be \
composed of 1, 0, C, E and P.", var);
	}
}

void valid_line(t_var *var,int i)
{
	int k;

	k = 0;
	if (i > 0 && var->map[i + 1])
	{
		if (var->map[i][0] != '1' || 
			var->map[i][ft_strlen(var->map[i]) - 1] != '1')
			print_free_exit("Map is not surrounded by ones", var);
	}
	else
		while(var->map[i][k])
		{
			if (var->map[i][k] != '1')
				print_free_exit("Map is not surrounded by ones", var);
			k++;
		}
}

void	check_map(t_var *var)
{
	int	i;
	int	j;
	int	f_line;
	i = -1;
	var->p = 0;
	if (!var->map)
	print_free_exit("Empty file.", var);
	while(var->map[++i])
	{
		if (i == 0)
			f_line = ft_strlen(var->map[i]);
		else
			if (f_line != ft_strlen(var->map[i]))
				print_free_exit("Map is not rectangular", var);
		j = -1;
		valid_line(var, i);
		while(var->map[i][++j])
		{
			valid_element(var->map[i][j], var);
			if (var->map[i][j] == 'P')
            {
				(var->p)++;
                var->px = j;
                var->py = i;
            }
		}
	}
	if(var->p > 1)
		print_free_exit("There should be only 1 Player.", var);
}
