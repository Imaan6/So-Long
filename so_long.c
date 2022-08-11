/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:32:01 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 07:47:25 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(t_var *var, char **av)
{
	var->tab = NULL;
	var->fd = open(av[1], O_RDONLY);
	if (var->fd == -1)
		print_error("file did not open ");
	var->temp = get_next_line(var->fd);
	while (var->temp != NULL)
	{
		if (var->temp[0] == '\n')
			print_free_exit("empty lines in file", var);
		var->tab = ft_strjoin(var->tab, var->temp);
		free(var->temp);
		var->temp = get_next_line(var->fd);
	}
	free(var->temp);
	var->map = ft_split(var->tab, '\n');
	free(var->tab);
	check_map(var);
}

void	map_conditions(t_var *v)
{
	if (v->map[v->i][v->j] == '1')
		v->img = mlx_xpm_file_to_image(v->mlx, \
		"Images/Wall.xpm", &v->d, &v->d);
	else if (v->map[v->i][v->j] == '0')
		v->img = mlx_xpm_file_to_image(v->mlx, "Images/Floor.xpm", \
		&v->d, &v->d);
	else if (v->map[v->i][v->j] == 'E')
		v->img = mlx_xpm_file_to_image(v->mlx, \
		"Images/Door.xpm", &v->d, &v->d);
	else if (v->map[v->i][v->j] == 'P' || v->map[v->i][v->j] == 'C')
	{
		v->img = mlx_xpm_file_to_image(v->mlx, "Images/Floor.xpm", \
		&v->d, &v->d);
		if (v->img == 0)
			print_free_exit("invalid image file", v);
		mlx_put_image_to_window(v->mlx, v->mlx_window, v->img, v->x, v->y);
		if (v->map[v->i][v->j] == 'C')
			v->img = mlx_xpm_file_to_image(v->mlx, "Images/Garbage.xpm", \
			&v->d, &v->d);
		else if (v->map[v->i][v->j] == 'P')
		v->img = mlx_xpm_file_to_image(v->mlx, "Images/Banania.xpm", \
		&v->d, &v->d);
	}
	if (v->img == 0)
		print_free_exit("invalid image file", v);
}

void	rendering_map(t_var *var)
{
	var->y = 0;
	var->i = 0;
	while (var->map[var->i])
	{
		var->j = 0;
		var->x = 0;
		while (var->map[var->i][var->j])
		{
			map_conditions(var);
			mlx_put_image_to_window(var->mlx, var->mlx_window, \
			var->img, var->x, var->y);
			var->x += 60;
			var->j++;
			mlx_destroy_image(var->mlx, var->img);
		}
		var->y += 60;
		var->i++;
	}
}

void	move_it(t_var *var)
{
	if (var->map[var->py + var->is_ver][var->px + var->is_hor] == '0' ||
	var->map[var->py + var->is_ver][var->px + var->is_hor] == 'C')
	{
		if (var->map[var->py + var->is_ver][var->px + var->is_hor] == 'C')
			(var->c)--;
		var->map[var->py][var->px] = '0';
		var->py += var->is_ver;
		var->px += var->is_hor;
		var->map[var->py][var->px] = 'P';
		rendering_map(var);
		ft_printf("%d \n", var->moves++);
	}
	else if (var->map[var->py + var->is_ver] \
	[var->px + var->is_hor] == 'E' && var->c == 0)
	{
		var->map[var->py][var->px] = '0';
		var->py += var->is_ver;
		var->px += var->is_hor;
		var->map[var->py][var->px] = 'P';
		rendering_map(var);
		exit_plan(var);
		ft_printf("%d \n", var->moves++);
	}
}

int	main(int ac, char **av)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	var->moves = 0;
	var->d = 60;
	if (ac != 2)
		print_error("Usage: ./so_long + <file.ber>");
	else if (ft_strcmp(".ber", get_extension(av[1])))
		print_error("Invalid file extension, needs to be : .ber");
	else if (ac == 2)
	{	
		read_map(var, av);
		var->mlx = mlx_init();
		var->mlx_window = mlx_new_window(var->mlx, \
		ft_strlen(var->map[0]) * 60, ft_width(var->map) * 60, "BANANIA");
		rendering_map(var);
		mlx_key_hook(var->mlx_window, actions, (void *)var);
		mlx_hook(var->mlx_window, 17, 1L << 2, exit_plan, (void *)var);
		mlx_loop(var->mlx);
	}
}
