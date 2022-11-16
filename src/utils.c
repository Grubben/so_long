/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:25:23 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/16 17:03:46 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Functional Paradigm
 * Data can be anything. The func function has to know how to deal with it
 * The (void *) is the data that the function receives
 * Anything that's not a 0 is a success
*/
int	mtrxdo(char **mtrx, void *data, int (*func)(char, void *, size_t, size_t))
{
	size_t	j;
	size_t	i;
	int		instant;
	int		accumulate;

	accumulate = 0;
	j = 0;
	while (mtrx[j] != NULL)
	{
		i = 0;
		while (mtrx[j][i] != '\0')
		{
			instant = func(mtrx[j][i], data, i, j);
			if (!instant)
			{
				func(mtrx[j][i], data, i, j);
				return (0);
			}
			accumulate += instant;
			i++;
		}
		j++;
	}
	return (accumulate);
}

char	**mtrxmap_cpy(char **matrixmap)
{
	char	**cpy;
	size_t	len;
	size_t	i;

	len = ft_mtrxlen((void **)matrixmap);
	cpy = malloc((len + 1) * (sizeof(void *)));
	if (!cpy && matrixmap == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = malloc((ft_strlen(matrixmap[i]) + 1) * sizeof(char));
		if (!cpy[i])
			return (NULL);
		ft_memcpy(cpy[i], matrixmap[i], ft_strlen(matrixmap[i]) + 1);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
