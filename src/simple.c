/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 16:50:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Les minima sont empilés dans b, puis pa reconstruit a dans l'ordre. */

void	sort_simple(t_push_swap *push_swap)
{
	int	minimum_position;

	while (push_swap->a.size > 0)
	{
		minimum_position = find_rank_pos(&push_swap->a, push_swap->b.size);
		bring_to_top(push_swap, &push_swap->a, minimum_position, OP_RA);
		exec_op(push_swap, OP_PB);
	}
	while (push_swap->b.size > 0)
		exec_op(push_swap, OP_PA);
}
