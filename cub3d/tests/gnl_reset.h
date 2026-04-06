#ifndef GNL_RESET_H
# define GNL_RESET_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Flushes the GNL buffer for a given file descriptor
 * 
 * This function consumes all remaining data from GNL's buffer
 * to prevent data leakage between tests that reuse file descriptors.
 * 
 * @param fd File descriptor to flush
 */
static void	flush_gnl_buffer(int fd)
{
	char	*line;
	int	save_errno;

	save_errno = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
	}
	// If we got an error (NULL from GNL but not EOF), save errno
	// This is a bit hacky but works for our purposes
	(void)save_errno;
}

#endif
