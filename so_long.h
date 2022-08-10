/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:20:51 by iel-moha          #+#    #+#             */
/*   Updated: 2022/08/10 23:50:59 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# define BUFFER_SIZE 1024

typedef struct var
{
	void    *mlx;
	void    *mlx_window;
	void    *img;
	int		x;
    int     y;
	int 	fd;
	char 	*tab;
	char	*temp;
	char    **map;
    int     d;
	int		p;
	int		c;
	int		i;
	int 	j;
	int		e;
	int		px;
	int		py;
	int 	is_ver;
	int		is_hor;
}	t_var;

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
void	print_free_exit(char *str, t_var *var);
void	check_map(t_var *var);
int		exit_plan(t_var *var);

# endif