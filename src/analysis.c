/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(const t_stack *stack)
{
	t_node	*left;
	t_node	*right;
	long	inversions;
	long	total_pairs;

	inversions = 0;
	total_pairs = (long)stack->size * (stack->size - 1) / 2;
	left = stack->top;
	while (left)
	{
		right = left->next;
		while (right)
		{
			if (left->value > right->value)
				inversions++;
			right = right->next;
		}
		left = left->next;
	}
	if (total_pairs == 0)
		return (0.0);
	return ((double)inversions / (double)total_pairs);
}

static int	compute_rank(const t_stack *stack, int value)
{
	t_node	*current;
	int		rank;

	rank = 0;
	current = stack->top;
	while (current)
	{
		if (current->value < value)
			rank++;
		current = current->next;
	}
	return (rank);
}

void	normalize_stack(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		current->rank = compute_rank(stack, current->value);
		current = current->next;
	}
	current = stack->top;
	while (current)
	{
		current->value = current->rank;
		current = current->next;
	}
}

int	is_sorted(const t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current && current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
