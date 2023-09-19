#include "main.h"

/**
 * _printf - custom printf function
 * @format: a character string parsed inn by the user
 * @...: denotes variable number of arguments
 *
 * Return: number of characters printed without the null byte
 */

int _printf(const char *format, ...)
{
	va_list my_list;

	int count = 0;
	va_start(my_list, format);

	for (; *format != '\0'; format++)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break;
			if (*format == 'c')
			{
				char c = (char)va_arg(my_list, int);

				write(1, &c, 1);
				count++;
			} else if (*format == 's')
			{
				char *string = va_arg(my_list, char*);

				for (; *string != '\0'; string++)
				{
					write(1, string, 1);
					count++;
				}
			} else if (*format == '%')
			{
				write(1, "%", 1);
				write(1, format, 1);
				count += 2;
			}
		} else
		{
			write(1, format, 1);
			count++;
		}
	} va_end(my_list);
	return (count);
}
