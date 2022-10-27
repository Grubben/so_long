/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/10/27 12:40:35 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char    *mapToMatrix(char *filename)
{
    int     fd;
    char    *firstline;
    int     linelen;
    
    // first gonna hv to check if map is okay
    fd = open(filename, O_RDONLY);
    firstline = get_next_line(fd);
    linelen = ft_strlen(firstline);
    return (firstline);
}