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
	if (matrixmap[y][x] == EXIT)
	{
		return (1);
	}
	else if (matrixmap[y - 1][x] != WALL)
	{
		return (pthchk(x, y - 1, matrixmap));
	}
	else if (matrixmap[y][x + 1] != WALL)
	{
		return (pthchk(x + 1, y, matrixmap));
	}
	else if (matrixmap[y + 1][x] != WALL)
	{
		return (pthchk(x, y + 1, matrixmap));
	}
	else if (matrixmap[y][x - 1] != WALL)
	{
		return (pthchk(x - 1, y + 1, matrixmap));
	}
	return (0);
}

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
`
int		vldpath_checkerp(t_info *worldata)
{
	char	**mtrxcpy;

	mtrxcpy = (char **)mtrxmap_cpy(worldata->matrixmap);
	if (!mtrxcpy)
		return (0);

	mtrxcpy[worldata->ppos_y][worldata->ppos_x] = PSTARTPOS;
	mtrxpass(worldata->ppos_x, worldata->ppos_y, mtrxcpy);
	//TODO: verify there is a P next to E
	// and no C exists
	return (1);
}
