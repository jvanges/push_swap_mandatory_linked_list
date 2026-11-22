/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Le sommet est top : les primitives ne font aucune allocation. */

void	stack_swap(t_stack *stack)
{
	int	tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = tmp;
}

/* Le nœud du sommet change de pile sans être copié ni réalloué. */
void	stack_push(t_stack *destination, t_stack *source)
{
	t_node	*node;

	if (source->size == 0)
		return ;
	node = source->top;
	source->top = node->next;
	if (source->top)
		source->top->prev = NULL;
	else
		source->bottom = NULL;
	source->size--;
	node->prev = NULL;
	node->next = destination->top;
	if (destination->top)
		destination->top->prev = node;
	else
		destination->bottom = node;
	destination->top = node;
	destination->size++;
}

void	stack_rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (stack->size < 2)
		return ;
	first = stack->top;
	last = stack->bottom;
	stack->top = first->next;
	stack->top->prev = NULL;
	stack->bottom = first;
	first->prev = last;
	first->next = NULL;
	last->next = first;
}

void	stack_reverse(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (stack->size < 2)
		return ;
	first = stack->top;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	stack->top = last;
	last->prev = NULL;
	last->next = first;
	first->prev = last;
}
