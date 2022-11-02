/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/02 15:02:14 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"


// Ezequiel
char    **aux(int fd, char **map, size_t count)
{
    char *line;

    line = get_next_line(fd);

    if (line)
        map = aux(fd, map, count+1);
    else
    {
        map = malloc(sizeof(char *) * (count + 1));
        if (!map)
            exit(0);
    }
    map[count] = line;
    return (map);
}

char    **matrix_maker(char *filename)
{
    int     fd;
    char    **matrix;

    // first gonna hv to check if map is okay
    fd = open(filename, O_RDONLY);

    matrix = aux(fd, NULL, 0);
    return (matrix);
    
}

int draw_map()
{

}
