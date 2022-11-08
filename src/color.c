/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:40:09 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/08 10:42:52 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	intbin_append(int *color, unsigned char fam)
{
	*color = *color << 8;
	*color = *color | fam;
}

int	rgbToColor(unsigned char r, unsigned char g, unsigned char b)
{
	int		color;

	color = 127; // This is the hard-coded alpha value
	// Tried changing it and nothing happened so leaving it
	intbin_append(&color, r);
	intbin_append(&color, g);
	intbin_append(&color, b);
	return (color);

}

int draw_map(t_info *worldata)
{
	size_t  j;
	size_t  i;
	char    type;

	mlx_clear_window(worldata->mlx, worldata->win.tile_ptr);
	j = 0;
	while (worldata->matrixmap[j] != NULL)
	{
		i = 0;
		type = worldata->matrixmap[j][i];
		while (type != '\0')
		{
			if (type == EMPTY)
				mlx_put_image_to_window(worldata->mlx, worldata->win.tile_ptr, worldata->empspace.tile_ptr, i*worldata->pixels, j*worldata->pixels);
			else if (type == WALL)
				mlx_put_image_to_window(worldata->mlx, worldata->win.tile_ptr, worldata->wall.tile_ptr, i*worldata->pixels, j*worldata->pixels);
			else if (type == COLLECT)
				mlx_put_image_to_window(worldata->mlx, worldata->win.tile_ptr, worldata->collectible.tile_ptr, i*worldata->pixels, j*worldata->pixels);
			else if (type == EXIT)
				mlx_put_image_to_window(worldata->mlx, worldata->win.tile_ptr, worldata->mapexit.tile_ptr, i*worldata->pixels, j*worldata->pixels);
			i++;
			type = worldata->matrixmap[j][i];
		}
		j++;
	}
	if (worldata->move_printb)
		mlx_string_put(worldata->mlx, worldata->win.tile_ptr, 450, 15, rgbToColor(0, 255, 255), worldata->strmoves);
	mlx_put_image_to_window(worldata->mlx, worldata->win.tile_ptr, worldata->player.tile_ptr, worldata->ppos_x * worldata->pixels, worldata->ppos_y * worldata->pixels);
	return (1);
}
