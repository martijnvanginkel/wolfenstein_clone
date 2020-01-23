/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 11:53:34 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/23 11:31:38 by mvan-gin      ########   odam.nl         */
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

void    print_map(int **map, int height)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < height)
    {
        while (map[y][x] != -1)
        {
            printf("%d ", map[y][x]);
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }
}

int     get_map_height(char *content_string)
{
    int i;
    int height;

    i = 0;
    height = 0;
    while (content_string[i] != '\0')
    {
        if (content_string[i] == '\n')
        {
            height++;
        }
        i++;
    }
    height++;
    return (height);
}

int     get_map_width(char *content_string, int index)
{
    int width;

    width = 0;
    while (content_string[index] != '\0')
    {
        if (content_string[index] == '\n')
        {
            width = (width / 2) + 1;
            return (width);
        }
        index++;
        width++;
    }
    width = (width / 2) + 1;
    return (width);
}

/* Fills in the pointer to the 2D array */
void    fill_map(int ***map, int height, char *content_string)
{
    int x;
    int y;
    int index;
    int width;

    x = 0;
    y = 0;
    index = 0;
    while (y < height && content_string[index] != '\0')
    {
        width = get_map_width(content_string, index);
        (*map)[y] = (int *)malloc(sizeof(int) * (width + 1)); /* One more for the -1 at the end of each column */
        if (!(*map)[y])
            return ;
        while (x < width)
        {
            (*map)[y][x] = (content_string[index] - 48);
            index = index + 2;
            x++;
        }
        (*map)[y][x] = -1; /* Put a -1 at the end of every column */
        x = 0;
        y++;
    }
}

int     **allocate_map(char *content_string)
{
    int **map;
    int height;

    height = get_map_height(content_string);
    map = (int **)malloc(sizeof(int *) * height);
    if (!map)
        return (0);
    fill_map(&map, height, content_string);
    if (!approve_map(map, height))
        return (0);

    print_map(map, height);
    
    return (map);
}

/* Function that collects all the data from the file*/
int     collect_file_information(char *file_name)
{
    char    *file_content;
    int     **map;

    file_content = read_content_from_file(file_name);
    if (!file_content)
        return (0);
    map = allocate_map(file_content);
    if (!map)
        return (0);
    return (1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        show_error("Expecting only one argument");
        return (0);
    }

    if(!collect_file_information(argv[1]))
        show_error("Something went wrong collecting the data from the file");

    return (0);
}