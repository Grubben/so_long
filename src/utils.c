/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:25:23 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/15 18:26:28 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


/* Functional Paradigm
 * Data can be anything. The func function has to know how to deal with it
 * The (void *) is the data that the function receives
*/
int	func_charmtrxdo(char **mtrx, void *data, int (*func)(char, void *, size_t, size_t))
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
	// Anything that's not a 0 is a success
	return (accumulate);
}
