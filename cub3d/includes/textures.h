/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:18:50 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

int				ft_load_all_textures(t_game *game);
t_texture		*ft_get_wall_texture(t_game *game);
unsigned int	ft_get_texture_pixel(t_texture *tex, int x, int y);

#endif
