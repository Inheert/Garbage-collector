/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ptr_stockage_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:56:38 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/12 18:11:13 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

t_ptr_stockage	*gb_ptr_stockage_new(void *ptr)
{
	t_ptr_stockage	*new;

	new = malloc(sizeof(t_ptr_stockage));
	if (!new)
		return (free(ptr), gb_malloc_error(), NULL);
	new->ptr = ptr;
	new->size = sizeof(t_ptr_stockage);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	gb_ptr_stockage_add_back(t_ptr_stockage **storage, t_ptr_stockage *new)
{
	t_ptr_stockage	*tmp;

	if (!storage || !new)
		return ;
	if (!*storage)
	{
		*storage = new;
		return ;
	}
	tmp = *storage;
	while (tmp->next)
	{
		if (tmp->ptr == new->ptr)
			return (free(new));
		tmp = tmp->next;
	}
	tmp->next = new;
	new->prev = tmp;
}

void	gb_ptr_stockage_clear(t_ptr_stockage **storage)
{
	t_ptr_stockage	*tmp;

	if (!storage ||!*storage)
		return ;
	while (*storage)
	{
		tmp = *storage;
		*storage = (*storage)->next;
		free(tmp->ptr);
		free(tmp);
	}
}

unsigned int	gb_hashf(void *ptr, int size)
{
	unsigned long long	ptr_value;
	unsigned int		hash;
	size_t				i;
	size_t				s;

	ptr_value = (unsigned long long)ptr;
	i = 0;
	hash = 0;
	s = sizeof(ptr_value);
	while (i < s)
	{
		hash += ((ptr_value >> (i * 8)) & 0xFF);
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return (hash % size);
}
