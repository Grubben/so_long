/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:10:33 by amc               #+#    #+#             */
/*   Updated: 2022/11/15 15:14:49 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

#include <stdio.h>

int destroy(t_info *worldata)
{
	mlx_destroy_window(worldata->mlx, worldata->win.tile_ptr);

	mlx_destroy_image(worldata->mlx, worldata->player.tile_ptr);
	mlx_destroy_image(worldata->mlx, worldata->empspace.tile_ptr);
	mlx_destroy_image(worldata->mlx, worldata->wall.tile_ptr);
	mlx_destroy_image(worldata->mlx, worldata->collectible.tile_ptr);
	mlx_destroy_image(worldata->mlx, worldata->mapexit.tile_ptr);
	if (worldata->move_printb)
		free(worldata->strmoves);

	mlx_destroy_display(worldata->mlx);
	exit(0);
	return (0);
}

int theloop(t_info *main)
{
	static int frame = 0;

	if (frame == 1600)
	{
		draw_map(main);
		frame = 0;
	}
	frame++;
	return (frame);
	// usleep(6000);
	// draw_map(main);
}

void	img_init(void *mlx, t_img *fill, char *sprite)
{
	fill->ptr = mlx_xpm_file_to_image(mlx, sprite, &fill->width, &fill->height);
}

int world_init(t_info *wrldt)
{
	wrldt->n_collectibles = 0;
	wrldt->n_collected = 0;
	if (!mtrx_checkwallsp(wrldt->matrixmap) || !mtrx_checkmp(wrldt))
		return (ft_printf("Error\nMap wrong\n") && 0);
	if (!vldpath_checkerp(wrldt))
		return (ft_printf("Error\nNo Valid Path\n") && 0);
	wrldt->mlx = mlx_init();
	wrldt->pixels = 32;
	wrldt->win.width = wrldt->pixels * ft_strlen(wrldt->matrixmap[0]);
	wrldt->win.height = wrldt->pixels * ft_mtrxlen((void **)(wrldt->matrixmap));
	
	wrldt->win.ptr = mlx_new_window(wrldt->mlx, wrldt->win.width, wrldt->win.height, "SoLong");
	
	img_init(wrldt->mlx, &wrldt->imgplyr, "player_sprites/hero1_32betterback.xpm");
	// wrldt->imgplyr.ptr = mlx_xpm_file_to_image(wrldt->mlx, "player_sprites/hero1_32betterback.xpm", &wrldt->imgplyr.width, &wrldt->imgplyr.height);
	img_init(wrldt->mlx, &wrldt->imgempty, "wrldSprts/empty.xpm");
	// wrldt->imgempty.ptr = mlx_xpm_file_to_image(wrldt->mlx, "wrldSprts/empty.xpm", &wrldt->imgempty.width, &wrldt->imgempty.height);
	img_init(wrldt->mlx, &wrldt->imgwall, "wrldSprts/wall.xpm");
	// wrldt->imgwall.ptr = mlx_xpm_file_to_image(wrldt->mlx, "wrldSprts/wall.xpm", &wrldt->imgwall.width, &wrldt->imgwall.height);
	img_init(wrldt->mlx, &wrldt->imgcoll, "wrldSprts/coll.xpm");
	// wrldt->imgcoll.ptr = mlx_xpm_file_to_image(wrldt->mlx, "wrldSprts/coll.xpm", &wrldt->imgcoll.width, &wrldt->imgcoll.height);
	img_init(wrldt->mlx, &wrldt->imgexit, "wrldSprts/exit.xpm");
	// wrldt->imgexit.ptr = mlx_xpm_file_to_image(wrldt->mlx, "wrldSprts/exit.xpm", &wrldt->imgexit.width, &wrldt->imgexit.height);
			
	wrldt->n_moves = 0;
	wrldt->strmoves = NULL;
	wrldt->move_printb = 0;
	if (wrldt->move_printb)
		wrldt->strmoves = ft_itoa(0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_info	main;

	if (argc > 1)
		main.matrixmap = matrix_maker(argv[1]);
	else
		return (0);
	if (!(main.matrixmap[0]))
	{
		free(main.matrixmap);
		ft_printf("Nothing inside %s\n", argv[1]);
		return (0);
	}

	matrixmap_printer(main.matrixmap);
	if (!world_init(&main))
	{
		mtrx_free(main.matrixmap);
		return (0);
	}

	mlx_loop_hook(main.mlx, theloop, &main);
	// Figuring out how hooks work.
	// These 2 are (not) exactly the same
	mlx_hook(main.win.tile_ptr, 02, 1L << 0, keyboardPrinter, &main); // on key press
	// mlx_key_hook(main.win, keyboardPrinter, &main); // on key release

	mlx_hook(main.win.tile_ptr, 17, 0L, destroy, &main); // DestroyNotify of the window
	mlx_loop(main.mlx);

	return (0);
}
