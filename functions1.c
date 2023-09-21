#include "main.h"

/************************* OUTPUT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Output an unsigned number
 * @kind: List a of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Number of chars printed.
 */

int print_unsigned(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	int p = BUFF_SIZE - 2;
	unsigned long int mum = va_arg(kind, unsigned long int);

	mum = convert_size_unsgnd(mum, mass);

	if (mum == 0)
		buffer[p--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (mum > 0)
	{
		buffer[p--] = (mum % 10) + '0';
		mum /= 10;
	}
	p++;
	return (write_unsgnd(0, p, buffer, banner, span, precise, mass));
}

/************* OUTPUT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Ouput an unsigned number in octal notation
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Number of chars printed
 */

int print_octal(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	int p = BUFF_SIZE - 2;
	unsigned long int mum = va_arg(kind, unsigned long int);
	unsigned long int init_num = mum;

	UNUSED(span);
	mum = convert_size_unsgnd(mum, mass);

	if (mum == 0)
		buffer[p--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (mum > 0)
	{
		buffer[p--] = (mum % 8) + '0';
		mum /= 8;
	}
	if (banner & F_HASH && init_num != 0)
		buffer[p--] = '0';
	p++;
	return (write_unsgnd(0, p, buffer, banner, span, precise, mass));
}

/************** OUTPUT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Output an unsigned number in hexadecimal notation
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Number of chars printed
 */

int print_hexadecimal(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	return (print_hexa(kind, "0123456789abcdef", buffer,
				banner, 'x', span, precise, mass));
}

/************* OUTPUT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Output an unsigned number in upper hexadecimal notation
 * @kind: Lista of arguments
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @span: get span
 * @precise: Precise specification
 * @mass: Mass specifier
 * Return: Number of chars printed
 */

int print_hexa_upper(va_list kind, char buffer[],
		int banner, int span, int precise, int mass)
{
	return (print_hexa(kind, "0123456789ABCDEF", buffer,
				banner, 'X', span, precise, mass));
}

/************** OUTPUT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Output a hexadecimal number in lower or upper
 * @kind: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @banner:  Calculates active banner
 * @banner_ch: Calculates active banner
 * @span: get span
 * @precise: precise specification
 * @mss: Mass specifier
 * @mass: Mass specification
 * Return: Number of chars printed
 */

int print_hexa(va_list kind, char map_to[], char buffer[],
		int banner, char banner_ch, int span, int precise, int mass)
{
	int p = BUFF_SIZE - 2;
	unsigned long int mum = va_arg(kind, unsigned long int);
	unsigned long int init_num = mum;

	UNUSED(span);
	mum = convert_size_unsgnd(mum, mass);

	if (mum == 0)
		buffer[p--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (mum > 0)
	{
		buffer[p--] = map_to[mum % 16];
		mum /= 16;
	}

	if (banner & F_HASH && init_num != 0)
	{
		buffer[p--] = banner_ch;
		buffer[p--] = '0';
	}
	p++;
	return (write_unsgnd(0, p, buffer, banner, span, precise, mass));
}
