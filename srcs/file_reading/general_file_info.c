/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_file_info.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 15:21:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/27 14:55:10 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void        loop_empty_space(char *file_string, int *index)
{
    while (file_string[*index] != '\0')
    {  
        while (file_string[*index] == ' ' || file_string[*index] == '\t')
        {
            (*index)++;
        }
        // if (file_string[*index] == '\n')
        // {
        //     (*index)++;
        //     return ;
        // }
        // printf("done");
        return ;
    }
}

// int             is_empty_line(char *file_string, int *index)
// {
//     while (file_string[*index] != '\0')
//     {
//         while (file_string[*index] == ' ' || file_string[*index] == '\t')
//             (*index)++;
//         if (file_string[*index] == '\n')
//         {
//             (*index)++;
//             return (1);
//         }
//         return (0);
//     }
//     return (0);
// }

int         find_color(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_tuple)
{
    return (0);
}

int        find_texture(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_tuple)
{
    char    *path;
    char    *temp;
    int     malloc_size;
    int     i;

    i = 0;
    malloc_size = 0;
    loop_empty_space(file_string, index);
    temp = &(file_string[*index]);
    if (temp[0] != '.' && temp[1] != '/')
        return (0);
    while (file_string[*index] != '\0' && file_string[*index] != '\n' && file_string[*index] != ' ' && file_string[*index] != '\t')
    {
        (*index)++;
        malloc_size++;
    }
    path = (char *)malloc(sizeof(char) * malloc_size + 1);
    if (!path)
        return (0);
    while (i < malloc_size)
    {
        path[i] = temp[i];
        i++;
    }
    path[i] = '\0';
    *(id_tuple->value) = path;
    loop_empty_space(file_string, index);
    return (1);
}

int        find_resolution(char *file_string, int *index, t_file_data *data, t_id_tuple *id_tuple)
{
    loop_empty_space(file_string, index);
    while (file_string[*index] >= '0' && file_string[*index] <= '9')
    {
        (data->res_width) = (data->res_width) * 10 + (file_string[*index] - 48);
        (*index)++;
    }
    loop_empty_space(file_string, index);
    while (file_string[*index] >= '0' && file_string[*index] <= '9')
    {
        (data->res_height) = (data->res_height) * 10 + (file_string[*index] - 48);
        (*index)++;
    }
    loop_empty_space(file_string, index);
    if (data->res_height != 0 && data->res_width != 0 && is_empty_line(&(file_string[*index])))
    {
        printf("\n\n resolution is found \n\n");
        (*index)++;
        return (1);
    }
    else
    {
        printf("\n\n res not found \n\n");
        return (0);
    }
}

t_id_tuple *initialize_tuple_list()
{
    t_id_tuple *id_list;

    id_list = (t_id_tuple *)malloc(sizeof(t_id_tuple) * 9);
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

void            link_struct_value(t_id_tuple *id_tuple, t_file_data *file_data)
{
    id_tuple->value = (char **)malloc(sizeof(char *) * 1);

    if (same_string(id_tuple->identifier, "NO ", 3))
        file_data->north_texture = id_tuple->value;
    else if (same_string(id_tuple->identifier, "SO ", 3))
        file_data->south_texture = id_tuple->value;
    else if (same_string(id_tuple->identifier, "WE ", 3))
        file_data->west_texture = id_tuple->value;
    else if (same_string(id_tuple->identifier, "EA ", 3))
        file_data->east_texture = id_tuple->value;
    else if (same_string(id_tuple->identifier, "S ", 2))
        file_data->sprite_texture = id_tuple->value;
    else if (same_string(id_tuple->identifier, "F ", 2))
        file_data->floor_color = id_tuple->value;
    else if (same_string(id_tuple->identifier, "C ", 2))
        file_data->ceiling_color = id_tuple->value;
}

/* Function that looks which identifier matches the start of the line and returns 0 on nothing found */
int             fits_identifier(char *file_string, int *index, t_file_data *file_data)
{
    int         i;
    int         id_strlen;
    t_id_tuple  *id_list;

    i = 0;
    id_list = initialize_tuple_list();
    while (id_list[i].identifier != 0)
    {
        id_strlen = get_strlen(id_list[i].identifier);
        if (same_string(&(file_string[*index]), id_list[i].identifier, id_strlen))
        {
            printf("found something");

            link_struct_value(&(id_list[i]), file_data);
            (*index) += id_strlen;
            if (!id_list[i].function(file_string, index, file_data, &(id_list)[i]))
                return (0);
            return (1);
        }   
        i++;
    }
    return (0);
}

void           print_file(t_file_data *data)
{
    printf("\n--------------------\n");
    printf("width : %d \n", data->res_width);
    printf("height : %d \n", data->res_height);
    printf("n_tex : %s \n", *(data->north_texture));
    printf("s_tex : %s \n", *(data->south_texture));
    printf("w_tex : %s \n", *(data->west_texture));
    printf("e_tex : %s \n", *(data->east_texture));
    printf("sprite : %s \n", *(data->sprite_texture));
    // printf("floor : %s \n", data->floor_color);
    // printf("ceiling : %s \n", data->ceiling_color);
    printf("\n--------------------\n");
}

int            all_info_filled(t_file_data *data)
{
    if (data->res_width != 0 &&
        data->res_height != 0 &&
        data->west_texture != 0 &&
        data->north_texture != 0 &&
        data->east_texture != 0 &&
        data->south_texture != 0 &&
        data->sprite_texture != 0)
        return (1);
    //     data->south_texture != 0 &&
    //     data->west_texture != 0 &&
    //     data->east_texture != 0 &&
    //     data->sprite_texture != 0 &&
    //     data->floor_color != 0 &&
    //     data->ceiling_color != 0)
    //     return (1);
    return (0);
}

/* Function that collects all the information */
int            get_general_info(t_file_data *file_data)
{
    int index;

    index = 0;
    while (all_info_filled(file_data) == 0)
    {
        if (is_empty_line(&((file_data->full_file)[index])))
        {
            loop_empty_space(&((file_data->full_file)[index]), &index);
            if ((file_data->full_file)[index] == '\n')
                index++;
        }
        else
        {
            if (!fits_identifier(file_data->full_file, &index, file_data)) /* Line didnt match any identifiers */
            {
                return (0);                
            }
            else /* Returned function with success */
            {
                
            }       
        }
    }
    print_file(file_data);
    return (1);
}