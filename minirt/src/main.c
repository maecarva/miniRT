/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:57:10 by maecarva          #+#    #+#             */
/*   Updated: 2025/04/20 11:36:42 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_help(char *message)
{
	printf("Error\n");
	if (message)
		printf("%s\n", message);
	printf(GRN"Usage : ./minirt <scene.rt>\n"RESET);
}

void	print_err(t_config *c, char *msg)
{
	printf(HRED"Error.\n"RESET);
	if (msg)
		return ((void)printf("%s\n", msg));
	if (c->err.line > -1)
		printf("In scene file : %s\n", c->av[1]);
	if (c->err.msg)
	{
		if (ft_strcmp(INVALID_OBJECT, c->err.msg) == 0
			|| ft_strcmp(INVALID_NUMBER, c->err.msg) == 0)
			printf(c->err.msg, c->err.line);
		else
			printf(c->err.msg, c->av[1]);
	}
}

void	print_tuto(void)
{
	printf("Move camera : WASD\nTurn camera : arrowkeys\n");
}

int	main(int ac, char **av)
{
	t_config	*c;

	c = init_config(ac, av);
	if (!c)
		return (perror("Can't initialize config : "), EXIT_FAILURE);
	if (ac != 2)
		return (ft_help("Invalid number of arguments."),
			clean_exit(c), EXIT_FAILURE);
	c->mlx = mlx_init();
	if (c->mlx == NULL)
		return (false);
	if (parse_scene(c, av[1]) == false)
		return (print_err(c, NULL), clean_exit(c), EXIT_FAILURE);
	check_config(c);
	if (c->err.msg)
		return (print_err(c, NULL), clean_exit(c), EXIT_FAILURE);
	if (c)
		print_config(c);
	print_tuto();
	if (!render_multi(c))
		return (clean_exit(c));
	// render(c);
	install_hooks(c, true);
	mlx_loop(c->mlx);
	return (EXIT_SUCCESS);
}
