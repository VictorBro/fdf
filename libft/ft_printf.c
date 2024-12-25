/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronov <vbronov@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 22:03:37 by vbronov           #+#    #+#             */
/*   Updated: 2024/12/07 14:27:30 by vbronov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_atoi_helper(const char *str, int *o_cur)
{
	int	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + *str - '0';
		str++;
		(*o_cur)++;
	}
	return (num);
}

int	process_normal(const char *str, va_list *params, t_opt *opt)
{
	int	total;

	total = 0;
	if (str[1] == 'c')
		total += ft_printchar(va_arg(*params, int), opt);
	else if (str[1] == 's')
		total += ft_printstr(va_arg(*params, char *), opt);
	else if (str[1] == 'p')
		total += ft_printptr(va_arg(*params, void *), opt);
	else if (str[1] == 'd' || str[1] == 'i')
		total += ft_printnum(va_arg(*params, int), opt);
	else if (str[1] == 'u')
		total += ft_printunum(va_arg(*params, unsigned int), opt);
	else if (str[1] == 'x')
		total += ft_printhex(va_arg(*params, unsigned int), opt, 0);
	else if (str[1] == 'X')
		total += ft_printhex(va_arg(*params, unsigned int), opt, 1);
	else if (str[1] == '%')
		total += print_char('%', opt);
	return (total);
}

void	process_flags(t_opt *opt, const char *str, int *cur)
{
	if (str[1] == '#')
		opt->sharp = 1;
	else if (str[1] == ' ')
		opt->space = 1;
	else if (str[1] == '+')
		opt->plus = 1;
	else if (str[1] == '0')
	{
		opt->zero_width = ft_atoi_helper(str + 2, cur);
		opt->zero = 1;
	}
	else if (str[1] == '-')
	{
		opt->padding = ft_atoi_helper(str + 2, cur);
		opt->minus = 1;
	}
	else if (str[1] == '.')
	{
		opt->dot_width = ft_atoi_helper(str + 2, cur);
		opt->dot = 1;
	}
}

int	process(const char *str, va_list *params, int *cur, t_opt *opt)
{
	int	total;

	if (!str[(*cur) + 1])
	{
		opt->error = 1;
		return (0);
	}
	total = 0;
	while (ft_strchr("0123456789# +-.", str[(*cur) + 1]) != NULL)
	{
		if (ft_strchr("# +0-.", str[(*cur) + 1]) != NULL)
			process_flags(opt, str + (*cur), cur);
		else
		{
			opt->min_width = ft_atoi_helper(str + (*cur) + 1, cur);
			(*cur)--;
		}
		(*cur)++;
	}
	total += process_normal(str + (*cur), params, opt);
	(*cur)++;
	return (total);
}

int	ft_printf(const char *str, ...)
{
	va_list	params;
	int		cur;
	int		total;
	t_opt	opt;

	if (is_valid(str) == 0)
		return (-1);
	cur = 0;
	total = 0;
	va_start(params, str);
	while (str[cur])
	{
		init_opt(&opt);
		if (str[cur] == '%')
			total += process(str, &params, &cur, &opt);
		else
			total += print_char(str[cur], &opt);
		cur++;
		if (opt.error)
			break ;
	}
	va_end(params);
	if (opt.error)
		return (-1);
	return (total);
}
