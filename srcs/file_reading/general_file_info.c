/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_file_info.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 15:21:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/25 16:30:42 by mvan-gin      ########   odam.nl         */
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
        return ;
    }
}

/*
    There needs to be a void function that will loop the index pointer until its not meeting a space or tab
 */

/*
    The resolution needs to loop until it finds something different than a digit
    If this is not a space or tab, ut should return 0
    
    Every pointer function needs a checker to see if everything is filled in
    If its not filled in that function can already return 0 so there doesnt need to be a checker function
 */

int             is_empty_line(char *file_string, int *index)
{
    while (file_string[*index] != '\0')
    {
        while (file_string[*index] == ' ' || file_string[*index] == '\t')
            (*index)++;
        if (file_string[*index] == '\n')
        {
            (*index)++;
            return (1);
        }
        return (0);
    }
    return (0);
}

int         find_color()
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
    // id_tuple->value = (char **)malloc(sizeof(char*) * 2);
    // if (!id_tuple->value)
    //     return (0);
    // (id_tuple->value)[0] = (char *)malloc(sizeof(char) * malloc_size + 1);
    // if (!(id_tuple->value)[0])
    //     return (0);
    // // //*(id_tuple->value)[0] = 'h';
    // (id_tuple->value)[0][0] = 'h';
    // (id_tuple->value)[0][1] = 'o';
    // (id_tuple->value)[0][2] = 'i';
    // (id_tuple->value)[0][3] = '\0';

    path = malloc(sizeof(char) * 3);
    path[0] = 'h';
    path[1] = 'o';
    path[2] = '\0';

    (id_tuple->value)[0] = path;

    // file_data->north_texture = (id_tuple->value)[0];


    printf("path : %s\n", (id_tuple->value)[0]);
    printf("path2 : %s\n", *(file_data->north_texture));

    
    //printf("path : [%s]\n", path);
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
    if (data->res_height != 0 && data->res_width != 0 && is_empty_line(file_string, index))
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
    id_list[1].identifier = "NO";
    id_list[1].function = &find_texture;
    id_list[2].identifier = "SO";
    id_list[2].function = &find_texture;
    id_list[3].identifier = "WE";
    id_list[3].function = &find_texture;
    id_list[4].identifier = "EA";
    id_list[4].function = &find_texture;
    id_list[5].identifier = "S ";
    id_list[5].function = &find_texture;
    id_list[6].identifier = "F ";
    id_list[6].function = &find_texture;
    id_list[7].identifier = "C ";
    id_list[7].function = &find_texture;
    id_list[8].identifier = 0;
    return (id_list);
}

void            link_struct_value(t_id_tuple *id_tuple, t_file_data *file_data)
{
    id_tuple->value = (char **)malloc(sizeof(char *) * 1);
    //file_data->north_texture = (char **)malloc(sizeof(char *) * 1);
    // *(id_tuple)->value = malloc(sizeof(char) * 4);
    // (*(id_tuple)->value)[0] = 'h';
    // (*(id_tuple)->value)[0] = '0';
    // (*(id_tuple)->value)[0] = 'i';
    // (*(id_tuple)->value)[0] = '\0';

    file_data->north_texture = id_tuple->value;

    if (same_string(id_tuple->identifier, "NO ", 3))
    {
        //file_data->north_texture = id_tuple->value;
        //id_tuple->value = &(file_data->north_texture);
    }
    // else if (same_string(id_tuple->identifier, "SO ", 3))
    //     id_tuple->value = &(file_data->south_texture);
    // else if (same_string(id_tuple->identifier, "WE ", 3))
    //     id_tuple->value = &(file_data->west_texture);
    // else if (same_string(id_tuple->identifier, "EA ", 3))
    //     id_tuple->value = &(file_data->east_texture);
    // else if (same_string(id_tuple->identifier, "S ", 2))
    //     id_tuple->value = &(file_data->sprite_texture);
    // else if (same_string(id_tuple->identifier, "F ", 2))
    //     id_tuple->value = &(file_data->floor_color);
    // else if (same_string(id_tuple->identifier, "C ", 2))
    //     id_tuple->value = &(file_data->ceiling_color);
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
            //printf("\nid found: %s\n", id_list[i].identifier);
            link_struct_value(&(id_list[i]), file_data);
            (*index) += id_strlen;
            if (!id_list[i].function(file_string, index, file_data, &(id_list)[i]))
                return (0);
            return (1);
        }
        i++;
    }
    //printf("\n\nstill on this :: %c\n\n", file_string[*index]);
    return (-1);
}

void           print_file(t_file_data *data)
{
    printf("\n--------------------\n");
    printf("width : %d \n", data->res_width);
    printf("height : %d \n", data->res_height);
    //printf("n_tex : %s \n", data->north_texture);
    printf("s_tex : %s \n", data->south_texture);
    printf("w_tex : %s \n", data->west_texture);
    printf("e_tex : %s \n", data->east_texture);
    printf("sprite : %s \n", data->sprite_texture);
    printf("floor : %s \n", data->floor_color);
    printf("ceiling : %s \n", data->ceiling_color);
    printf("\n--------------------\n");
}

int            all_info_filled(t_file_data *data)
{
    if (data->res_width != 0 &&
        data->res_height != 0 &&
        data->north_texture != 0 &&
        data->south_texture != 0 &&
        data->west_texture != 0 &&
        data->east_texture != 0 &&
        data->sprite_texture != 0 &&
        data->floor_color != 0 &&
        data->ceiling_color != 0)
        return (1);
    return (0);
}

/* Function that collects all the information */
int            get_general_info(t_file_data *file_data)
{
    int index;
    int id_return;

    index = 0;

    while (all_info_filled(file_data) == 0)
    {
        id_return = fits_identifier(file_data->full_file, &index, file_data);
        if (id_return == -1) /* Couldnt find identifier_tag so check for empty line */
        {
            if (!is_empty_line(file_data->full_file, &index))
            {
                print_file(file_data);
                //printf("here0");
                return (0);
            }
        }
        else if (id_return == 0) /* Couldnt return the function with success so map is wrong */
        {
            //printf("here1");
            return (0);
        }
        else /* Returned function with success */
        {
            //printf("result : %c\n", (file_data->full_file)[index]);
        }
    }



    return (1);
}