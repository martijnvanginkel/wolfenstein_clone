/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:09:15 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/26 10:30:31 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int				check_file_parsed(char *file)
{
	int i;

	i = get_strlen(file);
	if (file[i - 1] != 'b')
		return (0);
	else if (file[i - 2] != 'u')
		return (0);
	else if (file[i - 3] != 'c')
		return (0);
	else if (file[i - 4] != '.')
		return (0);
	else
		return (1);
}

int             main(int argc, char **argv)
{
	t_file_data *file_data;

    if (argc != 2)
    {
        show_error("Expecting only one argument\n");
        return (0);
    }
	else
	{
		if (!check_file_parsed(argv[1]))
		{
			show_error("Passed file is not the right type");
			return (0);
		}
	}

	printf("\n\n%s\n\n", argv[1]);
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
