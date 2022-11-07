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


int	destroy(t_info *worldata)
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
		destroy(worldata);
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

int	world_init(t_info *worldata)
{
	worldata->n_collectibles = 0;
	worldata->n_collected = 0;
	if (!matrixmap_checkandsetp(worldata))
	{
		free(worldata->matrixmap);
		ft_printf("Map wrong\n");
		return (0);
	}

	placeplayer_p(worldata);

	worldata->mlx = mlx_init();
	worldata->PIXELS = 32;	
	
	worldata->win.tile_width = worldata->PIXELS * ft_strlen(*worldata->matrixmap);
	worldata->win.tile_height = worldata->PIXELS * ft_strlen(*worldata->matrixmap);
	worldata->win.tile_ptr = mlx_new_window(worldata->mlx, worldata->win.tile_width, worldata->win.tile_height, "So Long");
	
	worldata->n_moves = 0;
	worldata->move_printb = 0;
	if (worldata->move_printb)
		worldata->strmoves = ft_itoa(0);


	worldata->player.tile_ptr = mlx_xpm_file_to_image(worldata->mlx, "player_sprites/hero1_32betterback.xpm", &worldata->player.tile_width, &worldata->player.tile_height);

	worldata->empspace.tile_ptr = mlx_xpm_file_to_image(worldata->mlx, "world_sprites/empty32.xpm", &worldata->empspace.tile_width, &worldata->empspace.tile_width);
	worldata->wall.tile_ptr = mlx_xpm_file_to_image(worldata->mlx, "world_sprites/wall32.xpm", &worldata->wall.tile_width, &worldata->wall.tile_width);
	worldata->collectible.tile_ptr = mlx_xpm_file_to_image(worldata->mlx, "world_sprites/collectible32.xpm", &worldata->collectible.tile_width, &worldata->collectible.tile_width);
	worldata->mapexit.tile_ptr = mlx_xpm_file_to_image(worldata->mlx, "world_sprites/exit32.xpm", &worldata->mapexit.tile_width, &worldata->mapexit.tile_width);
	worldata->n_collected = 0;
	return (1);	
}

int	main(int argc, char *argv[])
{
	t_info	main;

	if (argc > 1)
		main.matrixmap = matrix_maker(argv[1]);
	else
		return (0);

	world_init(&main);
	matrixmap_printer(main.matrixmap);

	mlx_loop_hook(main.mlx, theloop, &main);
	// Figuring out how hooks work.
	// These 2 are (not) exactly the same
	mlx_hook(main.win.tile_ptr, 02, 1L<<0, keyboardPrinter, &main); // on key press
	// mlx_key_hook(main.win, keyboardPrinter, &main); // on key release

	mlx_hook(main.win.tile_ptr, 17, 0L, destroy, &main); // DestroyNotify of the window
	mlx_loop(main.mlx);

	
	return (0);
}
