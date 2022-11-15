/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:20:13 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/15 17:12:33 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Checks for events(collectibles or exit)
// Returns 1 if yes, 0 if no
int	chck_events(t_info *worldata)
{
	if (worldata->matrixmap[worldata->ppos_y][worldata->ppos_x] == COLLECT)
	{
		worldata->n_collected++;
		worldata->matrixmap[worldata->ppos_y][worldata->ppos_x] = EMPTY;
		return (1);
	}
	if (worldata->matrixmap[worldata->ppos_y][worldata->ppos_x] == EXIT)
	{
		if (worldata->n_collectibles == worldata->n_collected)
		{
			destroy(worldata);
		}
	}
	return (0);
}

// Moves player in specified direction.
// If cannot, returns 0 
int	move_player(int directx, int directy, size_t quant, t_info *worldata)
{
	int	newx;
	int	newy;

	newx = worldata->ppos_x + directx * (long)quant;
	newy = worldata->ppos_y - directy * (long)quant;
	if ((newx < 0) || (newy < 0))
		return (0);
	if (worldata->matrixmap[newy][newx] == WALL)
		return (0);
	worldata->ppos_x = newx;
	worldata->ppos_y = newy;
	worldata->n_moves++;
	if (worldata->move_printb)
	{
		free(worldata->smvs);
		worldata->smvs = ft_itoa(worldata->n_moves);
		if (!worldata->smvs)
			destroy(worldata);
	}
	else
		ft_printf("%d\n", worldata->n_moves);
	chck_events(worldata);
	return (1);
}

int	keyboardprinter(int keycode, t_info *worldata)
{
	if (keycode == 'w')
	{
		move_player(0, 1, 1, worldata);
	}
	else if (keycode == 'a')
	{
		move_player(-1, 0, 1, worldata);
	}
	else if (keycode == 's')
	{
		move_player(0, -1, 1, worldata);
	}
	else if (keycode == 'd')
	{
		move_player(1, 0, 1, worldata);
	}
	else if (keycode == 65307)
	{
		destroy(worldata);
	}
	return (1);
}
