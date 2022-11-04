/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/04 17:02:37 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Ezequiel
char    **aux(int fd, char **map, size_t count)
{
	char *line;

	line = get_next_line(fd);

	if (line)
	{
		line[ft_strlen(line)-1] = '\0';	// removes '\n'
		map = aux(fd, map, count+1);
	}
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

	fd = open(filename, O_RDONLY);

	matrix = aux(fd, NULL, 0);
	return (matrix);
	
}

// Checks wether map is rectangular and closed by walls
int matrixmap_checkp(char **matrixmap)
{
	size_t  lenx;
	size_t  j;
	
	if (!matrixmap[0])
		return (0);
	lenx = ft_strlen(matrixmap[0]);
	if (!lenx)
		return (0);
	j = 1;
	while (matrixmap[j] != NULL)
	{
		// Checks if rectangular
		if (ft_strlen(matrixmap[j]) != lenx)
			return (0);
		// Checks if sided by walls
		if (matrixmap[j][0] != WALL || matrixmap[j][lenx-1] != WALL)
			return (0);
		j++;
	}
	// Checks if first and last row is all WALL
	if (!ft_str_isallp(matrixmap[0], WALL) && !ft_str_isallp(matrixmap[j-1], WALL))
		return (0);

	//TODO: Have to check if there is a valid path
	return (1);
}

int		placeplayer_p(t_info *worldata)
{
	size_t	j;
	size_t	i;
	char	type;
	
	j = 0;
	i = 0;
	while (worldata->matrixmap[j] != NULL)
	{
		i = 0;
		type = worldata->matrixmap[j][i];
		while (type != '\0')
		{
			if (type == PSTARPOS)
			{
				worldata->ppos_x = i;
				worldata->ppos_y = j;
				worldata->matrixmap[j][i] = EMPTY;	//Overwrites P to EMPTY
				return (1);
			}
			i++;
			type = worldata->matrixmap[j][i];
		}
		j++;
	}
	return (0);
}

int draw_map(t_info *worldata)
{
	size_t  j;
	size_t  i;
	char    type;

	mlx_clear_window(worldata->mlx, worldata->win);
	j = 0;
	while (worldata->matrixmap[j] != NULL)
	{
		i = 0;
		type = worldata->matrixmap[j][i];
		while (type != '\0')
		{
			if (type == EMPTY)
				mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->empspace.tile_img, i*worldata->PIXELS, j*worldata->PIXELS);
			else if (type == WALL)
				mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->wall.tile_img, i*worldata->PIXELS, j*worldata->PIXELS);
			else if (type == COLLECT)
				mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->collectible.tile_img, i*worldata->PIXELS, j*worldata->PIXELS);
			else if (type == EXIT)
				mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->mapexit.tile_img, i*worldata->PIXELS, j*worldata->PIXELS);
			i++;
			type = worldata->matrixmap[j][i];
		}
		j++;
	}
	if (worldata->move_printb)
		mlx_string_put(worldata->mlx, worldata->win, 450, 15, rgbToColor(0, 255, 255), worldata->strmoves);
	mlx_put_image_to_window(worldata->mlx, worldata->win, worldata->player.tile_img, worldata->ppos_x * worldata->PIXELS, worldata->ppos_y * worldata->PIXELS);
	return (1);
}

void    matrixmap_printer(t_info *worldata)
{
	size_t  j;

	j = 0;
	while (worldata->matrixmap[j] != NULL)
	{
		ft_printf("%s\n", worldata->matrixmap[j]);
		j++;
	}
}
