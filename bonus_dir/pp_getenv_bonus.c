/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_getenv_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odessein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:44:47 by odessein          #+#    #+#             */
/*   Updated: 2022/07/28 14:17:19 by odessein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*pp_get_path(char **envp)
{
	int		i;
	char	*res;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			res = ft_strdup(envp[i] + 5);
			return (res);
		}
		i++;
	}
	res = (char *) malloc(sizeof(*res));
	res[0] = 0;
	return (res);
}
