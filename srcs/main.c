/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:09:15 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/06 11:55:34 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int             main(int argc, char **argv)
{
	t_file_data *file_data;

    // if (argc != 2)
    // {
    //     show_error("Expecting only one argument");
    //     return (0);
    // }
	file_data = collect_file_information(argv[1]);
	if (!file_data)
	{
        show_error("Something went wrong collecting the data from the file");
		return (0);
	}

	print_string("All info successfully collected");

	run_game(file_data);


    return (0);
}

/*
	Print een 2D map
	Print de speler op het juiste vlakje
	Zorg dat de speler zich kan bewegen
	Zorg dat je kunt bijhouden in welk vlakje van de 2D array de speler zich bevindt
	Zorg dat de speler kan draaien om as
 */
