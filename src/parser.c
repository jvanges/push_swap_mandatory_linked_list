/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Les drapeaux peuvent être mélangés aux valeurs, mais jamais répétés. */

/* Zéro désigne une valeur ; les autres codes identifient un drapeau. */
static int	get_flag_code(const char *str)
{
	if (ft_streq(str, "--simple"))
		return (SIMPLE + 1);
	if (ft_streq(str, "--medium"))
		return (MEDIUM + 1);
	if (ft_streq(str, "--complex"))
		return (COMPLEX + 1);
	if (ft_streq(str, "--adaptive"))
		return (ADAPTIVE + 1);
	if (ft_streq(str, "--bench"))
		return (FLAG_BENCH);
	return (0);
}

static int	apply_flag(t_config *config, int flag_code)
{
	if (flag_code == FLAG_BENCH)
	{
		if (config->bench)
			return (0);
		config->bench = 1;
		return (1);
	}
	if (config->strategy_seen)
		return (0);
	config->strategy = (t_strategy)(flag_code - 1);
	config->strategy_seen = 1;
	return (1);
}

int	parse_arguments(int argc, char **argv, t_push_swap *push_swap,
		t_config *config)
{
	int	i;
	int	flag_code;

	config->strategy = ADAPTIVE;
	config->bench = 0;
	config->strategy_seen = 0;
	i = 1;
	while (i < argc)
	{
		flag_code = get_flag_code(argv[i]);
		if (flag_code && !apply_flag(config, flag_code))
			return (0);
		if (!flag_code && !parse_string(argv[i], push_swap))
			return (0);
		i++;
	}
	return (1);
}
