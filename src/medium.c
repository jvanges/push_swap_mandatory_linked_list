/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 16:50:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Chaque bloc trié est placé sous les blocs déjà terminés dans a. */

static void	extract_chunk(t_push_swap *push_swap, int min_rank, int max_rank,
		int remaining_count)
{
	int	scanned_count;
	int	current_rank;

	scanned_count = 0;
	while (scanned_count < remaining_count)
	{
		current_rank = push_swap->a.top->value;
		if (current_rank >= min_rank && current_rank <= max_rank)
			exec_op(push_swap, OP_PB);
		else
			exec_op(push_swap, OP_RA);
		scanned_count++;
	}
}

/* Le rang maximal décroît de un après chaque extraction du bloc. */
static void	place_chunk(t_push_swap *push_swap, int current_chunk_size,
		int max_rank)
{
	int	moved_count;

	moved_count = 0;
	while (moved_count < current_chunk_size)
	{
		bring_to_top(push_swap, &push_swap->b,
			find_rank_pos(&push_swap->b, max_rank - moved_count), OP_RB);
		exec_op(push_swap, OP_PA);
		moved_count++;
	}
	moved_count = 0;
	while (moved_count < current_chunk_size)
	{
		exec_op(push_swap, OP_RA);
		moved_count++;
	}
}

void	sort_medium(t_push_swap *push_swap)
{
	int	size;
	int	chunk_size;
	int	completed_count;
	int	current_chunk_size;

	size = push_swap->a.size;
	chunk_size = chunk_size_for(size);
	completed_count = 0;
	while (completed_count < size)
	{
		current_chunk_size = chunk_size;
		if (current_chunk_size > size - completed_count)
			current_chunk_size = size - completed_count;
		extract_chunk(push_swap, completed_count,
			completed_count + current_chunk_size - 1,
			size - completed_count);
		bring_to_top(push_swap, &push_swap->a, completed_count, OP_RA);
		place_chunk(push_swap, current_chunk_size,
			completed_count + current_chunk_size - 1);
		completed_count += current_chunk_size;
	}
}
