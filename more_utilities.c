/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 07:37:09 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 07:50:32 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_plan(t_var *var)
{
	mlx_destroy_window(var->mlx, var->mlx_window);
	free(var);
	exit(1);
}

int	actions(int key, void *var2)
{
	t_var	*var;

	var = (t_var *)var2;
	var->is_hor = 0;
	var->is_ver = 0;
	if (key == 53)
		exit_plan(var);
	if (key == 13 || key == 126)
		var->is_ver = -1;
	else if (key == 1 || key == 125)
		var->is_ver = 1;
	else if (key == 2 || key == 124)
		var->is_hor = 1;
	else if (key == 0 || key == 123)
		var->is_hor = -1;
	move_it(var);
	return (0);
}

int	ft_width(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
