/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doxygen_groups.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:15:05 by  ruiferna         #+#    #+#             */
/*   Updated: 2026/06/04 15:15:05 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOXYGEN_GROUPS_H
# define DOXYGEN_GROUPS_H

/**
 * @defgroup parser Parser
 * @brief .cub file reading, element parsing, and map validation.
 */

/**
 * @defgroup raycasting Raycasting
 * @brief Per-column DDA walker and wall slice projection.
 */

/**
 * @defgroup player Player
 * @brief Player state, input mapping, and movement.
 */

/**
 * @defgroup graphics Graphics
 * @brief Image buffer management, draw helpers, doors, and minimap.
 */

/**
 * @defgroup textures Textures
 * @brief XPM loading, pixel sampling, and texture selection.
 */

/**
 * @defgroup error Error
 * @brief Centralized error reporting and game cleanup.
 */

/**
 * @defgroup exit Exit
 * @brief ESC, DESTROY_NOTIFY, and clean shutdown paths.
 */

/**
 * @defgroup init Initialization
 * @brief Game initialization and resource loading.
 */

/**
 * @defgroup sprites Sprites
 * @brief Sprite loading, animation, and rendering.
 */

#endif
