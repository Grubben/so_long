/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:10:33 by amc               #+#    #+#             */
/*   Updated: 2022/11/04 18:25:59 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

#include <stdio.h>


int	windestroy(t_info *main)
{
	mlx_destroy_window(main->mlx, main->win);
	exit(0);
}

int	keyboardPrinter(int keycode, t_info *worldata)
{
	if (keycode == 'w')
	{
		move_player(0, 1, 1, worldata);
		printf("w\n");
	}
	else if (keycode == 'a')
	{
		move_player(-1, 0, 1, worldata);
		printf("a\n");
	}
	else if (keycode == 's')
	{
		move_player(0, -1, 1, worldata);
		printf("s\n");
	}
	else if (keycode == 'd')
	{
		move_player(1, 0, 1, worldata);
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
	static int           frame = 0;
	
	if (frame == 1600)
	{
	      draw_map(main);
	     frame = 0;
	 }
	frame++;
	return (frame);
	// usleep(6000);
	// draw_map(main);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	main;

	if (argc > 1)
		main.matrixmap = matrix_maker(argv[1]);
	else
		return (0);
		
	if (!matrixmap_checkp(main.matrixmap))
	{
		free(main.matrixmap);
		ft_printf("Map wrong\n");
		return (0);
	}

	placeplayer_p(&main);
	// if (!vldpath_checkerp(&main))
	// {
	// 	free(main.matrixmap);
	// 	ft_printf("No valid path\n");
	// 	return (0);
	// }
	// else
	// 	ft_printf("Map has Valid Path\n");

	main.mlx = mlx_init();
	main.PIXELS = 32;	
	
	main.SIZE_X = main.PIXELS * ft_strlen(*main.matrixmap);
	main.SIZE_Y = main.PIXELS * ft_strlen(*main.matrixmap);
	main.win = mlx_new_window(main.mlx, main.SIZE_X, main.SIZE_Y, "So Long");
	
	main.n_moves = 0;
	main.move_printb = 0;
	if (main.move_printb)
		main.strmoves = ft_itoa(0);


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

	matrixmap_printer(main.matrixmap);

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
