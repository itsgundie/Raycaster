/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edestiny <edestiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:54:14 by amargy            #+#    #+#             */
/*   Updated: 2019/12/30 10:03:44 by edestiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <stdint.h>

# define BUFF_SIZE_PRINTF 1000
# define DEF_PRE 6
# define DUB_LEN 1076
# define LON_LEN 16447

typedef struct		s_printf
{
	char			buff[BUFF_SIZE_PRINTF];
	int				i_buff;
	int				s;
	int				i;
	va_list			ap;
	long long		arg;
	char			*format;
	int				base;
	int				lcase;
	char			box[2];
	char			mod[2];
	int				i_res;
	int				unsign;
	int				zero;
	int				minus;
	int				width;
	int				spec_found;
	int				sharp;
	int				prec;
	int				prec_f;
	int				space_f;
	int				string_f;
	int				s_q;
	int				char_f;
	int				i_prec;
	int				plus_f;
	int				exept_zero;
	int				ptr_f;
	int				static_ft_printf;
	int				length_capital_l;
	int				float_f;
	int				nan_f;
	int				inf_f;
}					t_printf;

typedef union		u_val
{
	double			n;
	struct
	{
		uint32_t	lo;
		uint32_t	hi;
	}				u32;
}					t_val;

typedef struct		s_bg
{
	uint32_t		n[128];
	int32_t			lo;
	int32_t			hi;
	int				sign:1;
}					t_bg;

typedef union		u_val64
{
	long double		n;
	struct
	{
		uint64_t	lo;
		uint64_t	hi;
	}				u64;
}					t_val64;

typedef struct		s_bgl
{
	uint32_t		n[2048];
	int32_t			lo;
	int32_t			hi;
	unsigned int	sign : 1;
}					t_bgl;

extern unsigned int	g_ten_pow[];

typedef void		(*t_function_point_array)(t_printf*);

int					ft_printf(const char *format, ...);
int					pars(t_printf *p, t_function_point_array fpa[256]);
void				spec_flags(t_function_point_array fpa[256]);
void				spec_flags_two(t_function_point_array fpa[256]);
void				unknownspec(t_printf *p);
void				print_to_percent(t_printf *p);
void				second_percent(t_printf *p);
void				itoa_int(int arg);
void				dioux(t_printf *p);
void				xf(t_printf *p);
void				upx_f(t_printf *p);
void				itoa_base(t_printf *p, char *res);
void				itoa_decimal(t_printf *p, char *res);
void				print_arg(char *res, t_printf *p);
void				width_f(t_printf *p);
void				long_f(t_printf *p);
int					atoi_width_prec(t_printf *p);
void				zero_space_print(int quantity, char s, t_printf *p);
void				exception(t_printf *p, char *res);
void				percent_found(t_printf *p, t_function_point_array fpa[256]);
void				cast_arg(t_printf *p);
void				char_f(t_printf *p);
void				point_f(t_printf *p);
char				*precision_d(char *res, t_printf *p);
void				put_zero(t_printf *p);
void				preprint(char *res, t_printf *p);
char				*ft_strcpy(char *dst, const char *src);
void				sharp_res(char *res, t_printf *p);
void				space_f(t_printf *p);
void				space_flag_print(char *res, t_printf *p);
void				str_f(t_printf *p);
void				plus_minus_print(char *res, t_printf *p);
int					numbers_preprint(char *res, t_printf *p);
void				cast_signed(t_printf *p);
void				cast_unsigned(t_printf *p);
void				ptr_f(t_printf *p);
void				ptr_preprint(char *res, t_printf *p);
void				print_buff(t_printf *p);
void				buffcpy(char *res, t_printf *p, int size);
void				format_float(t_printf *p);
void				print_float(char *s, t_printf *p);
void				print_float2(char *s, t_printf *p);
void				check_point(char **s, t_printf *p);
void				print_str_float(char *s, t_printf *p);
void				div_dub_hi(t_bg *nd, uint32_t *carry, uint32_t *i);
void				div_long_hi(t_bgl *nd, uint32_t *carry, uint32_t *i);
void				div_dub_last(t_bg *nd, uint32_t *carry,\
							uint32_t *i, uint32_t pos);
void				div_long_last(t_bgl *nd, uint32_t *carry,\
							uint32_t *i, uint32_t pos);
void				div_nd_long(t_bgl *nd, uint32_t pos);
char				*dub_2_str(t_bg *nd, int pre, char *str, int zero);
char				*bad_num_dubl(t_val *tmp, char *dubstr, int sign);
void				get_dub_fracture(t_val *tmp, t_bg *nd, int32_t *expa);
void				implicit_bit(int32_t *expa, t_bg *nd);
char				*double_trouble(double *n, int pre, char *dubstr);
int					expa_choice(unsigned int val);
void				mult_nd_long(t_bgl *nd, uint32_t pos, uint32_t carry);
void				mult_long_last(t_bgl *nd, uint32_t *carry,\
							uint32_t *i, uint32_t pos);
char				*bad_num_long(t_val64 *tmp, char *dubstr, int sign);
void				get_long_fracture(t_val64 *tmp, t_bgl *nd, int32_t *expa);
char				*long_double_trouble(long double *n, int pre, char *dubstr);
void				round_up(uint32_t *nd, int nd_lo, int mask);
void				round_lo(int pre, int prepos, int *ndlo);
int					round_tail(int nd_lo, int pre, uint32_t *nd, int mask);
void				do_long_round(t_bgl *nd, int *pre);
void				do_round_dub(t_bg *nd, int *pre);
void				div_nd_dub(t_bg *nd, uint32_t pos);
void				dubtoi(int up, char **pos, uint32_t u, int pre);
void				write_bef_dot_dub(t_bg *nd, char **pos);
void				write_bef_long_dot(t_bgl *nd, char **pos);
void				write_af_lo_dot(t_bgl *nd, char **pos, int pre, int zero);
char				*long_2_str(t_bgl *nd, int pre, char *str, int zero);
void				write_af_dub_dot(t_bg *nd, char **pos, int pre, int zero);
void				mult_long_main(t_bgl *nd, uint32_t *carry, uint32_t *i);
int					ft_isdigit(int c);
void				mult_nd_dub(t_bg *nd, uint32_t pos, uint32_t carry);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *s);
void				put_zero2(t_printf *p);
void				sharp_f(t_printf *p);
void				intf(t_printf *p);
void				itoa_lu(t_printf *p, unsigned long lu, char *res);
void				o_f(t_printf *p);
void				check_unsigned(t_printf *p);
void				short_f(t_printf *p);
void				capital_long_f(t_printf *p);
void				width_align_print(char *res, t_printf *p);
void				precision_zero(char *res, t_printf *p);

#endif
