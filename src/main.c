/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Le désordre est mesuré avant la normalisation et toute opération. */

static void	free_stacks(t_push_swap *push_swap)
{
	stack_clear(&push_swap->a);
	stack_clear(&push_swap->b);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_push_swap	push_swap;
	double		disorder_ratio;

	if (argc == 1)
		return (0);
	push_swap = (t_push_swap){0};
	if (!parse_arguments(argc, argv, &push_swap, &config))
	{
		free_stacks(&push_swap);
		print_error();
		return (1);
	}
	if (push_swap.a.size == 0)
		return (0);
	disorder_ratio = compute_disorder(&push_swap.a);
	normalize_stack(&push_swap.a);
	execute_strategy(&push_swap, &config, disorder_ratio);
	free_stacks(&push_swap);
	return (0);
}
