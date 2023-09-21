#include "main.h"

/* OUTPUT CHARACTER */

/**
 * print_char - Output a character
 * @kind: List a of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active flags
 * @span: Width
 * @precise: Precision specification
 * @mass: Size specifier
 * Return: Number of chars printed
 */

int print_char(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	char b = va_arg(kind, int);

	return (handle_write_char(b, buffer, banner, span, precise, mass));
}

/* OUTPUT A STRING */
/**
 * print_string - Output a string
 * @kind: List a of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active flags
 * @span: get width.
 * @precise: Precision specification
 * @mass: Size specifier
 * Return: Number of chars printed
 */

int print_string(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	int lent = 0, p;
	char *str = va_arg(kind, char *);

	UNUSED(buffer);
	UNUSED(banner);
	UNUSED(span);
	UNUSED(precise);
	UNUSED(mass);

	if (str == NULL)
	{
		str = "(null)";

		if (precise >= 6)
			str = "      ";
	}

	while (str[lent] != '\0')
		lent++;

	if (precise >= 0 && precise < lent)
		lent = precise;
	if (span > lent)
	{
		if (banner & F_MINUS)
		{
			write(1, &str[0], lent);
			for (p = span - lent; p > 0; p--)
				write(1, " ", 1);
			return (span);
		}
		else
		{
			for (p = span - lent; p > 0; p--)
				write(1, " ", 1);
			write(1, &str[0], lent);
			return (span);
		}
	}
	return (write(1, str, lent));
}

/* OUTPUT PERCENTAGE SIGN */
/**
 * print_percent - Prints a percent sign
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active flags
 * @span: get width.
 * @precise: Precision specification
 * @mass: Size specifier
 * Return: Number of chars printed
 */

int print_percent(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	UNUSED(kind);
	UNUSED(buffer);
	UNUSED(banner);
	UNUSED(span);
	UNUSED(precise);
	UNUSED(mass);
	return (write(1, "%%", 1));
}

/* OUTPUT INTEGER */
/**
 * print_int - Output integer
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active flags
 * @span: get width.
 * @precise: Precision specification
 * @mass: Size specifier
 * Return: Number of chars printed
 */

int print_int(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	int p = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(kind, long int);
	unsigned long int mum;

	m = convert_size_number(m, mass);

	if (m == 0)
		buffer[p--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	mum = (unsigned long int)m;

	if (m < 0)
	{
		mum = (unsigned long int)((-1) * m);
		is_negative = 1;
	}
	while (mum > 0)
	{
		buffer[p--] = (mum % 10) + '0';
		mum /= 10;
	}
	p++;

	return (write_number(is_negative, p, buffer, banner, span, precise, mass));
}

/* OUTPUT B */
/**
 * print_binary - Output an unsigned number
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active flags
 * @span: get width.
 * @precise: Precision specification
 * @mass: Size specifier
 * Return: Numbers of char printed.
 */

int print_binary(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	unsigned int m, o, p, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(banner);
	UNUSED(span);
	UNUSED(precise);
	UNUSED(mass);

	m = va_arg(kind, unsigned int);
	o = 2147483648; /* (2 ^ 31) */
	a[0] = m / o;
	for (p= 1; p < 32; p++)
	{
		o /= 2;
		a[p] = (m / o) % 2;
	}
	for (p = 0, sum = 0, count = 0; p < 32; p++)
	{
		sum += a[p];
		if (sum || p == 31)
		{
			char y = '0' + a[p];

			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}
