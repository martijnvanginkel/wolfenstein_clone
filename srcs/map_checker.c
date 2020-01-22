/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 11:53:34 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/22 17:43:28 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* Joins a newly read line to the string that contains the entire file content */
void    glue_lines(char **full_content, char *read_line)
{
    char *temp;

    temp = *full_content;
    *full_content = strjoin(*full_content, read_line);
    free(temp);
}

/* Reads the content out of the map.cub file and returns it as a string */
char    *read_content_from_file(char *file_name)
{
    int fd;
    char *read_line;
    char *full_content;
    char *temp;

    read_line = NULL;
    full_content = make_empty_string();
    fd = open("srcs/map.cub", O_RDONLY);
    if (fd == -1)
        return (NULL);
    while (get_next_line(fd, &read_line))
    {
        glue_lines(&full_content, read_line);
    }
    glue_lines(&full_content, read_line);
    return (full_content);
}

void    print_map(int **map, int rows, int columns)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < columns)
    {
        while (x < rows)
        {
            printf("%d ", map[y][x]);
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }
}

int     **allocate_map(int rows, int columns, char *content_string)
{
    int **map;
    int index;
    int x;
    int y;

    x = 0;
    y = 0;
    index = 0;
    map = (int **)malloc(sizeof(int *) * rows);
    if (!map)
        return (NULL);
    while (y < columns && content_string[index] != '\0')
    {
        map[y] = (int *)malloc(sizeof(int) * columns);
        while (x < rows)
        {
            map[y][x] = (content_string[index] - 48);
            printf("%d", map[y][x]);
            index = index + 2;
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }
    //print_map(map, 9, 9);
    return (map);
}

/* Function that collects all the data */
void    collect_file_information(char *file_name)
{
    char    *file_content;
    int     **map;


    file_content = read_content_from_file(file_name);
    if (!file_content)
        return ;

   map = allocate_map(9, 9, file_content);


}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_string("Expecting only one argument\n");
        return (0);
    }

    collect_file_information(argv[1]);

    return (0);
}