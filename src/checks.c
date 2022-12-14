/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amc <amc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:35:23 by endarc            #+#    #+#             */
/*   Updated: 2022/11/18 13:47:23 by amc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Checks wether map is rectangular and closed by walls
int	mtrx_checkwallsp(char **mtrxmp)
{
	size_t	lenx;
	size_t	j;

	if (!mtrxmp[0])
		return (0);
	lenx = ft_strlen(mtrxmp[0]);
	if (!lenx)
		return (0);
	j = 1;
	while (mtrxmp[j] != NULL)
	{
		if (ft_strlen(mtrxmp[j]) != lenx)
			return (0);
		if (mtrxmp[j][0] != WALL || mtrxmp[j][lenx - 1] != WALL)
			return (0);
		j++;
	}
	if (!ft_str_isallp(mtrxmp[0], WALL) || !ft_str_isallp(mtrxmp[j - 1], WALL))
		return (0);
	return (1);
}

int	checkconsts(char c, void *hiddendata, size_t i, size_t j)
{
	int	**data;

	data = hiddendata;
	(void)i;
	(void)j;
	if (c == EXIT)
		(*(data[1]))++;
	else if (c == PSTARTPOS)
	{
		(*(data[0]))++;
	}
	return (1);
}

int	checkstartpos(char c, void *hiddendata, size_t i, size_t j)
{
	t_info	*data;

	data = hiddendata;
	if (c == COLLECT)
	{
		data->n_collectibles++;
		return (1);
	}
	if (c == PSTARTPOS)
	{
		data->ppos_x = i;
		data->ppos_y = j;
		data->matrixmap[j][i] = EMPTY;
		return (1);
	}
	else if (c == EMPTY || c == WALL || c == EXIT)
		return (1);
	return (0);
}

int	mtrx_checkmp(t_info *worldata)
{
	int	pn;
	int	en;
	int	*parr[2];

	pn = 0;
	en = 0;
	parr[0] = &pn;
	parr[1] = &en;
	if (!mtrxdo(worldata->matrixmap, &parr, checkconsts))
		return (0);
	if (!mtrxdo(worldata->matrixmap, worldata, checkstartpos))
		return (0);
	if (!worldata->n_collectibles)
		return (0);
	if (en != 1 || pn != 1)
		return (0);
	return (1);
}
