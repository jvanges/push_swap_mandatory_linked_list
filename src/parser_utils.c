/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Un argument peut contenir plusieurs entiers séparés par des blancs. */

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_streq(const char *left, const char *right)
{
	int	i;

	i = 0;
	while (left[i] && left[i] == right[i])
		i++;
	return (left[i] == right[i]);
}

/* La validation avant addition évite tout dépassement de int. */
static int	convert_digits(const char *str, int *cursor, int sign, int *value)
{
	long	number;
	long	limit;

	number = 0;
	limit = INT_MAX;
	if (sign == -1)
		limit++;
	while (str[*cursor] >= '0' && str[*cursor] <= '9')
	{
		if (number > (limit - (str[*cursor] - '0')) / 10)
			return (0);
		number = number * 10 + (str[*cursor] - '0');
		(*cursor)++;
	}
	if (str[*cursor] && !ft_isspace(str[*cursor]))
		return (0);
	*value = (int)(number * sign);
	return (1);
}

static int	parse_number(const char *str, int *cursor, int *value)
{
	int	sign;

	sign = 1;
	if (str[*cursor] == '+' || str[*cursor] == '-')
	{
		if (str[*cursor] == '-')
			sign = -1;
		(*cursor)++;
	}
	if (str[*cursor] < '0' || str[*cursor] > '9')
		return (0);
	return (convert_digits(str, cursor, sign, value));
}

int	parse_string(const char *str, t_push_swap *push_swap)
{
	int	cursor;
	int	found;
	int	value;

	cursor = 0;
	found = 0;
	while (str[cursor])
	{
		while (str[cursor] && ft_isspace(str[cursor]))
			cursor++;
		if (!str[cursor])
			break ;
		if (!parse_number(str, &cursor, &value)
			|| !stack_append(&push_swap->a, value))
			return (0);
		found = 1;
	}
	return (found);
}
