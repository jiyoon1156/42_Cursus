/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 17:45:49 by jhur              #+#    #+#             */
/*   Updated: 2020/05/13 15:43:37 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_read_flag(t_list *info, const char **format)
{
	while (**format == '-')
	{
		(*info).left = 1;
		(*format)++;
	}
	if (**format == '0')
	{
		(*info).zero_flag = 1;
		(*format)++;
	}
}

void	ft_has_width(t_list *info, const char **format, va_list *ap)
{
	(*info).width = ft_atoi(*format);
	if (**format == '*')
	{
		(*info).width = va_arg(*ap, int);
		if ((*info).width < 0)
		{
			(*info).width *= -1;
			(*info).left = 1;
		}
		(*format)++;
	}
	else
	{
		while (**format >= '0' && **format <= '9')
			(*format)++;
	}
}

void	ft_has_precision(t_list *info, char const **format, va_list *ap)
{
	if (**format == '.')
	{
		(*info).precision = 1;
		++(*format);
		(*info).p_len = ft_atoi(*format);
		if (**format == '*')
		{
			(*info).p_len = va_arg(*ap, int);
			(*format)++;
		}
		else
		{
			while (**format >= '0' && **format <= '9')
				(*format)++;
		}
	}
}

int		ft_has_spec(t_list info, const char **format, va_list *ap)
{
	int	result;

	result = 0;
	if (**format == 'c' || **format == 'C')
		result = c_conversion(ap, info);
	else if (**format == 's')
		result = s_conversion(ap, info);
	else if (**format == 'p')
		result = p_conversion(ap, info, *format);
	else if (**format == 'd' || **format == 'i' || **format == 'D')
		result = d_conversion(ap, info);
	else if (**format == 'u' || **format == 'U')
		result = u_conversion(ap, info);
	else if (**format == 'x')
		result = x_conversion(ap, info, *format);
	else if (**format == 'X')
		result = x_conversion(ap, info, *format);
	else if (**format == '%')
		result = percent_conversion(info);
	return (result);
}

int		ft_processing(const char **format, va_list *ap)
{
	t_list	info;
	int		result;
	int		count;

	count = 0;
	result = 0;
	info.zero_flag = 0;
	info.left = 0;
	info.precision = 0;
	info.p_len = 0;
	info.width = 0;
	while ((**format) != '%')
	{
		ft_putchar(**format);
		count++;
		(*format)++;
	}
	(*format)++;
	if (**format == '\0')
		return (-1);
	ft_read_flag(&info, format);
	if (**format == '\0')
		return (-1);
	ft_has_width(&info, format, ap);
	if (**format == '\0')
		return (-1);
	ft_has_precision(&info, format, ap);
	if (**format == '\0')
		return (-1);
	result = ft_has_spec(info, format, ap) + count;
	if (**format == '\0')
		return (-1);
	++(*format);
	return (result);
}
