/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:12:41 by Théo              #+#    #+#             */
/*   Updated: 2024/10/12 18:10:19 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	gb_store_malloc(void *ptr)
{
	if (!ptr)
		return ;
	gb_garbage_collector(ADD, ptr);
}

void	gb_unstore_malloc(void *ptr)
{
	if (!ptr)
		return ;
	gb_garbage_collector(UNSTORE, ptr);
}

void	gb_free(void *ptr)
{
	gb_garbage_collector(DELETE, ptr);
}

void	gb_free_all(void)
{
	gb_garbage_collector(CLEAR, NULL);
}
