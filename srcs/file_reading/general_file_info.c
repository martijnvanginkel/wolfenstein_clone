/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_file_info.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 15:21:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/24 19:12:58 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int        find_texture(char *file_string, int *index, t_file_data *file_data)
{
    printf("\n\n find texture \n\n");
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

int        find_resolution(char *file_string, int *index, t_file_data *data)
{
    while (file_string[*index] != '\0')
    {
        while (file_string[*index] == ' ' || file_string[*index] == '\t')
        {
            (*index)++;
        }
        while (file_string[*index] >= '0' && file_string[*index] <= '9')
        {
            (data->res_width) = (data->res_width) * 10 + (file_string[*index] - 48);
            (*index)++;
        }
        while (file_string[*index] == ' ' || file_string[*index] == '\t')
        {
            (*index)++;
        }

    }

    printf("\n\n find resolution \n\n");
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

/* Function that looks which identifier matches the start of the line and returns 0 on nothing found */
int             fits_identifier(char *file_string, int *index, t_file_data *file_data)
{
    int     i;
    int     id_strlen;
    t_id_tuple *id_list;

    i = 0;
    id_list = initialize_tuple_list();
    while (id_list[i].identifier != 0)
    {
        id_strlen = get_strlen(id_list[i].identifier);
        if (same_string(file_string, id_list[i].identifier, id_strlen))
        {
            printf("\n\nid found: %s\n\n", id_list[i].identifier);
            
            (*index) += id_strlen;
            if (!id_list[i].function(file_string, index, file_data))
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
    int index;

    index = 0;
    // Check of het een van de identifying combinaties is
    // Als dat niet het geval is, kijk of het een lege line is

    // while ((file_data->full_file)[i] != '\0')
    // {
        if (fits_identifier(file_data->full_file, &index, file_data))
        {
            return (0);
        }
        else
        {
            // check_if_fully_empty_line();
        }
        
        
    //     return (0);
    // }

    return (1);
}