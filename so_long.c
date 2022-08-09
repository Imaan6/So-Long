/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:32:01 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/09 01:58:49 by iel-moha         ###   ########.fr       */
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
			// if (temp[0] == '\n')
			// 	print_free_exit("empty lines in file" ,arg);
			var->tab = ft_strjoin(var->tab, var->temp);
		}
		// if (temp && temp[0] == '\n')
		// 		print_free_exit("empty lines in file" ,arg);
		var->map = ft_split(var->tab, '\n');
		free(var->tab);
		//check_map(arg);
}

int main(int ac, char **av)
{
	t_var *var;
	var = malloc(sizeof(t_var));
	int	i, j;
	i = 0;
	if (ac != 2)
		print_error("Usage: ./so_long + <file.ber>");
	else if (ft_strcmp(".ber", get_extension(av[1])))
		print_error("Invalid file extension, needs to be : .ber");
	else if (ac == 2)
	{
		read_map(var, av);
		var->d = 60;
		
		var->mlx = mlx_init();
		var->mlx_window = mlx_new_window(var->mlx, 1000, 1000, "URMOM");
		// var->img = mlx_xpm_file_to_image(var->mlx, "Images/Wall.xpm", &var->x, &var->x);
		// mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, 0, 0);
		// mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, 55, 0);
		var->y = 0;
		while(var->map[i])
		{
			j = 0;
			var->x = 0;
			while(var->map[i][j])
			{
				if(var->map[i][j] == '1')
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Wall.xpm", &var->d, &var->d);
				else if (var->map[i][j] == '0')
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Floor.xpm", &var->d, &var->d);
				else if (var->map[i][j] == 'E')
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Door.xpm", &var->d, &var->d);
				else if (var->map[i][j] == 'P' || var->map[i][j] == 'C')
				{
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Floor.xpm", &var->d, &var->d);
					mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, var->x, var->y);
					if(var->map[i][j] == 'C')
						var->img = mlx_xpm_file_to_image(var->mlx, "Images/Garbage.xpm", &var->d, &var->d);
					else if(var->map[i][j] == 'P')
					var->img = mlx_xpm_file_to_image(var->mlx, "Images/Banania.xpm", &var->d, &var->d);
				}
				mlx_put_image_to_window(var->mlx, var->mlx_window, var->img, var->x, var->y);
				var->x += 60;
				j++;
			}
			var->y += 60;
			i++;
		}
	}
	mlx_loop(var->mlx);
}