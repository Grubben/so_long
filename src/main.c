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

int	main(void)
{
	// printf("%i\n", rgbToColor(127, 0, 0, 255));
	void	*connid, *winid;

	connid = mlx_init();

	winid = mlx_new_window(connid, 500, 500, "So Long");
	mlx_string_put(connid, winid, 50, 150, rgbToColor(255, 0, 0), "YAY");
	mlx_string_put(connid, winid, 50, 100, rgbToColor(0, 255, 0), "YAY");
	mlx_string_put(connid, winid, 50, 50, rgbToColor(0, 0, 255), "YAY");
	mlx_string_put(connid, winid, 50, 200, rgbToColor(255, 255, 255), "YAY");
	mlx_string_put(connid, winid, 50, 300, rgbToColor(255, 255, 0), "YAY");
	mlx_string_put(connid, winid, 50, 250, rgbToColor(255, 0, 255), "YAY");
	mlx_string_put(connid, winid, 50, 350, rgbToColor(0, 255, 255), "YAY");
	// mlx_string_put(connid, winid, 50, 400, rgbToColor(0, 0, 255), "YAY");

	
	mlx_loop(connid);

	
	return (0);
}