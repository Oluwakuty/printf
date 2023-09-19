#include "main.h"

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	int print_chars = 0;
	va_list list_of_args;

	if (format == NULL)
	{ return (-1); }
	va_start(list_of_args, format);
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			print_chars++;
		} else
		{
			format++;
			if (*format == '\0')
				break;
			if (*format == '%')
			{
				write(1, format, 1);
				print_chars++;
			} else if (*format == 'c')
			{
				char c = va_arg(list_of_args, int);

				write(1, &c, 1);
				print_chars++;
			} else if (*format == 's')
			{
				char *str = va_arg(list_of_args, char*);
				int str_len = 0;

				while (str[str_len] != '\0')
					str_len++;
				write(1, str, str_len);
				print_chars += str_len;
			}
		} format++;
	} va_end(list_of_args);
	return (print_chars);
}

/**
 * handle_specifiers - Handle conversion specifiers
 * @format: format.
 * Return: void..
 */

void handle_specifiers(const char *format, ...)
{
	va_list args;
	va_start(args, format)

		for (int i = 0; format[i] != '\0'; i++)
		{
			if (format[i] == '%' && format[i + 1] == 'd')
			{
				int value = va_arg(args, int);

				write(1, value, 1);
				i++;
			}
			else if (format[i] == '%' && format[i + 1] == 'i')
			{
				int value = va_arg(args, int);

				write(1, value, 1);
				i++;
			}
			else 
			{
				putchar(format[i]);
			}
		}
	va_end(args);
}
