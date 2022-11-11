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
		cpy[i] = NULL;	// change NULL value to mtrx[i] for semi-shallow copy
		i++;
	}
	return (cpy);
}

char	**mtrxmap_cpy(char **matrixmap)
{
	char	**cpy;
	size_t	len;
	size_t	i;

	len = ft_mtrxlen((void **)matrixmap);
	cpy = malloc(len * (sizeof(void *) + 1));
	if (!cpy && matrixmap == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = malloc(ft_strlen(matrixmap[i]) * (sizeof(char) + 1));
		if (!cpy[i])
			return (NULL);
		ft_memcpy(cpy[i], matrixmap[i], ft_strlen(matrixmap[i]) + 1);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

int     canmoveto(int x, int y, char **mtrxcpy)
{
        if (mtrxcpy[y][x] == EMPTY || mtrxcpy[y][x] == COLLECT)
		{
			mtrxcpy[y][x] = PSTARTPOS;
			return (1);
		}
        return (0);
}

void     mtrxpass(int x, int y, char **mtrxcpy)
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

int		vldpath_checkerp(t_info *worldata)
{
	char	**mtrxcpy;
	char	type;
	size_t	j;
	size_t	i;

	mtrxcpy = (char **)mtrxmap_cpy(worldata->matrixmap);
	if (!mtrxcpy)
		return (0);

	mtrxcpy[worldata->ppos_y][worldata->ppos_x] = PSTARTPOS;
	mtrxpass(worldata->ppos_x, worldata->ppos_y, mtrxcpy);

	//TODO: verify there is a P next to E
	j = 1;
	while (mtrxcpy[j] != NULL)
	{
		i = 1;
		while (mtrxcpy[j][i] != '\0')
		{
			type = mtrxcpy[j][i];
			if (type == COLLECT)
			{
				ft_printf("Collectible at %d_%d coord is not accessible", i, j);
				return (0);
			}
			if (type == EXIT)
			{
				return (chck_around(i, j, mtrxcpy));
			}
			i++;
		}
		j++;
	}
	// if we get here, means no exit was found. Shouldn't happen
	return (0);
	
	// and no C exists
	return (1);
}
