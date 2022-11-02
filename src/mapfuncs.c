/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:38:12 by amaria-d          #+#    #+#             */
/*   Updated: 2022/11/02 14:46:06 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

// TODO: get ezequiel recursive func to not have to use t_list
char    **mapToMatrix(char *filename)
{
    int     fd;
    char    *line;
    t_list  *list;
    t_list  *tmp;
    char    **matrix;

    // first gonna hv to check if map is okay
    fd = open(filename, O_RDONLY);
    list = NULL;
    line = get_next_line(fd);
    while (line)
    {
        tmp = ft_lstnew(line);
        if (!tmp)
            exit(0);
        ft_lstadd_back(&list, tmp);
        line = get_next_line(fd);
    }
    matrix = ft_lsttoarr(list);
    ft_lstclear(&list, ft_nothing);
    return (matrix);
}

intdraw_map()