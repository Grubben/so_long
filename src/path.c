/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amc <amc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:14:18 by amc               #+#    #+#             */
/*   Updated: 2022/11/07 11:35:27 by amc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		pthchk(int x, int y, char **matrixmap)
{
	if (matrixmap[y][x] != PSTARTPOS)
	{
		return (1);
	}
	if (matrixmap[y - 1][x] != WALL)
	{
		return (pthchk(x, y - 1, matrixmap));
	}
	if (matrixmap[y][x + 1] != WALL)
	{
		return (pthchk(x + 1, y, matrixmap));
	}
	if (matrixmap[y + 1][x] != WALL)
	{
		return (pthchk(x, y + 1, matrixmap));
	}
	if (matrixmap[y][x - 1] != WALL)
	{
		return (pthchk(x - 1, y + 1, matrixmap));
	}
	return (0);
}

int		vldpath_checkerp(t_info *worldata)
{
	return (pthchk(worldata->ppos_x, worldata->ppos_y, worldata->matrixmap));
}