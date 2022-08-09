/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:32:01 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/09 05:40:36 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(t_var *var, char **av)
{
		var->fd = open(av[1], O_RDONLY);
		if(var->fd == -1)
			print_error("file did not open ");
		while((var->temp = get_next_line(var->fd)) != NULL)
		{
			if (var->temp[0] == '\n')
				print_free_exit("empty lines in file" ,var);
			var->tab = ft_strjoin(var->tab, var->temp);
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
				mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, var->x, var->y);
				if(var->map[var->i][var->j] == 'C')
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Garbage.xpm", &var->d, &var->d);
				else if(var->map[var->i][var->j] == 'P')
				var->img = mlx_xpm_file_to_image(var->mlx, "Images/Banania.xpm", &var->d, &var->d);
			}
			mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, var->x, var->y);
			var->x += 60;
			var->j++;
		}
		var->y += 60;
		var->i++;
	}
}

// void	*actions(int key, t_var *var)
// {
// 	// if (key == 53)
//     //     exitplan(var->p);
//     if (key == 13 || key == 126)
//         move_up(var);
//     else if (key == 1 || key == 125)
//         move_down(var);
//     else if (key == 2 || key == 124)
//         move_right(var);
//     else if (key == 0 || key == 123)
//         move_left(var);
// }

// void	move_up(t_var *var)
// {
// 	if(var->map[var->px][(var->py)--] == '0')
		
// }

int main(int ac, char **av)
{
	t_var *var;
	var = malloc(sizeof(t_var));
	if (ac != 2)
		print_error("Usage: ./so_long + <file.ber>");
	else if (ft_strcmp(".ber", get_extension(av[1])))
		print_error("Invalid file extension, needs to be : .ber");
	else if (ac == 2)
	{
		read_map(var, av);
		var->d = 60;
		
		var->mlx = mlx_init();
		var->mlx_window = mlx_new_window(var->mlx, 1000, 1000, "BANANIA");
		rendering_map(var);
		//mlx_key_hook(var->mlx_window, actions, &var);
	}
	mlx_loop(var->mlx);
}