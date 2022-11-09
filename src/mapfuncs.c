/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/09 18:48:29 by amaria-d         ###   ########.fr       */
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

void    matrixmap_printer(char **matrixmap)
{
	size_t  j;

	j = 0;
	while (matrixmap[j] != NULL)
	{
		ft_printf("%s\n", matrixmap[j]);
		j++;
	}
	ft_printf("\n");
}
