/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:35:23 by endarc            #+#    #+#             */
/*   Updated: 2022/11/14 12:00:23 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Checks wether map is rectangular and closed by walls
int mtrx_checkwallsp(char **mtrxmap)
{
	size_t	lenx;
	size_t  j;
	
	// Not necessary. Already checked in main:100
	if (!mtrxmap[0])
		return (0);
	lenx = ft_strlen(mtrxmap[0]);
	if (!lenx)
		return (0);
	j = 1;
	while (mtrxmap[j] != NULL)
	{
		// Checks if rectangular
		if (ft_strlen(mtrxmap[j]) != lenx)
			return (0);
		// Checks if sided by walls
		if (mtrxmap[j][0] != WALL || mtrxmap[j][lenx-1] != WALL)
			return (0);
		j++;
	}
	// Checks if first and last row is all WALL
	if (!ft_str_isallp(mtrxmap[0], WALL) && !ft_str_isallp(mtrxmap[j-1], WALL))
		return (0);
	return (1);
}

static int	mtrx_checktiles(t_info *worldata, int *pnptr, int *enptr)
{
	size_t	j;
	size_t	i;
	
	j = 1;
	//TODO: I'm checking int the last row, which has already been checked to be all WALL
	while (worldata->matrixmap[j] != NULL)
	{
		i = 0;
		while (worldata->matrixmap[j][i] != '\0')
		{
			if (worldata->matrixmap[j][i] == COLLECT)
				worldata->n_collectibles++;
			else if (worldata->matrixmap[j][i] == EXIT)
				(*enptr)++;
			else if (worldata->matrixmap[j][i] == PSTARTPOS)
			{
				worldata->ppos_x = i;
				worldata->ppos_y = j;
				worldata->matrixmap[j][i] = EMPTY;
				(*pnptr)++;
			}
			else if (worldata->matrixmap[j][i] != EMPTY && worldata->matrixmap[j][i] != WALL)
				return (0);
			i++;
		}		
		j++;
	}
	return (1);
}

int	mtrx_checkmp(t_info *worldata)
{
	int		pn;	// how many Ps
	int		en;	// how many EXITs
	
	pn = 0;
	en = 0;
	if (!mtrx_checktiles(worldata, &pn, &en))
		return (0);
	if (!worldata->n_collectibles)
		return (0);	// Need at least 1 collectible
	if (en != 1 || pn != 1)	// Only 1 exit and startpos
		return (0);
	return (1);
}
