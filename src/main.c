/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amc <amc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:10:33 by amc               #+#    #+#             */
/*   Updated: 2022/10/17 18:15:59 by amc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
typedef struct s_vars
{
	void	*mlx_ptr;
	void	*win_ptr;	
}				t_vars;

#include <stdio.h>
#include <stdlib.h>


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

int	keyboardPrinter(int keycode)
{
	(void)keycode;
	if (keycode == 32)
		printf("M\n");
	return (1);
}

int	windestroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	exit(0);
}

// int	ft_keyboard()

int	main(void)
{
	// printf("%i\n", rgbToColor(127, 0, 0, 255));
	// void	*connid, *winid;
	// int	mx, my;	// mouse-x and y
	t_vars	vars;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, 500, 500, "So Long");

	// mlx_string_put(connid, winid, 50, 150, rgbToColor(255, 0, 0), "YAY");
	// mlx_string_put(connid, winid, 50, 100, rgbToColor(0, 255, 0), "YAY");
	// mlx_string_put(connid, winid, 50, 50, rgbToColor(0, 0, 255), "YAY");
	// mlx_pixel_put(connid, winid, 100, 100, rgbToColor(255, 255, 255));

	// Figuring out how hooks work.
	// These 2 are exactly the same
	mlx_hook(vars.win_ptr, 2, 1L<<0, keyboardPrinter, NULL);
	// mlx_key_hook(vars.win_ptr, keyboardPrinter, NULL);

	mlx_hook(vars.win_ptr, 17, 0L, windestroy, &vars); // DestroyNotify of the window
	

	mlx_loop(vars.mlx_ptr);

	
	return (0);
}