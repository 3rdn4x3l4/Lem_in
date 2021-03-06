/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plagache <plagache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:47:08 by alagache          #+#    #+#             */
/*   Updated: 2020/05/09 12:51:08 by plagache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <limits.h>

static	int		read_ant_parse(t_lem_in *info)
{
	int	ret;

	ret = read_file(info);
	if (ret == FAILURE || ret == MALLOC_FAILURE)
	{
		ft_printf("ERROR\n");
		return (FAILURE);
	}
	if (split_file(info) == FAILURE)
	{
		ft_printf("ERROR\n");
		return (FAILURE);
	}
	if (get_ants(info) == FAILURE || info->nbr_ants == 0)
	{
		ft_printf("ERROR\n");
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	return (SUCCESS);
}

static	int		room_link_parse(t_lem_in *info)
{
	if (get_rooms(info) == FAILURE || info->head == NULL)
	{
		ft_printf("ERROR\n");
		free_graph(info->head, 2);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	if (get_commands(info) == FAILURE)
	{
		ft_printf("ERROR\n");
		free_graph(info->head, 2);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	if (get_links(info) == FAILURE)
	{
		ft_printf("ERROR\n");
		free_graph(info->head, 3);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	return (SUCCESS);
}

static	int		resolve(t_lem_in *info)
{
	int	flow;

	if (validate_data(info) == FAILURE)
		return (FAILURE);
	if (create_matrice(info) == NULL)
	{
		ft_printf("ERROR\n");
		free_graph(info->head, 3);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	info->best_paths.turns = INT_MAX;
	flow = edmond_karp(info);
	if (flow == 0 || flow == FAILURE)
	{
		ft_printf("ERROR\n");
		free_graph(info->head, 3);
		free_matrice(info->m_flow, info->rooms);
		free_file(info->file_split, info->file);
		return (FAILURE);
	}
	ft_printf("%s\n", info->file);
	free_file(info->file_split, info->file);
	return (SUCCESS);
}

/*
** ft_printf("%i\n", (info->best_paths).turns);
*/

static	int		print(t_lem_in *info)
{
	int	ret;

	ret = move_paths(info->best_paths.flow, info->best_paths.paths);
	free_paths(info->best_paths.paths, info->best_paths.flow);
	free_graph(info->head, 3);
	free_matrice(info->m_flow, info->rooms);
	if (ret == FAILURE)
	{
		ft_printf("ERROR\n");
		return (FAILURE);
	}
	if ((info->options & PRINT_LN) != 0)
	{
		ft_printf("Number of line : %i\n", info->best_paths.turns);
	}
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	t_lem_in	info;
	int			ret;

	ft_memset(&info, 0, sizeof(t_lem_in));
	if (option_check(ac, av, &info) == FAILURE)
		return (EXIT_FAILURE);
	ret = read_ant_parse(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	ret = room_link_parse(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	ret = resolve(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	ret = print(&info);
	if (ret == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
