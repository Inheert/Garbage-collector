/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:01:31 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/12 18:56:17 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	gb_malloc_error(void)
{
	printf("ERROR: a problem occured when using malloc.\n");
	gb_free_all();
	exit(EXIT_FAILURE);
}

static void	gb_add_to_garbage(t_ptr_stockage *container[CONTAINER_SIZE],
						void *ptr)
{
	t_ptr_stockage	*new;
	unsigned int	index;

	if (!ptr)
		return ;
	new = (t_ptr_stockage *)ptr;
	index = gb_hashf(new->ptr, CONTAINER_SIZE);
	if (container[index])
		gb_ptr_stockage_add_back(&container[index], new);
	else
		container[index] = new;
}

static void	gb_delete_from_garbage(t_ptr_stockage *container[CONTAINER_SIZE],
		void *ptr, int had_to_be_free)
{
	t_ptr_stockage	*tmp;
	unsigned int	index;

	if (!ptr)
		return ;
	index = gb_hashf(ptr, CONTAINER_SIZE);
	if (!container[index])
		return ;
	tmp = container[index];
	while (tmp && tmp->ptr != ptr)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp == container[index])
		container[index] = container[index]->next;
	if (had_to_be_free)
	{
		free(tmp->ptr);
		free(tmp);
	}
}

static void	gb_clear_garbage(t_ptr_stockage *container[CONTAINER_SIZE])
{
	unsigned int	i;

	if (!container)
		return ;
	i = -1;
	while (++i < CONTAINER_SIZE)
	{
		gb_ptr_stockage_clear(&container[i]);
		container[i] = NULL;
	}
}

void	*gb_garbage_collector(t_garbage_action action, void *ptr)
{
	static t_ptr_stockage	*container[CONTAINER_SIZE];

	if (action == ADD)
		gb_add_to_garbage(container, ptr);
	else if (action == DELETE)
		gb_delete_from_garbage(container, ptr, 1);
	else if (action == CLEAR)
		gb_clear_garbage(container);
	else if (action == UNSTORE)
		gb_delete_from_garbage(container, ptr, 0);
	else if (action == GET_GARBAGE)
		return (container);
	return (NULL);
}
