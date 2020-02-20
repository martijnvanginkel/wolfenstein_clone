/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rgb_to_hex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 15:36:40 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/19 16:11:36 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int     hex_char_to_dec(char c)
{
    if (c >= '0' && c <= '9')
    {
        return (c - 48);
    }
    else if (c == 'A')
        return (10);
    else if (c == 'B')
        return (11);
    else if (c == 'C')
        return (12);
    else if (c == 'D')
        return (13);
    else if (c == 'E')
        return (14);
    else if (c == 'F')
        return (15);
    return (0);
}

static char    *rgb_to_hex(int *rgb_code)
{
    char    *hex_code;
    char    *temp;
    char    *r;
    char    *g;
    char    *b;

    r = dec_to_hex((long)rgb_code[0], 1);
    g = dec_to_hex((long)rgb_code[1], 1);
    b = dec_to_hex((long)rgb_code[2], 1);
    temp = strjoin(r, g);
    hex_code = strjoin(temp, b);
    free(temp);
    free(r);
    free(g);
    free(b);
    return (hex_code);
}

int     dec_from_hex_color(int *rgb_code)
{
    char    *hex_code;
    int down = 5;
    int up = 0;
    int num = 0;

    hex_code = rgb_to_hex(rgb_code);
    while (hex_code[up] != '\0')
    {
        num = num + (hex_char_to_dec(hex_code[up]) * pow(16, down));   
        up++;
        down--;
    }
    return (num);
}