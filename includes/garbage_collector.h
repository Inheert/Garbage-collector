/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:05:01 by tclaereb          #+#    #+#             */
/*   Updated: 2024/10/12 22:22:07 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <time.h>

# define CONTAINER_SIZE 1024
# define CONTAINER_DISPLAY_NODE_SIZE 15

typedef enum s_garbage_action
{
	ADD,
	CLEAR,
	DELETE,
	UNSTORE,
	GET_GARBAGE,
}	t_garbage_action;

typedef struct s_ptr_stockage
{
	void					*ptr;
	size_t					size;
	struct s_ptr_stockage	*next;
	struct s_ptr_stockage	*prev;
}	t_ptr_stockage;

typedef struct s_big_number_256
{
	uint8_t	bytes[256];
}	t_big_number_256;

// Core function used to add / delete a ptr to the garbage or clear the garbage
void			*gb_garbage_collector(t_garbage_action action, void *ptr);

// Garbage strucure manipulation
t_ptr_stockage	*gb_ptr_stockage_new(void *ptr);
void			gb_ptr_stockage_add_back(t_ptr_stockage **storage,
					t_ptr_stockage *new);
void			gb_ptr_stockage_clear(t_ptr_stockage **storage);
unsigned int	gb_hashf(void *ptr, int size);

// Allocation and free functions

// Allocate SIZE bytes of memory, the new pointer is also added to the
// garbage collector.
void			*gb_malloc(size_t size);
// Re-allocate the previous allocated block int old_ptr, making the new block
// NEW_SIZE bytes long. OLD_SIZE is used to set to copy the old memory and set
// the rest at 0.
void			*gb_realloc(void *old_ptr, size_t old_size, size_t new_size);
// add PTR to the garbage collector. ONLY add PTR that have been allocate using malloc
// or PTR that have been unstore from the garbage or a double free will raise if you use
// gb_free_all()
void			gb_store_malloc(void *ptr);
// unstore PTR from the garbage, if it not in then nohing happend.
void			gb_unstore_malloc(void *ptr);
// unstore PTR from the garbage and free the block.
void			gb_free(void *ptr);
// unstore all PTR from the garbage and free each block.
void			gb_free_all(void);

// Function to raise when malloc error happen
void			gb_malloc_error(void);

void			gb_display(int container_per_line);

#endif
