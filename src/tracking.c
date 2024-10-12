/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Théo <theoclaereboudt@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:55:43 by Théo              #+#    #+#             */
/*   Updated: 2024/10/12 21:50:14 by Théo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

static void	convert_base_256_to_10(const t_big_number_256 *container_size,
									int start, char *result, int *pos)
{
	uint16_t	carry;
	uint16_t	temp;
	int			j;

	while (start < 256)
	{
		carry = container_size->bytes[start++];
		j = -1;
		while (++j < *pos)
		{
			temp = (result[j] - '0') * 256 + carry;
			result[j] = (temp % 10) + '0'; // Stocke le chiffre
			carry = temp / 10; // Calculer la retenue
		}
		while (carry > 0)
		{
			result[(*pos)++] = (carry % 10) + '0';
			carry /= 10;
		}
	}
}

void	gb_display_number(int pos, char *result, int j)
{
	int	blank_size;
	int	i;

	blank_size = CONTAINER_DISPLAY_NODE_SIZE - pos - 1;
	if (blank_size % 2 != 0)
		blank_size += 1;
	i = -1;
	while (++i < blank_size / 2)
		printf(" ");
	printf("%d nodes - ", j);
	i = pos - 1;
	while (i >= 0)
		printf("%c", result[i--]);
	printf(" bytes");
	i = -1;
	while (++i < blank_size / 2)
		printf(" ");
}

void	gb_print_big_number_decimal(const t_big_number_256 *container_size, int j)
{
	char		result[800];
	int			start;
	int			pos;
	int			i;

	start = 0;
	while (start < 256 && container_size->bytes[start] == 0)
		start++;
	if (start == 256)
	{
		gb_display_number(1, "0", 0);
		return ;
	}
	i = -1;
	while (++i < 800)
		result[i] = 0;
	pos = 0;
	convert_base_256_to_10(container_size, start, result, &pos);
	gb_display_number(pos, result, j);
}


void	gb_add_to_big_number(t_big_number_256 *container_size, size_t value)
{
	uint16_t	carry;
	uint16_t	sum;
	int			i;

	carry = 0;
	i = 255;
	while (value > 0 || carry > 0)
	{
		sum = container_size->bytes[i] + (value & 0xFF) + carry;
		container_size->bytes[i] = sum & 0xFF;
		carry = sum >> 8;
		value >>= 8;
		i--;
	}
}

void	gb_subtract_from_big_number(t_big_number_256 *container_size,
									size_t value)
{
	uint16_t	borrow;
	uint16_t	current_value;
	int			i;

	borrow = 0;
	i = 255;
	while (value > 0 || borrow > 0)
	{
		current_value = (value & 0xFF) + borrow;
		if (container_size->bytes[i] < current_value)
		{
			container_size->bytes[i] += 256;
			borrow = 1;
		}
		else
			borrow = 0;
		container_size->bytes[i] -= current_value;
		value >>= 8;
		i--;
	}
}

void	gb_calculate_and_display_node_size(t_ptr_stockage *container)
{
	t_big_number_256	container_size;
	int					j;

	j = -1;
	while (++j < 256)
		container_size.bytes[j] = 0;
	j = 0;
	while (container)
	{
		gb_add_to_big_number(&container_size, container->size);
		container = container->next;
		j++;
	}
	gb_print_big_number_decimal(&container_size, j);
}

void	gb_display(int container_per_line)
{
	t_ptr_stockage	**container;
	int				i;

	(void)container_per_line;
	container = gb_garbage_collector(GET_GARBAGE, NULL);
	i = 0;
	while (++i < CONTAINER_SIZE)
	{
		gb_calculate_and_display_node_size(container[i - 1]);
		if (i != 0 && i % container_per_line == 0)
			printf("\n");
	}
	printf("\n");
}
