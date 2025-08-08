/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:17:48 by maecarva          #+#    #+#             */
/*   Updated: 2025/04/18 13:50:37 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minirt.h"

static bool	get_texture_sphere(t_config *c, t_sphere *s,
				char **infos, char **tmp)
{
	*tmp = ft_strchr(infos[8], ':');
	if (!*tmp)
		return (false);
	*tmp = ft_strdup(*tmp + 1);
	if (!*tmp || ft_strlen(*tmp) == 0)
		return (free(*tmp), false);
	s->textured = true;
	s->texture_name = *tmp;
	s->texture.img = mlx_xpm_file_to_image(c->mlx,
			*tmp, &s->texture.imgw, &s->texture.imgh);
	if (!s->texture.img)
		return (free(*tmp), false);
	s->texture.addr = mlx_get_data_addr(s->texture.img,
			&s->texture.bits_per_pixels,
			&s->texture.line_len, &s->texture.endian);
	if (!s->texture.addr)
		return (free(*tmp), false);
	if (infos[9] == NULL)
		return (true);
	return (true);
}

static bool	get_bump_sphere(t_config *c, t_sphere *s, char **infos, char **tmp)
{
	char	*tmp2;

	tmp2 = ft_strchr(infos[9], ':');
	if (!tmp2)
		return (false);
	tmp2 = ft_strdup(tmp2 + 1);
	if (!tmp2 || ft_strlen(tmp2) == 0)
		return (free(tmp2), free(*tmp), false);
	s->bumped = true;
	s->bump_name = tmp2;
	s->bump.img = mlx_xpm_file_to_image(
			c->mlx, tmp2, &s->bump.imgw, &s->bump.imgh);
	if (!s->bump.img)
		return (free(tmp2), free(*tmp), false);
	s->bump.addr = mlx_get_data_addr(s->bump.img,
			&s->bump.bits_per_pixels,
			&s->bump.line_len, &s->bump.endian);
	if (!s->bump.addr)
		return (free(tmp2), free(*tmp), false);
	return (true);
}

static bool	handle_more_args_sphere(t_config *c, char **infos, t_sphere *s)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (infos[8] && ft_strcmp("checked", infos[8]) == 0)
		s->checked = true;
	else if (ft_strnstr(infos[8], "text", ft_strlen(infos[8])) == infos[8])
	{
		if (get_texture_sphere(c, s, infos, &tmp) == false)
			return (false);
		if (infos[9] == NULL)
			return (true);
		if (ft_strnstr(infos[9], "bump", ft_strlen(infos[9])) == infos[9])
		{
			if (get_bump_sphere(c, s, infos, &tmp) == false)
				return (mlx_destroy_image(c->mlx, s->texture.img), false);
		}
		else
			return (free(tmp2),
				free(tmp), mlx_destroy_image(c->mlx, s->texture.img), false);
	}
	else
		return (false);
	return (true);
}

static bool	fill_sphere(t_config *c, char **infos, t_object_node *node)
{
	((t_sphere *)node->obj)->id = ++(c->total_objects);
	((t_sphere *)node->obj)->center = point_create(
			ft_atod(infos[1]), ft_atod(infos[2]), ft_atod(infos[3]));
	((t_sphere *)node->obj)->radius = ft_atod(infos[4]);
	((t_sphere *)node->obj)->color = point_create(
			ft_atoi(infos[5]) / 255.0,
			ft_atoi(infos[6]) / 255.0, ft_atoi(infos[7]) / 255.0);
	((t_sphere *)node->obj)->material = default_material(
			((t_sphere *)node->obj)->color);
	if (infos[8])
	{
		if (!handle_more_args_sphere(c, infos, (t_sphere *)node->obj))
			return (false);
	}
	return (true);
}

bool	parse_sphere(t_config *c, char **infos, int currline)
{
	t_object_node	*node;
	t_list			*lsttmp;

	if (ft_tabsize(infos) <= 7 || ft_tabsize(infos) > 10)
		return (false);
	if (!check_only_valid_float(&infos[1], 7))
	{
		c->err.msg = INVALID_NUMBER;
		c->err.line = currline;
		return (false);
	}
	node = ft_calloc(sizeof(t_object_node), 1);
	if (!node)
		return (false);
	node->type = SPHERE;
	node->obj = ft_calloc(sizeof(t_sphere), 1);
	if (!node->obj)
		return (free(node), false);
	if (!fill_sphere(c, infos, node))
		return (free(node->obj), free(node), false);
	lsttmp = ft_lstnew(node);
	if (!lsttmp)
		return (free(node->obj), free(node), false);
	ft_lstadd_back(&c->objects_list, lsttmp);
	return (true);
}
