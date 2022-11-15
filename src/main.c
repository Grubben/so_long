/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:10:33 by amc               #+#    #+#             */
/*   Updated: 2022/11/15 15:41:53 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	destroy(t_info *worldata)
{
	mlx_destroy_window(worldata->mlx, worldata->win.ptr);
	mlx_destroy_image(worldata->mlx, worldata->imgplyr.ptr);
	mlx_destroy_image(worldata->mlx, worldata->imgempty.ptr);
	mlx_destroy_image(worldata->mlx, worldata->imgwall.ptr);
	mlx_destroy_image(worldata->mlx, worldata->imgcoll.ptr);
	mlx_destroy_image(worldata->mlx, worldata->imgexit.ptr);
	if (worldata->move_printb)
		free(worldata->smvs);
	mlx_destroy_display(worldata->mlx);
	exit(0);
	return (0);
}

int	theloop(t_info *main)
{
	static int	frame = 0;

	if (frame == 1600)
	{
		draw_map(main);
		frame = 0;
	}
	frame++;
	return (frame);
}

static void	img_init(void *mlx, t_img *fill, char *sprite)
{
	fill->ptr = mlx_xpm_file_to_image(mlx, sprite, &fill->width, &fill->height);
}

int	world_init(t_info *wrldt)
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
	wrldt->win.ptr = mlx_new_window(wrldt->mlx,
			wrldt->win.width, wrldt->win.height, "SoLong");
	img_init(wrldt->mlx, &wrldt->imgplyr,
		"player_sprites/hero1_32betterback.xpm");
	img_init(wrldt->mlx, &wrldt->imgempty, "wrldSprts/empty.xpm");
	img_init(wrldt->mlx, &wrldt->imgwall, "wrldSprts/wall.xpm");
	img_init(wrldt->mlx, &wrldt->imgcoll, "wrldSprts/coll.xpm");
	img_init(wrldt->mlx, &wrldt->imgexit, "wrldSprts/exit.xpm");
	wrldt->n_moves = 0;
	wrldt->smvs = NULL;
	wrldt->move_printb = 0;
	if (wrldt->move_printb)
		wrldt->smvs = ft_itoa(0);
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
	mlx_hook(main.win.ptr, 02, 1L << 0, keyboardPrinter, &main);
	mlx_hook(main.win.ptr, 17, 0L, destroy, &main);
	mlx_loop(main.mlx);
	return (0);
}
