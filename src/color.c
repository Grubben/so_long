/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:40:09 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/15 15:45:51 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	intbin_append(int *color, unsigned char fam)
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

static void	imgtowin(t_info *worldata, t_img *imgp, int i, int j)
{
	mlx_put_image_to_window(worldata->mlx, worldata->win.ptr, imgp->ptr, i * worldata->pixels, j * worldata->pixels);
}

int draw_map(t_info *wrldt)
{
	size_t  j;
	size_t  i;
	char    type;

	mlx_clear_window(wrldt->mlx, wrldt->win.ptr);
	j = 0;
	while (wrldt->matrixmap[j] != NULL)
	{
		i = 0;
		type = wrldt->matrixmap[j][i];
		while (type != '\0')
		{
			if (type == EMPTY)
				imgtowin(wrldt, &wrldt->imgempty, i, j);
				// mlx_put_image_to_window(wrldt->mlx, wrldt->win.ptr,wrldt->imgempty.ptr, i*wrldt->pixels, j*wrldt->pixels);
			else if (type == WALL)
				imgtowin(wrldt, &wrldt->imgwall, i, j);
				// mlx_put_image_to_window(wrldt->mlx, wrldt->win.ptr, wrldt->imgwall.ptr, i*wrldt->pixels, j*wrldt->pixels);
			else if (type == COLLECT)
				imgtowin(wrldt, &wrldt->imgcoll, i, j);
				// mlx_put_image_to_window(wrldt->mlx, wrldt->win.ptr, wrldt->imgcoll.ptr, i*wrldt->pixels, j*wrldt->pixels);
			else if (type == EXIT)
				imgtowin(wrldt, &wrldt->imgexit, i, j);
				// mlx_put_image_to_window(wrldt->mlx, wrldt->win.ptr, wrldt->imgexit.ptr, i*wrldt->pixels, j*wrldt->pixels);
			i++;
			type = wrldt->matrixmap[j][i];
		}
		j++;
	}
	if (wrldt->move_printb)
		mlx_string_put(wrldt->mlx, wrldt->win.ptr, 450, 15, rgbToColor(0, 255, 255), wrldt->smvs);
	mlx_put_image_to_window(wrldt->mlx, wrldt->win.ptr, wrldt->imgplyr.ptr,
		wrldt->ppos_x * wrldt->pixels, wrldt->ppos_y * wrldt->pixels);
	return (1);
}
