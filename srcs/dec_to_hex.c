/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dec_to_hex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 10:21:19 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/19 15:01:51 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char		give_back_hex_char(long number, int is_upper)
{
	if (!(number >= 10 && number <= 15))
	{
		return (number + '0');
	}
	else
	{
		if (number == 10)
			return (make_upper_on_yes('a', is_upper));
		else if (number == 11)
			return (make_upper_on_yes('b', is_upper));
		else if (number == 12)
			return (make_upper_on_yes('c', is_upper));
		else if (number == 13)
			return (make_upper_on_yes('d', is_upper));
		else if (number == 14)
			return (make_upper_on_yes('e', is_upper));
		else
			return (make_upper_on_yes('f', is_upper));
	}
}

char		*fill_str_with_remainders(long dec_num, int size, int **remainders,
			int is_upper)
{
	char	*result;
	int		index;
	int		malloc_size;

	index = 0;
	malloc_size = size;
	if (dec_num < 0)
		dec_num = dec_num * -1;
	result = malloc(sizeof(char) * malloc_size);
	if (!result)
		return (0);
	while (size > 0)
	{
		size--;
		result[index] = give_back_hex_char((*remainders)[size], is_upper);
		index++;
	}
	result[index] = '\0';
	return (result);
}

void		fill_hex_remainders(long dec_num, int **remainders)
{
	int index;

	index = 0;
	if (dec_num < 0)
		dec_num = (dec_num * -1);
	while (dec_num >= 16)
	{
		(*remainders)[index] = dec_num % 16;
		dec_num = (dec_num / 16);
		index++;
	}
	(*remainders)[index] = dec_num % 16;
	return ;
}

int			hex_array_size(long dec_num)
{
	int index;

	index = 0;
	if (dec_num < 0)
		dec_num = (dec_num * -1);
	while (dec_num >= 16)
	{
		dec_num = (dec_num / 16);
		index++;
	}
	index++;
	return (index);
}

char		*dec_to_hex(long dec_num, int is_upper)
{
	int		hex_size;
	char	*result;
	int		*remainders;
	char	*temp;

	hex_size = hex_array_size(dec_num);
	remainders = malloc(sizeof(int) * hex_size);
	if (!remainders)
		return (0);
	fill_hex_remainders(dec_num, &remainders);
	result = fill_str_with_remainders(dec_num, hex_size, &remainders, is_upper);
	if (get_strlen(result) == 1)
	{
		temp = result;
		result = strjoin(result, "0");
		free(temp);
	}
	free(remainders);
	return (result);
}