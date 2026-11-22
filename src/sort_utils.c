/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	integer_sqrt(int value)
{
	int	root;

	root = 0;
	while (root + 1 <= value / (root + 1))
		root++;
	return (root);
}

int	find_rank_pos(const t_stack *stack, int target_rank)
{
	t_node	*current;
	int		position;

	current = stack->top;
	position = 0;
	while (current)
	{
		if (current->value == target_rank)
			return (position);
		current = current->next;
		position++;
	}
	return (-1);
}

int	find_max_pos(const t_stack *stack)
{
	t_node	*current;
	int		position;
	int		max_position;
	int		max_value;

	current = stack->top;
	position = 0;
	max_position = 0;
	max_value = current->value;
	while (current)
	{
		if (current->value > max_value)
		{
			max_value = current->value;
			max_position = position;
		}
		current = current->next;
		position++;
	}
	return (max_position);
}

void	bring_to_top(t_push_swap *push_swap, t_stack *stack,
		int target_position, t_operation forward)
{
	t_operation	reverse;

	reverse = OP_RRA;
	if (forward == OP_RB)
		reverse = OP_RRB;
	if (target_position <= stack->size / 2)
	{
		while (target_position-- > 0)
			exec_op(push_swap, forward);
	}
	else
	{
		target_position = stack->size - target_position;
		while (target_position-- > 0)
			exec_op(push_swap, reverse);
	}
}
