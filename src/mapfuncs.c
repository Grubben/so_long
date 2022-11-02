/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/02 15:34:52 by amaria-d         ###   ########.fr       */
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

void    matrixmap_printer(t_info *worldata)
{
    size_t  j;

    j = 0;
    while (worldata->matrixmap[j] != NULL)
    {
        ft_printf("%s", worldata->matrixmap[j]);
        j++;
    }
}

int draw_map(t_info *worldata)
{
    size_t  j;
    size_t  i;
    char    type;

    mlx_clear_window(worldata->mlx, worldata->win);
    mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->wall.tile_img, 0, 0);
    mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->player.tile_img, worldata->ppos_x, worldata->ppos_y);

    j = 0;
    while (worldata->matrixmap[j] != NULL)
    {
        i = 0;
        type = worldata->matrixmap[j][i];
        while (type != '\0')
        {
            //TODO: making 0, 1, ... into an enum and an arry index with corresponding images
            // would be amazing
            if (type == '1')
            {
                mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->wall.tile_img, i*worldata->BYTES, j*worldata->BYTES);
            }
            i++;
            type = worldata->matrixmap[j][i];
        }
        j++;
    }
        
    return (1);
}
