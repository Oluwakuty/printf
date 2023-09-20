#include "main.h"

/**
 * _printf - custom printf function
 * @format: a character string parsed inn by the user
 * @...: denotes variable number of arguments
 *
 * Return: number of characters printed without the null byte
 */

int _printf(const char *format, ...);

int _printf(const char *format, ...)
{
	va_list myprint; /*declare the name of our list as myprint*/

	int format_len = strlen(format), char_len = 0, i;

	va_start(myprint, format); /*init arg list*/

	if (format == NULL) /*check invalid input*/
		return (-1);

	for (i = 0; i < format_len; i++)
	{
		if (format[i] != '%') /*check for char wth format*/
		{	char fp = format[i];

			write(1, &fp, 1);
			char_len++; /*increment string lenght*/
		} else
		{	int j = ++i;

			if (format[j] == '%') /*handle % convr*/
			{	char fp = format[j];

				write(1, &fp, 1);
				char_len++;
			} else if (format[j] == 'c') /*handle c convr*/
			{
				char c = va_arg(myprint, int);/*check single char*/

				if ((c >= ' ') && (c <= '~') && (c != '\0'))
				{
					write(1, &c, 1);
					char_len++;
				} else
					return (-1);
			} else if (format[j] == 's') /*handle s convr*/
			{
				char *s = va_arg(myprint, char *); /*store string in s*/
				int s_len = strlen(s), si;

				for (si = 0; si < s_len; si++)
				{
					if ((s[si] >= ' ') && (s[si] <= '~') && (s[si] != '\0'))
					{
						write(1, &s[si], 1);
						char_len++;
					} else
						return (-1);
				}
			}
		}
	}
	va_end(myprint);
	return (char_len);
}
