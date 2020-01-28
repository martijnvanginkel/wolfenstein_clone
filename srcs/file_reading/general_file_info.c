/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_file_info.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 15:21:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/28 17:48:18 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void        loop_empty_space(char *file_string, int *index)
{
    while (file_string[*index] != '\0')
    {  
        while (file_string[*index] == ' ' || file_string[*index] == '\n')
            (*index)++;
        return ;
    }
}

t_id_tuple *initialize_tuple_list()
{
    t_id_tuple *id_list;

    id_list = (t_id_tuple *)malloc(sizeof(t_id_tuple) * 9);
    if (!id_list)
        return (0);
    id_list[0].identifier = "R ";
    id_list[0].function = &find_resolution;
    id_list[1].identifier = "NO ";
    id_list[1].function = &find_texture;
    id_list[2].identifier = "SO ";
    id_list[2].function = &find_texture;
    id_list[3].identifier = "WE ";
    id_list[3].function = &find_texture;
    id_list[4].identifier = "EA ";
    id_list[4].function = &find_texture;
    id_list[5].identifier = "S ";
    id_list[5].function = &find_texture;
    id_list[6].identifier = "F ";
    id_list[6].function = &find_color;
    id_list[7].identifier = "C ";
    id_list[7].function = &find_color;
    id_list[8].identifier = 0;
    return (id_list);
}

int            link_struct_value(t_id_tuple *id_tuple, t_file_data *file_data)
{
    id_tuple->value = (void **)malloc(sizeof(void *) * 1);
    if (!id_tuple->value)
        return (0);
    if (same_string(id_tuple->identifier, "R ", 2))
        file_data->resolution = (int **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "NO ", 3))
        file_data->north_texture = (char **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "SO ", 3))
        file_data->south_texture = (char **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "WE ", 3))
        file_data->west_texture = (char **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "EA ", 3))
        file_data->east_texture = (char **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "S ", 2))
        file_data->sprite_texture = (char **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "F ", 2))
        file_data->floor_color = (int **)id_tuple->value;
    else if (same_string(id_tuple->identifier, "C ", 2))
        file_data->ceiling_color = (int **)id_tuple->value;
    else
        return (0);
    return (1);
}

/* Function that looks which identifier matches the start of the line and returns 0 on nothing found */
int             fits_identifier(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_list)
{
    int         i;
    int         id_strlen;

    i = 0;
    while (id_list[i].identifier != 0)
    {
        id_strlen = get_strlen(id_list[i].identifier);
        if (same_string(&(file_string[*index]), id_list[i].identifier, id_strlen))
        {
            if (!link_struct_value(&(id_list[i]), file_data))
                return (0);
            (*index) += id_strlen;
            if (!id_list[i].function(file_string, index, file_data, &(id_list)[i]))
                return (0);
            return (1);
        }
        i++;
    }
    return (0);
}

/* Function that collects all the information */
int            get_general_info(t_file_data *file_data)
{
    int         index;
    t_id_tuple  *id_list;

    index = 0;
    id_list = initialize_tuple_list();
    if (!id_list)
        return (0);
    while (all_info_filled(file_data) == 0)
    {
        if (is_empty_line(file_data->full_file, index))
            loop_empty_space(file_data->full_file, &index);
        else
        {
            if (!fits_identifier(file_data->full_file, &index, file_data, id_list)) /* Line didnt match any identifiers */
                return (0);                
            else /* Returned function with success */
            {

            }       
        }
    }
    
	print_file_data(file_data);
    return (1);
}