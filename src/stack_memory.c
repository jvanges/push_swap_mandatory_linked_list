/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* L'insertion vérifie les doublons avant d'allouer un nouveau nœud. */

int	stack_append(t_stack *stack, int value)
{
	t_node	*current;
	t_node	*new_node;

	current = stack->top;
	while (current)
	{
		if (current->value == value)
			return (0);
		current = current->next;
	}
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (0);
	new_node->value = value;
	new_node->prev = stack->bottom;
	new_node->next = NULL;
	if (stack->bottom)
		stack->bottom->next = new_node;
	else
		stack->top = new_node;
	stack->bottom = new_node;
	stack->size++;
	return (1);
}

void	stack_clear(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	current = stack->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
}
