/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 16:20:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 16:20:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	rotation_cost(int position, int size)
{
	if (position <= size / 2)
		return (position);
	return (size - position);
}

static void	push_chunks(t_push_swap *push_swap, int chunk_size)
{
	int	pushed;
	int	limit;
	int	rank;

	pushed = 0;
	while (push_swap->a.size > 0)
	{
		limit = (pushed / chunk_size + 1) * chunk_size - 1;
		rank = push_swap->a.top->value;
		if (rank <= limit)
		{
			exec_op(push_swap, OP_PB);
			if (push_swap->b.size > 1 && rank <= limit - chunk_size / 2)
				exec_op(push_swap, OP_RB);
			pushed++;
		}
		else
			exec_op(push_swap, OP_RA);
	}
}

static void	extract_ranks(t_push_swap *push_swap, int target)
{
	int	max_position;
	int	prev_position;
	int	use_previous;

	while (push_swap->b.size > 0)
	{
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
		target -= 1 + use_previous;
	}
}

void	sort_small(t_push_swap *push_swap)
{
	int	chunk_size;

	chunk_size = integer_sqrt(push_swap->a.size) * 5 / 2;
	if (chunk_size < 1)
		chunk_size = 1;
	push_chunks(push_swap, chunk_size);
	extract_ranks(push_swap, push_swap->b.size - 1);
}
