/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:32:01 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/11 01:56:12 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(t_var *var, char **av)
{
		var->tab = NULL;
		var->fd = open(av[1], O_RDONLY);
		if(var->fd == -1)
			print_error("file did not open ");
		while((var->temp = get_next_line(var->fd)) != NULL)
		{
			if (var->temp[0] == '\n')
				print_free_exit("empty lines in file" ,var);
			var->tab = ft_strjoin(var->tab, var->temp);
			free(var->temp);
		}
		if (var->temp && var->temp[0] == '\n')
				print_free_exit("empty lines in file" , var);
		var->map = ft_split(var->tab, '\n');
		free(var->temp);
		free(var->tab);
		check_map(var);
}

void	rendering_map(t_var *var)
{
	var->y = 0;
	var->i = 0;	
	while(var->map[var->i])
	{
		var->j = 0;
		var->x = 0;
		while(var->map[var->i][var->j])
		{
			if(var->map[var->i][var->j] == '1')
				var->img = mlx_xpm_file_to_image(var->mlx, "Images/Wall.xpm", &var->d, &var->d);
			else if (var->map[var->i][var->j] == '0')
				var->img = mlx_xpm_file_to_image(var->mlx, "Images/Floor.xpm", &var->d, &var->d);
			else if (var->map[var->i][var->j] == 'E')
				var->img = mlx_xpm_file_to_image(var->mlx, "Images/Door.xpm", &var->d, &var->d);
			else if (var->map[var->i][var->j] == 'P' || var->map[var->i][var->j] == 'C')
			{
				var->img = mlx_xpm_file_to_image(var->mlx, "Images/Floor.xpm", &var->d, &var->d);
				if(var->img == 0)
					print_free_exit("invalid image file", var);
				mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, var->x, var->y);
				if(var->map[var->i][var->j] == 'C')
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Garbage.xpm", &var->d, &var->d);
				else if(var->map[var->i][var->j] == 'P')
				var->img = mlx_xpm_file_to_image(var->mlx, "Images/Banania.xpm", &var->d, &var->d);
			}
			if(var->img == 0)
				print_free_exit("invalid image file", var);
			mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, var->x, var->y);
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
	if(var->map[var->py + var->is_ver][var->px + var->is_hor] == '0' ||
	 var->map[var->py + var->is_ver][var->px + var->is_hor] == 'C')
	{
		if(var->map[var->py + var->is_ver][var->px + var->is_hor] == 'C')
			(var->c)--;
		var->map[var->py][var->px] = '0';
		var->py += var->is_ver;
		var->px += var->is_hor;
		var->map[var->py][var->px] = 'P';
		rendering_map(var);
		ft_printf("%d \n", var->moves++);
	}
	else if(var->map[var->py + var->is_ver][var->px + var->is_hor] == 'E' && var->c == 0)
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

int exit_plan(t_var *var)
{
	mlx_destroy_window(var->mlx, var->mlx_window);
	free(var);
	exit(1);
}

int	actions(int key, void *var2)
{
	t_var *var = (t_var *)var2;
	
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
	return 0;
}

int	ft_width(char **s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	return(i);
}

int main(int ac, char **av)
{
	t_var *var;
	var = malloc(sizeof(t_var));
	var->moves = 0;
	if (ac != 2)
		print_error("Usage: ./so_long + <file.ber>");
	else if (ft_strcmp(".ber", get_extension(av[1])))
		print_error("Invalid file extension, needs to be : .ber");
	else if (ac == 2)
	{
		read_map(var, av);
		var->d = 60;

		var->mlx = mlx_init();
		var->mlx_window = mlx_new_window(var->mlx, ft_strlen(var->map[0]) * 60, ft_width(var->map) * 60, "BANANIA");
		rendering_map(var);
		mlx_key_hook(var->mlx_window, actions, (void *)var);
		mlx_hook(var->mlx_window, 17, 1L<<2, exit_plan, (void*)var);
		mlx_loop(var->mlx);
	}
}
