#include "dis_asm.h"

void	ft_init(t_instr *data)
{
	data->type = 0;
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