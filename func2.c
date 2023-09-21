#include "main.h"

/* OUTPUT POINTER */
/**
 * print_pointer - Output the value of a pointer variable
 * @kind: List a of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Number of chars printed.
 */

int print_pointer(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	char more_d = 0, padded = ' ';
	int indic = BUFF_SIZE - 2, lent = 2, padded_start = 1; /* lent=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(kind, void *);

	UNUSED(span);
	UNUSED(mass);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precise);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[indic--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		lent++;
	}
	if ((banner & F_ZERO) && !(banner & F_MINUS))
		padded = '0';
	if (banner & F_PLUS)
		more_d = '+', lent++;
	else if (banner & F_SPACE)
		more_d = ' ', lent++;
	indic++;
	/* return (write(1, &buffer[p], BUFF_SIZE - p - 1));*/
	return (write_pointer(buffer, indic, lent,
				span, banner, padded, more_d, padded_start));
}

/* OUTPUT NON PRINTABLE */
/**
 * output_non_printable - Prints ascii codes in hexa of non printable chars
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: <Mass> specifier
 * Return: Number of chars printed
 */

int print_non_printable(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	int p = 0, offsett = 0;
	char *str = va_arg(kind, char *);

	UNUSED(banner);
	UNUSED(span);
	UNUSED(precise);
	UNUSED(mass);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[p] != '\0')
	{
		if (is_printable(str[p]))
			buffer[p + offsett] = str[p];
		else
			offsett += append_hexa_code(str[p], buffer, p + offsett);
		p++;
	}
	buffer[p + offsett] = '\0';

	return (write(1, buffer, p + offsett));
}

/* OUTPUT REVERSE */
/**
 * print_reverse - Output reverse string.
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	char *str;
	int p, count = 0;

	UNUSED(buffer);
	UNUSED(banner);
	UNUSED(span);
	UNUSED(mass);

	str = va_arg(kind, char *);

	if (str == NULL)
	{
		UNUSED(precise);
		str = ")Null(";
	}
	for (p = 0; str[p]; p++)
		;

	for (p = p - 1; p >= 0; p--)
	{
		char y = str[p];

		write(1, &y, 1);
		count++;
	}
	return (count);
}

/* OUTPUT A STRING IN ROT13 */
/**
 * print_rot13string - Output a string in rot13.
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	char x;
	char *str;
	unsigned int p, q;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(kind, char *);
	UNUSED(buffer);
	UNUSED(banner);
	UNUSED(span);
	UNUSED(precise);
	UNUSED(mass);

	if (str == NULL)
		str = "(AHYY)";
	for (p = 0; str[p]; p++)
	{
		for (q = 0; in[q]; q++)
		{
			if (in[q] == str[p])
			{
				x = out[q];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[q])
		{
			x = str[p];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
