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
#include "so_long.h"

int     ft_strcmp(const char *s1, const char *s2)
{
        int  i;

        i = 0;
        while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
                i++;
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void init_args(t_args *arg)
{
	arg->map = NULL;
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
	exit(1);
}

void print_free_exit(char *str, t_args *arg)
{
	if (arg->map)
		free(arg->map);
	free(arg);
	print_error(str);
}

char	*get_extension(char *str)
{
	int p;
	int i;

	i = 0;
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
	t_args *arg;
	char *urmom;
	int	i;
	char	*temp;

	arg = malloc(sizeof(t_args));
	init_args(arg);
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
			if (temp[0] == '\n')
				print_free_exit("empty lines in file" ,arg);
			urmom = ft_strjoin(urmom, temp);
		}
		if (temp && temp[0] == '\n')
				print_free_exit("empty lines in file" ,arg);
		arg->map = ft_split(urmom, '\n');
		check_map(arg);
	}
}

void valid_element(char c, t_args *arg)
{
	if(c != '0' && c != '1' && c != 'C' 
			&& c != 'E' && c != 'P')
	{
		print_free_exit("arg->Map can only be \
composed of 1, 0, C, E and P.", arg);
	}
}

void valid_line(t_args *arg,int i)
{
	int k;

	k = 0;
	if (i > 0 && arg->map[i + 1])
	{
		if (arg->map[i][0] != '1' || 
			arg->map[i][ft_strlen(arg->map[i]) - 1] != '1')
			print_free_exit("Map is not surrounded by ones", arg);
	}
	else
		while(arg->map[i][k])
		{
			if (arg->map[i][k] != '1')
				print_free_exit("Map is not surrounded by ones", arg);
			k++;
		}
}

void	check_map(t_args *arg)
{
	int	i;
	int	j;
	int	f_line;
	i = -1;
	arg->p = 0;
	if (!arg->map)
	print_free_exit("Empty file.", arg);
	while(arg->map[++i])
	{
		if (i == 0)
			f_line = ft_strlen(arg->map[i]);
		else
			if (f_line != ft_strlen(arg->map[i]))
				print_free_exit("Map is not rectangular", arg);
		j = -1;
		valid_line(arg, i);
		while(arg->map[i][++j])
		{
			valid_element(arg->map[i][j], arg);
			if (arg->map[i][j] == 'P')
				(arg->p)++;
		}
	}
	if(arg->p > 1)
		print_free_exit("There should be only 1 Player.", arg);
}
