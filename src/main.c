/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:10:33 by amc               #+#    #+#             */
/*   Updated: 2022/11/02 18:16:24 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

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

int	keyboardPrinter(int keycode, t_info *worldata)
{
	if (keycode == 'w')
	{
		worldata->ppos_y -= worldata->PIXELS;
		printf("w\n");
	}
	else if (keycode == 'a')
	{
		worldata->ppos_x -= worldata->PIXELS;
		printf("a\n");
	}
	else if (keycode == 's')
	{
		worldata->ppos_y += worldata->PIXELS;
		printf("s\n");
	}
	else if (keycode == 'd')
	{
		worldata->ppos_x += worldata->PIXELS;
		printf("d\n");
	}
	else if (keycode == 65307)
	{
		windestroy(worldata);
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
		draw_map(main);
		// mlx_string_put(main->mlx, main->win, main->ppos_x, main->ppos_y, rgbToColor(0, 255, 255), "@");
		// mlx_destroy_image(main->mlx, main->img);
		// main->img = mlx_new_image(main->mlx, main->SIZE_X, main->SIZE_Y);
		// main->pimg = mlx_xpm_file_to_image(main->mlx, "player_sprites/hero1.xpm", &(main->pimg_width), &(main->pimg_height));
		// printf("%d__%d\n", width, height);

		frame = 0;	
		// printf("%d\n", frame);
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

	if (argc > 1)
		main.matrixmap = matrix_maker(argv[1]);
	else
		return (0);

	main.mlx = mlx_init();
	main.PIXELS = 32;	
	main.SIZE_X = 500;
	main.SIZE_Y = 500;
	main.win = mlx_new_window(main.mlx, main.SIZE_X, main.SIZE_Y, "So Long");
	main.n_moves = 0;

	main.ppos_x = 0;
	main.ppos_y = 0;

	// main.img = mlx_new_image(main.mlx, main.SIZE_X, main.SIZE_Y);
	main.player.tile_img = mlx_xpm_file_to_image(main.mlx, "player_sprites/hero1_32betterback.xpm", &main.player.tile_width, &main.player.tile_height);

	main.empspace.tile_img = mlx_xpm_file_to_image(main.mlx, "world_sprites/empty32.xpm", &main.empspace.tile_width, &main.empspace.tile_width);
	main.wall.tile_img = mlx_xpm_file_to_image(main.mlx, "world_sprites/wall32.xpm", &main.wall.tile_width, &main.wall.tile_width);
	main.collectible.tile_img = mlx_xpm_file_to_image(main.mlx, "world_sprites/collectible32.xpm", &main.collectible.tile_width, &main.collectible.tile_width);
	main.mapexit.tile_img = mlx_xpm_file_to_image(main.mlx, "world_sprites/exit32.xpm", &main.mapexit.tile_width, &main.mapexit.tile_width);

	// printf("%d__%d\n", width, height);


	// mlx_put_image_to_window(main.mlx, main.win, main.img, main.ppos_x, main.ppos_y);

	// mlx_string_put(main.mlx, main.win, main.ppos_x, main.ppos_y, rgbToColor(0, 255, 255), "@");


	// mlx_string_put(connid, winid, 50, 150, rgbToColor(255, 0, 0), "YAY");
	// mlx_string_put(connid, winid, 50, 100, rgbToColor(0, 255, 0), "YAY");
	// mlx_string_put(connid, winid, 50, 50, rgbToColor(0, 0, 255), "YAY");
	// mlx_pixel_put(connid, winid, 100, 100, rgbToColor(255, 255, 255));

	matrixmap_printer(&main);

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
