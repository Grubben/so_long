/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:10:33 by amc               #+#    #+#             */
/*   Updated: 2022/11/02 14:58:18 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"
typedef struct s_info
{
	void	*mlx;
	void	*win;

	unsigned int	SIZE_X;
	unsigned int	SIZE_Y;

	void			*img;

	unsigned int	ppos_x;
	unsigned int	ppos_y;

	void			*pimg;
	int				pimg_width;
	int				pimg_height;

	void			*wallimg;
	int				wallimg_width;
	int				wallimg_height;

	size_t			n_moves;
}				t_info;

#include <stdio.h>

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

int	windestroy(t_info *main)
{
	mlx_destroy_window(main->mlx, main->win);
	exit(0);
}

int	keyboardPrinter(int keycode, t_info *main)
{
	if (keycode == 'w')
	{
		main->ppos_y -= 20;
		printf("w\n");
	}
	else if (keycode == 'a')
	{
		main->ppos_x -= 20;
		printf("a\n");
	}
	else if (keycode == 's')
	{
		main->ppos_y += 20;
		printf("s\n");
	}
	else if (keycode == 'd')
	{
		main->ppos_x += 20;
		printf("d\n");
	}
	else if (keycode == 65307)
	{
		windestroy(main);
	}
	else
	{
		printf("k%i\n", keycode);
	}
	return (1);
}


int	theloop(t_info *main)
{
	static int		frame = 0;

	if (frame == 600)
	{
		mlx_clear_window(main->mlx, main->win);
		mlx_put_image_to_window(main->mlx, main->win, main->wallimg, 0, 0);
		mlx_put_image_to_window(main->mlx, main->win, main->pimg, main->ppos_x, main->ppos_y);
		// mlx_string_put(main->mlx, main->win, main->ppos_x, main->ppos_y, rgbToColor(0, 255, 255), "@");
		// mlx_destroy_image(main->mlx, main->img);
		// main->img = mlx_new_image(main->mlx, main->SIZE_X, main->SIZE_Y);
		// main->pimg = mlx_xpm_file_to_image(main->mlx, "player_sprites/hero1.xpm", &(main->pimg_width), &(main->pimg_height));
		// printf("%d__%d\n", width, height);

		frame = 0;
		printf("%d\n", frame);
	}
	frame++;
	return (frame);
}

int	main(int argc, char *argv[])
{
	// printf("%i\n", rgbToColor(127, 0, 0, 255));
	// void	*connid, *winid;
	// int	mx, my;	// mouse-x and y
	t_info	main;
	char	**matrixmap;

	if (argc > 1)
		matrixmap = matrix_maker(argv[1]);
	else
		return (0);

	main.mlx = mlx_init();
	main.SIZE_X = 500;
	main.SIZE_Y = 500;
	main.win = mlx_new_window(main.mlx, main.SIZE_X, main.SIZE_Y, "So Long");
	main.n_moves = 0;

	main.ppos_x = 10;
	main.ppos_y = 10;

	main.img = mlx_new_image(main.mlx, main.SIZE_X, main.SIZE_Y);
	main.pimg = mlx_xpm_file_to_image(main.mlx, "player_sprites/hero1.xpm", &main.pimg_width, &main.pimg_height);

	main.wallimg = mlx_xpm_file_to_image(main.mlx, "world_sprites/wall.xpm", &main.wallimg_height, &main.wallimg_height);

	// printf("%d__%d\n", width, height);


	// mlx_put_image_to_window(main.mlx, main.win, main.img, main.ppos_x, main.ppos_y);

	// mlx_string_put(main.mlx, main.win, main.ppos_x, main.ppos_y, rgbToColor(0, 255, 255), "@");


	// mlx_string_put(connid, winid, 50, 150, rgbToColor(255, 0, 0), "YAY");
	// mlx_string_put(connid, winid, 50, 100, rgbToColor(0, 255, 0), "YAY");
	// mlx_string_put(connid, winid, 50, 50, rgbToColor(0, 0, 255), "YAY");
	// mlx_pixel_put(connid, winid, 100, 100, rgbToColor(255, 255, 255));

	ft_printf("%s\n", matrixmap[0]);


	mlx_pixel_put(main.mlx, main.win, 250, 250, rgbToColor(0, 255, 255));

	mlx_loop_hook(main.mlx, theloop, &main);


	// Figuring out how hooks work.
	// These 2 are (not) exactly the same
	mlx_hook(main.win, 02, 1L<<0, keyboardPrinter, &main); // on key press
	// mlx_key_hook(main.win, keyboardPrinter, &main); // on key release

	mlx_hook(main.win, 17, 0L, windestroy, &main); // DestroyNotify of the window
	mlx_loop(main.mlx);

	
	return (0);
}
