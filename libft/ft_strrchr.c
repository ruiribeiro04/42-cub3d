/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:15:11 by ruiferna          #+#    #+#             */
/*   Updated: 2025/04/14 21:28:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	i = 0;
	last = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (last);
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{
   const char str[] = "Tutorialspoint";
   // "ch" is search string
   const char ch = 't';
   char *ret;
   ret = ft_strrchr(str, ch);
   printf("String after |%c| is - |%s|\n", ch, ret);
   return(0);
}
*/
