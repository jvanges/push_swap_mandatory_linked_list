/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 16:50:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Seules les rotations génèrent des opérations, pas les recherches C. */

static int	integer_sqrt(int value)
{
	int	root;

	root = 0;
	while (root + 1 <= value / (root + 1))
		root++;
	return (root);
}

int	chunk_size_for(int size)
{
	return (integer_sqrt(size) * 5 / 2);
}

int	rotation_cost(int position, int size)
{
	if (position <= size / 2)
		return (position);
	return (size - position);
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

/* Le coût et le sens de rotation partagent la même règle d'arrondi. */
void	bring_to_top(t_push_swap *push_swap, t_stack *stack,
		int target_position, t_operation forward)
{
	t_operation	reverse;
	int			rotations;

	reverse = OP_RRA;
	if (forward == OP_RB)
		reverse = OP_RRB;
	rotations = rotation_cost(target_position, stack->size);
	if (target_position > stack->size / 2)
		forward = reverse;
	while (rotations-- > 0)
		exec_op(push_swap, forward);
}
