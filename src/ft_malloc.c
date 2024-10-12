/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:56:17 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/12 21:06:35 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	*gb_malloc(size_t size)
{
	void			*ptr;
	t_ptr_stockage	*new;

	if (size <= 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (gb_malloc_error(), NULL);
	new = gb_ptr_stockage_new(ptr);
	new->size += size;
	gb_garbage_collector(ADD, new);
	return (ptr);
}

static void	*gb_copy_memory(void *dest, const void *src, size_t n)
{
	unsigned char		*_dest;
	unsigned char		*_src;

	_dest = (unsigned char *)dest;
	_src = (unsigned char *)src;
	if (_dest == NULL && _src == NULL)
		return (dest);
	while (n--)
	{
		*_dest = *_src;
		_dest++;
		_src++;
	}
	return (dest);
}

static void	gb_bytes_zero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

static void	gb_realloc_save(void *new_ptr, void *old_ptr, size_t size)
{
	t_ptr_stockage	*new;

	gb_free(old_ptr);
	new = gb_ptr_stockage_new(new_ptr);
	new->size += size;
	gb_store_malloc(new_ptr);
}

void	*gb_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size <= 0)
		return (gb_free(old_ptr), NULL);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (gb_malloc_error(), NULL);
	if (old_ptr)
	{
		if (old_size < new_size)
		{
			gb_copy_memory(new_ptr, old_ptr, old_size);
			gb_bytes_zero(new_ptr + old_size, new_size - old_size);
		}
		else
		{
			gb_copy_memory(new_ptr, old_ptr, new_size);
			gb_bytes_zero(new_ptr + old_size, old_size - new_size);
		}
	}
	gb_realloc_save(new_ptr, old_ptr, new_size);
	return (new_ptr);
}
