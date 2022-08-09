/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:20:51 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/09 01:49:13 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct var
{
	void    *mlx;
	void    *mlx_window;
	void    *img;
	int		x;
    int     y;
	int 	fd;
	char 	*tab;
	int		i;
	char	*temp;
	char    **map;
    int     d;
}	t_var;

# define BUFFER_SIZE 1024

void	print_error(char *str);
void    ft_putstr(char *s);
int     ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, int len);
int     ft_strlen(char *s);
int     check_newline(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*get_extension(char *str);
char	**ft_split(char const *s, char c);

# endif