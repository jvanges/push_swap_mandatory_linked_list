/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-ges <jvan-ges@student.42belgium.be>   +#+  +:+       +#+        */
/*   By: anaubare <anaubare@student.42belgium.be>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:45:00 by jvan-ges          #+#    #+#             */
/*   Updated: 2026/11/22 15:45:00 by jvan-ges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Le désordre choisit la stratégie selon les seuils 0.2 et 0.5. */
static t_strategy	adaptive_strategy(double disorder_ratio)
{
	if (disorder_ratio < 0.2)
		return (SIMPLE);
	if (disorder_ratio < 0.5)
		return (MEDIUM);
	return (COMPLEX);
}

/* Jusqu'à 512 éléments, Medium et Complex partagent le chemin borné. */
void	execute_strategy(t_push_swap *push_swap, const t_config *config,
		double disorder_ratio)
{
	t_strategy	selected_strategy;

	selected_strategy = config->strategy;
	if (selected_strategy == ADAPTIVE)
		selected_strategy = adaptive_strategy(disorder_ratio);
	if (!is_sorted(&push_swap->a))
	{
		if (selected_strategy != SIMPLE && push_swap->a.size <= 512)
			sort_small(push_swap);
		else if (selected_strategy == SIMPLE)
			sort_simple(push_swap);
		else if (selected_strategy == MEDIUM)
			sort_medium(push_swap);
		else
			sort_complex(push_swap);
	}
	if (config->bench)
		print_bench(push_swap, disorder_ratio, selected_strategy,
			config->strategy == ADAPTIVE);
}
