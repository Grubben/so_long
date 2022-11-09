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

int	chngaround_topstart(size_t x, size_t y, char **mtrxcpy)
{
	int	succesfulb;

	succesfulb = 0;
	if (mtrxcpy[y - 1][x] == EMPTY || mtrxcpy[y - 1][x] == COLLECT)
	{
		mtrxcpy[y - 1][x] = PSTARTPOS;
		succesfulb = 1;
	}

	if (mtrxcpy[y][x + 1] == EMPTY || mtrxcpy[y][x + 1] == COLLECT)
	{
		mtrxcpy[y][x + 1] = PSTARTPOS;
		succesfulb = 1;
	}

	if (mtrxcpy[y + 1][x] == EMPTY || mtrxcpy[y + 1][x] == COLLECT)
	{
		mtrxcpy[y + 1][x] = PSTARTPOS;
		succesfulb = 1;
	}

	if (mtrxcpy[y][x - 1] == EMPTY || mtrxcpy[y][x - 1] == COLLECT)
	{
		mtrxcpy[y][x - 1] = PSTARTPOS;		
		succesfulb = 1;
	}
	return (succesfulb);
}

int		mtrxpassall(char **mtrxcpy)
{
	int		go_again;
	size_t	j;
	size_t	i;

	go_again = 1;
	while (go_again)
	{
		go_again = 0;
		j = 1;
		while (mtrxcpy[j])
		{
			i = 1;
			while (mtrxcpy[j][i])
			{
				if (mtrxcpy[j][i] == PSTARTPOS)
				{
					if (chngaround_topstart(i, j, mtrxcpy))
						go_again = 1;
				}
				i++;
			}
			j++;
		}
	}
	return (1);
}















int		vldpath_checkerp(t_info *worldata)
{
	// return (pthchk(worldata->ppos_x, worldata->ppos_y, worldata->matrixmap));
	char	**mtrxcpy;

	mtrxcpy = (char **)mtrxmap_cpy(worldata->matrixmap);
	if (!mtrxcpy)
		return (0);
	mtrxpassall(mtrxcpy);
	return (1);
}