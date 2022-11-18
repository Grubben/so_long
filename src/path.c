/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:01:13 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/16 17:52:21 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
void	**ft_mtrxcpy(void **mtrx)
{
	void	**cpy;
	size_t	len;
	size_t	i;

	len = ft_mtrxlen(mtrx);
	cpy = malloc(len * (sizeof(void *) + 1));
	if (!cpy && mtrx == NULL)
		return (NULL);
	i = 0;
	while (i < len + 1)
	{
		cpy[i] = NULL; // change NULL value to mtrx[i] for semi-shallow copy
		i++;
	}
	return (cpy);
}
*/

/* I added this to fix a mistake.
 * But this should never give a mistake bcs the map
 * should hv been checked well before getting here
 * if (x < 0 || y < 0)
 *     return (0);
*/
int	canmoveto(int x, int y, char **mtrxcpy)
{
	if (mtrxcpy[y][x] == EMPTY || mtrxcpy[y][x] == COLLECT)
	{
		mtrxcpy[y][x] = PSTARTPOS;
		return (1);
	}
	return (0);
}

void	mtrxpass(int x, int y, char **mtrxcpy)
{
	if (canmoveto(x, y - 1, mtrxcpy))
		(mtrxpass(x, y - 1, mtrxcpy));
	if (canmoveto(x + 1, y, mtrxcpy))
		(mtrxpass(x + 1, y, mtrxcpy));
	if (canmoveto(x, y + 1, mtrxcpy))
		(mtrxpass(x, y + 1, mtrxcpy));
	if (canmoveto(x - 1, y, mtrxcpy))
		(mtrxpass(x - 1, y, mtrxcpy));
}

int	chck_around(size_t x, size_t y, char **mtrxcpy)
{
	if (mtrxcpy[y - 1][x] == PSTARTPOS)
		return (1);
	if (mtrxcpy[y][x + 1] == PSTARTPOS)
		return (1);
	if (mtrxcpy[y + 1][x] == PSTARTPOS)
		return (1);
	if (mtrxcpy[y + 1][x - 1] == PSTARTPOS)
		return (1);
	return (0);
}

int	pthchk(char c, void *hiddendata, size_t i, size_t j)
{
	char	**data;

	data = hiddendata;
	if (c == COLLECT)
	{
		return (0);
	}
	if (c == EXIT)
	{
		if (!chck_around(i, j, data))
		{
			return (0);
		}
	}
	return (1);
}

int	vldpath_checkerp(t_info *worldata)
{
	char	**mtrxcpy;

	mtrxcpy = mtrxmap_cpy(worldata->matrixmap);
	if (!mtrxcpy)
		return (0);
	mtrxcpy[worldata->ppos_y][worldata->ppos_x] = PSTARTPOS;
	mtrxpass(worldata->ppos_x, worldata->ppos_y, mtrxcpy);
	if (!mtrxdo(mtrxcpy, mtrxcpy, pthchk))
	{
		mtrx_free(mtrxcpy);
		return (0);
	}
	mtrx_free(mtrxcpy);
	return (1);
}
