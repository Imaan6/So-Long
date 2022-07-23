/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-moha <iel-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:46 by iel-moha          #+#    #+#             */
/*   Updated: 2021/12/22 10:14:39 by iel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024

typedef struct coord
{
    int x_p;
    int y_p;
    int nbr_c;
    int x_e;
    int y_e;

}t_args; 

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, int len);
int		ft_strlen(char *s);
int		check_newline(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	check_map(char **map);
void	check_doubles(char c, char **map);

#endif
