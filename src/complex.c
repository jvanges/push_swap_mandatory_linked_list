/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 16:50:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Le radix LSD traite un bit à la fois en conservant l'ordre stable. */

/* Les bits zéro vont dans b ; les bits un restent dans a avec ra. */
static void	radix_pass(t_push_swap *push_swap, int current_bit)
{
	int	i;
	int	size;

	i = 0;
	size = push_swap->a.size;
	while (i < size)
	{
		if (((push_swap->a.top->value >> current_bit) & 1) == 0)
			exec_op(push_swap, OP_PB);
		else
			exec_op(push_swap, OP_RA);
		i++;
	}
	while (push_swap->b.size > 0)
		exec_op(push_swap, OP_PA);
}

void	sort_complex(t_push_swap *push_swap)
{
	int	current_bit;

	current_bit = 0;
	while (((push_swap->a.size - 1) >> current_bit) > 0)
	{
		radix_pass(push_swap, current_bit);
		current_bit++;
	}
}
