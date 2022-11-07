/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endarc <endarc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/07 17:35:19 by endarc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Ezequiel
static char    **aux(int fd, char **map, size_t count)
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
