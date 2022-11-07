/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amc <amc@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/07 11:34:11 by amc              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Ezequiel
char    **aux(int fd, char **map, size_t count)
{
	char *line;

	line = get_next_line(fd);

	if (line)
	{
		line[ft_strlen(line)-1] = '\0';	// removes '\n'
		map = aux(fd, map, count+1);
	}
	else
	{
		map = malloc(sizeof(char *) * (count + 1));
		if (!map)
			exit(0);
	}
	map[count] = line;
	return (map);
}

char    **matrix_maker(char *filename)
{
	int     fd;
	char    **matrix;

	fd = open(filename, O_RDONLY);

	matrix = aux(fd, NULL, 0);
	return (matrix);
	
}

// Checks wether map is rectangular and closed by walls
int matrixmap_checkandsetp(t_info *worldata)
{
	char	**mtrxmap;
	size_t  lenx;
	size_t  j;
	size_t	i;
	char	type;
	int		pn;	// how many Ps
	int		en;	// how many EXITs
	
	mtrxmap = worldata->matrixmap;
	if (!mtrxmap[0])
		return (0);
	lenx = ft_strlen(mtrxmap[0]);
	if (!lenx)
		return (0);
	pn = 0;
	en = 0;
	j = 1;
	while (mtrxmap[j] != NULL)
	{
		// Checks if rectangular
		if (ft_strlen(mtrxmap[j]) != lenx)
			return (0);
		// Checks if sided by walls
		if (mtrxmap[j][0] != WALL || mtrxmap[j][lenx-1] != WALL)
			return (0);
		
		i = 0;
		type = mtrxmap[j][i];
		while (type != '\0')
		{
			if (type == PSTARTPOS)
			{
				if (pn)
					return (0);
				pn = 1;
			}
			else if (type == EXIT)
			{
				if (en)
					return (0);
				en = 1;
			}
			else if (type == COLLECT)
				worldata->n_collectibles++;
			i++;
			type = mtrxmap[j][i];
		}
		j++;
	}
	// Checks if first and last row is all WALL
	if (!ft_str_isallp(mtrxmap[0], WALL) && !ft_str_isallp(mtrxmap[j-1], WALL))
		return (0);
	if (!worldata->n_collectibles)
		return (0);	// Need at least 1 collectible
	return (1);
}

int		placeplayer_p(t_info *worldata)
{
	size_t	j;
	size_t	i;
	char	type;
	
	j = 0;
	i = 0;
	while (worldata->matrixmap[j] != NULL)
	{
		i = 0;
		type = worldata->matrixmap[j][i];
		while (type != '\0')
		{
			if (type == PSTARTPOS)
			{
				worldata->ppos_x = i;
				worldata->ppos_y = j;
				worldata->matrixmap[j][i] = EMPTY;	//Overwrites P to EMPTY
				return (1);
			}
			i++;
			type = worldata->matrixmap[j][i];
		}
		j++;
	}
	return (0);
}

// int		pthchk(int x, int y, char **matrixmap)
// {
// 	if (matrixmap[y][x] == EXIT)
// 		return (1);
// 	else if (matrixmap[y][x] == WALL)
// 		return (0);
// 	// else
// 	return (pthchk(x + 1, y, matrixmap) || pthchk(x, y + 1, matrixmap)
// 			|| pthchk(x - 1, y, matrixmap) || pthchk(x, y - 1, matrixmap) || pthchk(x - 1, y - 1, matrixmap));
// }

// int		directedchk(int x, int y, int direcx, int direcy, char **matrixmap)
// {
// 	if (matrixmap[y][x] == EXIT)
// 		return (1);
// 	else if (matrixmap[y][x] == WALL)
// 		return (
// 			directedchk(x - 1, y - 1, 0, -1, matrixmap) || directedchk(x - 1, y - 1, y + 1, 0, matrixmap)
// 		);
// 	// else
// 	return (directedchk(x + direcx, y + direcy, direcx, direcy, matrixmap));
	
// }

// // Checks if there exists a valid path between P and E
// int		vldpath_checkerp(t_info *worldata)
// {
// 	// return (pthchk(worldata->ppos_x, worldata->ppos_y, worldata->matrixmap));
// 	return (directedchk(worldata->ppos_x, worldata->ppos_y, 1, 0, worldata->matrixmap));
// }


void    matrixmap_printer(char **matrixmap)
{
	size_t  j;

	j = 0;
	while (matrixmap[j] != NULL)
	{
		ft_printf("%s\n", matrixmap[j]);
		j++;
	}
}
