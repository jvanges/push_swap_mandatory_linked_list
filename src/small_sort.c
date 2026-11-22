/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 16:20:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 16:50:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Chemin borné : remplir b par blocs, puis extraire les plus grands rangs. */

/* rb déplace la moitié inférieure du bloc courant vers le fond de b. */
static void	push_chunks(t_push_swap *push_swap, int chunk_size)
{
	int	limit;
	int	rank;

	while (push_swap->a.size > 0)
	{
		limit = (push_swap->b.size / chunk_size + 1) * chunk_size - 1;
		rank = push_swap->a.top->value;
		if (rank <= limit)
		{
			exec_op(push_swap, OP_PB);
			if (push_swap->b.size > 1 && rank <= limit - chunk_size / 2)
				exec_op(push_swap, OP_RB);
		}
		else
			exec_op(push_swap, OP_RA);
	}
}

/* Après une extraction en paire, sa rétablit l'ordre des deux rangs. */
static void	extract_ranks(t_push_swap *push_swap)
{
	int	target;
	int	max_position;
	int	prev_position;
	int	use_previous;

	while (push_swap->b.size > 0)
	{
		target = push_swap->b.size - 1;
		max_position = find_rank_pos(&push_swap->b, target);
		prev_position = find_rank_pos(&push_swap->b, target - 1);
		use_previous = (prev_position >= 0
				&& rotation_cost(prev_position, push_swap->b.size)
				< rotation_cost(max_position, push_swap->b.size));
		if (use_previous)
		{
			bring_to_top(push_swap, &push_swap->b, prev_position, OP_RB);
			exec_op(push_swap, OP_PA);
			max_position = find_rank_pos(&push_swap->b, target);
		}
		bring_to_top(push_swap, &push_swap->b, max_position, OP_RB);
		exec_op(push_swap, OP_PA);
		if (use_previous)
			exec_op(push_swap, OP_SA);
	}
}

void	sort_small(t_push_swap *push_swap)
{
	int	chunk_size;

	chunk_size = chunk_size_for(push_swap->a.size);
	push_chunks(push_swap, chunk_size);
	extract_ranks(push_swap);
}
