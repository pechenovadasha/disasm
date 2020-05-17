#ifndef DIS_ASM_H
# define DIS_ASM_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "op.h"

typedef struct		s_type
{
	char			*name; //имя инструкции
	int				count_args; //количество аргументов
	char			bit_args[3]; //обьясню в зуме если ты не поняла, хз как написать)
	int 			number; //номер инструкции по порядку
}					t_type;


typedef struct		s_instr
{
	struct s_type 	*type;//указатель на тип инструкции
	char 			args[3];//сюда записать второй байт, указывающий, какие аргументы
	char			*string;//а сюда в итоге все собираешь
}					t_instr;


typedef struct	s_struct
{
	char		*name;
	char 		*file_name;
	char 		*comment;
	int 		fd_creat_file;
	t_instr		*code; //список инструкций
}				t_struct;

extern	t_type	type_tab[17];
void	ft_args_type(char *str, t_instr *data);
void	ft_arg_dir(int fd, t_instr *data, int counter);
void	ft_arg_reg(int fd, t_instr *data);
void	ft_arg_ind(int fd, t_instr *data);
void	ft_check_args(t_instr *data, int fd);
void	ft_init(t_instr *data);
void	free_string(t_instr *data);
void	ft_arg_one_dir(int fd, t_instr *data);
char	*ft_strjoin_sp(char **str, char *buf, size_t len);
void	ft_creat_file(t_struct *data);
void	filling_out_file(char *str);
char	*invert(char *str, int i);

# endif