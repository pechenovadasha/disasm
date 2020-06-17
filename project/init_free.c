/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croxane <croxane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 16:22:04 by croxane           #+#    #+#             */
/*   Updated: 2020/05/19 12:11:41 by croxane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dis_asm.h"

void	ft_init(t_instr *data)
{
	data->type = 0;
	data->args[0] = 0;
	data->args[1] = 0;
	data->args[2] = 0;
	data->string = 0;
}

void	free_string(t_instr *data)
{
	int i;

	i = 0;
	data->type = 0;
	while (i < 3)
	{
		data->args[i] = 0;
		i++;
	}
	free(data->string);
	data->string = 0;
}
