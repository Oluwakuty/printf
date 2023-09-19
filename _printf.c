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
	va_list args;

	va_start(args, format);
	int count = 0;

	while (*format)
	{
		if (*format == '%')
		{	format++; /* Move past '%'*/

			switch (*format) /* Handle different conversion specifiers */
			{	case 'c': {
						  char c = va_arg(args, int); /* Fetch char argument */

						_putchar(c);
						count++;
						break;
					}
				case 's': {
					char *str = va_arg(args, char *); /* Fetch string argument */

					for (int i = 0; str[i] != '\0'; i++)
					{
						_putchar(str[i]);
						count++;
					} break;
					}
				case '%':
					  _putchar('%');
					  count++;
					break;
				default: /* Unknown conversion specifier, ignore it */
				break;
			}
			_putchar(*format);
			count++;
			format++;
		} va_end(args);
		return (count);
	}
}
