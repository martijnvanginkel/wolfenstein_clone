/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 11:53:34 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/29 10:24:12 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/* Joins a newly read line to the string that contains the entire file content */
void            glue_lines(char **full_file, char *read_line)
{
    char *temp;

    temp = *full_file;
    *full_file = strjoin(*full_file, read_line);
    free(temp);
    free(read_line);
}

/* Reads the content out of the map.cub file and returns it as a string */
char            *read_content_from_file(char *file_name)
{
    int fd;
    char *read_line;
    char *full_file;
    char *temp;

    read_line = NULL;
    full_file = make_empty_string();
    fd = open("srcs/map.cub", O_RDONLY);
    if (fd == -1)
        return (NULL);
    while (get_next_line(fd, &read_line))
    {
        glue_lines(&full_file, read_line);
    }
    glue_lines(&full_file, read_line);
    return (full_file);
}

/* Function that collects all the data from the file*/
int             collect_file_information(char *file_name)
{
    t_file_data file_data;

    file_data = empty_file_data();
    file_data.full_file = read_content_from_file(file_name);
    if (!file_data.full_file)
        return (0);

    
    // if (!get_general_info(&file_data))
    //     return (0);


    file_data.map = get_map(file_data.full_file);
	//allocate_map(file_data.full_file); // Make sure to only send the string that contains the start of the map
    if (!file_data.map)
        return (0);

    
    return (1);
}

int             main(int argc, char **argv)
{
    if (argc != 2)
    {
        show_error("Expecting only one argument");
        return (0);
    }

    if(!collect_file_information(argv[1]))
        show_error("Something went wrong collecting the data from the file");

    // while (1)
    // {
        
    // }

    return (0);
}