/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 04:48:41 by iel-moha          #+#    #+#             */
/*   Updated: 2022/07/22 05:34:56 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "get_next_line.h"
int     ft_strcmp(const char *s1, const char *s2)
{
        int  i;

        i = 0;
        while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
                i++;
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void    ft_putstr(char *s)
{
    int	i;

   	i = 0;
    while(s[i])
    {
        write(1, &s[i], 1);
                i++;
    }
}
void	print_error(char *str)
{
	ft_putstr("Error\n");
	ft_putstr(str);
	ft_putstr("\n");
}

char	*get_extension(char *str)
{
	int p;
	int i;

	while(str[i])
	{
		if (str[i] == '.')
			p = i;
		i++;
	}
	return (str + p);
}

int	main(int ac, char **av)
{
	int fd;
	char **map;
	char *urmom;
	int	i;
	char	*temp;
	i = 0;
	// void	*mlx_ptr;
	// void	*win_ptr;

	// mlx_ptr = mlx_init();
	// win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "deez nuts");
	// mlx_loop(mlx_ptr);
	if (ac != 2)
		print_error("Usage: ./so_long + <file.ber>");
	else if (ft_strcmp(".ber", get_extension(av[1])))
		print_error("Invalid file extension, needs to be : .ber");
	else if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if(fd == -1)
			print_error("file did not open ");
		while((temp = get_next_line(fd)) != NULL)
		{
			urmom = ft_strjoin(urmom, temp);
		}
		map = ft_split(urmom, '\n');
		check_map(map);
	}
}

void	check_map(char **map)
{
	int	i;
	int	j;
	
	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' 
			&& map[i][j] != 'E' && map[i][j] != 'P')
			{
				print_error("Map can only be composed of 1, 0, C, E and P.");
				exit(1);
			}
			j++;
		}
		i++;
	}
	check_doubles('P', map);
	check_doubles('E', map);
}

void	check_doubles(char c, char **map)
{
	int i;
	int	j;
	int checker;

	checker = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				checker++;
			j++;
		}
		i++;
	}
	if(checker > 1)
		print_error("There should be only 1 Player and 1 Exit.");
}