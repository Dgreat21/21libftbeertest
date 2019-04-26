/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgreat <dgreat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2019/04/26 19:40:28 by dgreat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "libft.h"


/*////////////////////////////////////////
 *
 * 		GO DOWN TO FUNC "test_all"
 * 		to disable (comment) functions
 * 		which you haven't done yet;
 *
 * ////////////////////////////////////////
 */


#define CHECK_NULL 0    /* check null-ptr? */
#define PRINT_LOGS 1	/* print logs?  !!! NOT WORKING !!! */
#define PRINT_DETAILED_LOGS 1 /* print detailed FAIL-logs? */
								/* !!! MAYBE TOOOOO LONG */

int total = 0;
int success = 0;

#define RED "\x1B[1m\x1B[31m"
#define GREEN "\x1B[1m\x1B[32m"
#define BLUE "\x1B[1m\x1B[34m"
#define WHITE "\x1B[0m"
#define BOLD "\x1B[1m"


char		*m_ft_int_to_unicode(int n, char *bytes)
{
	if (n < pow(2, 7))
		bytes[0] = (char)n;
	else if (n < pow(2, 11))
	{
		bytes[0] = 192 + n / 64;
		bytes[1] = 128 + n % 64;
	}
	else if (n < pow(2, 16))
	{
		bytes[0] = 224 + n / 4096;
		bytes[1] = 128 + (n / 64) % 64;
		bytes[2] = 128 + (n % 64);
	}
	else
	{
		bytes[0] = 240 + n / 262144;
		bytes[1] = 128 + (n / 4096) % 64;
		bytes[2] = 128 + (n / 64) % 64;
		bytes[3] = 128 + n % 64;
	}
	return (bytes);
}

void		m_ft_putchar_u_fd(int c, int fd)
{
	char uni_char[5];

	bzero(uni_char, 5);
	if (c >= 0 && c <= pow(2, 21) - 1)
	{
		m_ft_int_to_unicode(c, uni_char);
	}
	else
	{
		uni_char[0] = (char)c;
	}
	write(fd, uni_char, strlen(uni_char));
}

void print_total()
{
	printf(BLUE "\n  You have been graded by Moulinette");
	printf("\n      Success rate is ");
	if (success == total)
		printf(GREEN);
	else
		printf(RED);
	printf("%d/%d\n", success, total);
	printf(WHITE);
	if (success == total)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				m_ft_putchar_u_fd(127866, 1);
			}
			write(1, "\n", 1);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				m_ft_putchar_u_fd(0x1F4A9, 1);
			}
			write(1, "\n", 1);
		}
	}
}

typedef struct s_assert
{
	char *f;
	char *t;
	char *s1;
	char *s2;
}			t_assert;

char *Itoa(int n)
{
	int sign;
	char *res;
	int tmp[10];
	int i;
	int j;

	sign = (n >= 0 ? 1 : -1);
	i = (n == 0 ? 1 : 0);
	j = 0;
	tmp[0] = 0;
	while (n != 0)
	{
		tmp[i] = n % 10 * sign;
		n /= 10;
		i++;
	}
	res = (char*)malloc(i + (sign == -1) + 1);
	if (!res)
		return (0);
	if (sign == -1)
		res[j++] = '-';
	while (i > 0)
		res[j++] = tmp[--i] + '0';
	res[j] = 0;
	return (res);
}

char *str_to_code_sentence(char *str, int len)
{
	char *res = (char*)malloc(10240);
	res[0] = 0;
	for (int i = 0; i < len; i++)
	{
		strlcat(res, Itoa(str[i]), 10240);
	}
	return res;
}

void ft_assert(t_assert a)
{
	if (PRINT_LOGS)
	{
		printf(BOLD "\n%s", a.f);
		printf(WHITE ":%s: ", a.t);
	}
	total++;
	if (strcmp(a.s1, a.s2) == 0)
	{
		success++;
		if (PRINT_LOGS)
		{
			printf(GREEN "OK");
		}
	}
	else
	{
		if (PRINT_LOGS)
		{
			printf(RED "FAIL%c", 7);
			if (PRINT_DETAILED_LOGS)
			{
				printf(WHITE "\n'If you see numbers sequence instead of string:");
				printf("\n it's ASCII-codes sequence'");
				printf(RED "\nTHEIR(usually):\n<%s>\n\tvs\nYOURS(usually):\n<%s>", a.s1, a.s2);
			}
		}
	}
	printf(WHITE "");
	if (PRINT_LOGS)
	{
		fflush(stdout);
	}
}

void ft_memset_test()
{
	t_assert ass = (t_assert){"MEMSET_TEST", "", "", ""};

	const char *null = 0;

	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_memset((char*)null, 10, 100));
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test part";
	res = ft_memset(res, 54, 5);
	res_e = memset(res_e, 54, 5);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	res = ft_memset(res, 100, 1);
	res_e = memset(res_e, 100, 1);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	res = ft_memset(res, 86, 11);
	res_e = memset(res_e, 86, 11);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	res = ft_memset(res, 76, 1000);
	res_e = memset(res_e, 76, 1000);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test filling_by_zeroes";
	res = ft_memset(res, 56, 100);
	res_e = memset(res_e, 56, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_bzero_test()
{
	t_assert ass = (t_assert){"BZERO_TEST", "", "", ""};

	const char *null = 0;

	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ft_bzero((char*)null, 100);
		ass.s2 = Itoa(0);
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test part";
	ft_bzero(res, 5);
	bzero(res_e, 5);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	ft_bzero(res, 1);
	bzero(res_e, 1);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	ft_bzero(res, 11);
	bzero(res_e, 11);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	ft_bzero(res, 1000);
	bzero(res_e, 1000);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test filling_by_zeroes";
	ft_bzero(res, 100);
	bzero(res_e, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memcpy_test()
{
	t_assert ass = (t_assert){"MEMCPY_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;


	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_memcpy((char*)null, null, 100));
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test part";
	res = ft_memcpy(res, str_full, 5);
	res_e = memcpy(res_e, str_full, 5);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	res = ft_memcpy(res, str_empty, 0);
	res_e = memcpy(res_e, str_empty, 0);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	res = ft_memcpy(res, str_full, 11);
	res_e = memcpy(res_e, str_full, 11);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	res = ft_memcpy(res, str_big, 1000);
	res_e = memcpy(res_e, str_big, 1000);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *ss = (char*)malloc(200);
	if (!ss)
	{
		printf(BLUE "\n MY MALLOC FAIL");
		return ;
	}
	for (int i = 0; i < 200; i++)
	{
		ss[i] = 'A';
	}
	ss[199] = 0;

	ass.t = "test filling_by_zeroes";
	res = ft_memcpy(res, ss, 100);
	res_e = memcpy(res_e, ss, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);
	free(ss);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memccpy_test()
{
	t_assert ass = (t_assert){"MEMCCPY_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;


	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_memccpy((char*)null, null, 2000, 100));
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	res[431] = (unsigned char)9000;
	res_e[431] = (unsigned char)9000;
	char *ss = (char*)malloc(500);
	if (!ss)
	{
		printf(BLUE "\n MY MALLOC FAIL");
		return ;
	}
	for (int i = 0; i < 500; i++)
	{
		ss[i] = 'A';
	}
	ss[499] = 0;

	ass.t = "test part 1";
	ft_memccpy(res, ss, 9000, 500);
	memccpy(res_e, ss, 9000, 500);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	res[431] = (unsigned char)9000;
	res_e[431] = (unsigned char)9000;
	for (int i = 0; i < 500; i++)
	{
		ss[i] = 'A';
	}
	ss[499] = 0;

	ass.t = "test part 2";
	ft_memccpy(res, ss, 9001, 500);
	memccpy(res_e, ss, 9001, 500);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	res[431] = (unsigned char)9000;
	for (int i = 0; i < 500; i++)
	{
		ss[i] = 'A';
	}
	ss[499] = 0;
	char *tmp = res;
	ass.t = "test ret 1";
	res = ft_memccpy(res, ss, 9001, 500);
	ass.s1 = Itoa((int)res);
	res = tmp;
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	res[431] = (unsigned char)9000;
	res = memccpy(res, ss, 9001, 500);
	ass.s2 = Itoa((int)res);
	ft_assert(ass);

	res = tmp;
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	res[431] = (unsigned char)9000;
	for (int i = 0; i < 500; i++)
	{
		ss[i] = 'A';
	}
	ss[499] = 0;
	tmp = res;
	ass.t = "test ret 2";
	res = ft_memccpy(res, ss, 9000, 500);
	ass.s1 = Itoa((int)res);
	res = tmp;
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	res[431] = (unsigned char)9000;
	res = memccpy(res, ss, 9000, 500);
	ass.s2 = Itoa((int)res);
	ft_assert(ass);

	res = tmp;
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	res[431] = (unsigned char)9000;
	tmp = res;
	ass.t = "test ret 3";
	res = ft_memccpy(res, str_full, INT_MIN, 11);
	ass.s1 = Itoa((int)res);
	res = tmp;
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	res[431] = (unsigned char)9000;
	res = memccpy(res, str_full, INT_MIN, 11);
	ass.s2 = Itoa((int)res);
	ft_assert(ass);

	res = tmp;
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	ass.t = "test empty";
	ft_memccpy(res, str_empty, 10, 0);
	memccpy(res_e, str_empty, 10, 0);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test full";
	ft_memccpy(res, str_full, INT_MIN, 11);
	memccpy(res_e, str_full, INT_MIN, 11);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	ft_memccpy(res, str_big, 0, 1000);
	memccpy(res_e, str_big, 0, 1000);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	for (int i = 0; i < 200; i++)
	{
		ss[i] = 'A';
	}
	ss[199] = 0;

	ass.t = "test filling_by_zeroes";
	ft_memccpy(res, ss, INT_MIN, 100);
	memccpy(res_e, ss, INT_MIN, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);
	free(ss);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memmove_test()
{
	t_assert ass = (t_assert){"MEMMOVE_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;


	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_memmove((char*)null, null, 100));
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test part";
	res = ft_memmove(res, str_full, 5);
	res_e = memmove(res_e, str_full, 5);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	res = ft_memmove(res, str_empty, 0);
	res_e = memmove(res_e, str_empty, 0);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	res = ft_memmove(res, str_full, 11);
	res_e = memmove(res_e, str_full, 11);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	res = ft_memmove(res, str_big, 1000);
	res_e = memmove(res_e, str_big, 1000);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *ss = (char*)malloc(200);
	if (!ss)
	{
		printf(BLUE "\n MY MALLOC FAIL");
		return ;
	}
	for (int i = 0; i < 200; i++)
	{
		ss[i] = 'A';
	}
	ss[199] = 0;

	ass.t = "test filling_by_zeroes";
	res = ft_memmove(res, ss, 100);
	res_e = memmove(res_e, ss, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	ass.t = "test overlap 1";
	res = ft_memmove(res, res, 100);
	res_e = memmove(res_e, res_e, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	ass.t = "test overlap 2";
	res = ft_memmove(res, res, 0);
	res_e = memmove(res_e, res_e, 0);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	ass.t = "test overlap 3";
	res = ft_memmove(res, res, 1000);
	res_e = memmove(res_e, res_e, 1000);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	ass.t = "test overlap 4";
	res = ft_memmove(res, res + 100, 500);
	res_e = memmove(res_e, res_e + 100, 500);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;
	ass.t = "test overlap 5";
	ft_memmove(res + 100, res, 500);
	memmove(res_e + 100, res_e, 500);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);
	free(ss);


	res_e = (char*)malloc(500000000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 500000000; i++)
	{
		res_e[i] = 'A';
	}

	res = (char*)malloc(500000000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 500000000; i++)
	{
		res[i] = 'A';
	}
	ass.t = "test overlap BIG";
	ft_memmove(res, res + 1, 500000000 - 1);
	memmove(res_e, res_e + 1, 500000000 - 1);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	free(res);
	free(res_e);


	char dst1[24];
	char dst2[24];
	char *data = "1234567890";
	memset(dst1, 'A', 24);
	memset(dst2, 'A', 24);
	strlcpy(dst1, data, 24);
	strlcpy(dst2, data, 24);
	dst1[10] = 'A';
	dst2[10] = 'A';

	memmove(dst1, dst1 + 3, 20);
	ft_memmove(dst2, dst2 + 3, 20);

	ass.t = "test overlap 6";
	ass.s1 = str_to_code_sentence(dst1, 24);
	ass.s2 = str_to_code_sentence(dst2, 24);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memchr_test()
{
	t_assert ass = (t_assert){"MEMCHR_TEST", "", "", ""};

	const char s1[] = "qwertyuio";
	const char s2[] = "aaaaa";
	const char s3[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_memchr((char*)null, 7, 7));
		ft_assert(ass);
	}

	ass.t = "test 1";
	ass.s1 = Itoa((int) memchr(s1, 'q', 10));
	ass.s2 = Itoa((int) ft_memchr(s1, 'q', 10));
	ft_assert(ass);

	ass.t = "test 2";
	ass.s1 = Itoa((int) memchr(s1, 'i', 10));
	ass.s2 = Itoa((int) ft_memchr(s1, 'i', 10));
	ft_assert(ass);

	ass.t = "test 3";
	ass.s1 = Itoa((int) memchr(s1, '0', 10));
	ass.s2 = Itoa((int) ft_memchr(s1, '0', 10));
	ft_assert(ass);

	ass.t = "test 4";
	ass.s1 = Itoa((int) memchr(s2, 'a', 6));
	ass.s2 = Itoa((int) ft_memchr(s2, 'a', 6));
	ft_assert(ass);

	ass.t = "test 5";
	ass.s1 = Itoa((int) memchr(s1, 0, 10));
	ass.s2 = Itoa((int) ft_memchr(s1, 0, 10));
	ft_assert(ass);

	ass.t = "test 6";
	ass.s1 = Itoa((int) memchr(s1, 1000, 10));
	ass.s2 = Itoa((int) ft_memchr(s1, 1000, 10));
	ft_assert(ass);

	ass.t = "test 7";
	ass.s1 = Itoa((int) memchr(s3, 'q', 1));
	ass.s2 = Itoa((int) ft_memchr(s3, 'q', 1));
	ft_assert(ass);

	ass.t = "test 8";
	ass.s1 = Itoa((int) memchr(s3, 0, 1));
	ass.s2 = Itoa((int) ft_memchr(s3, 0, 1));
	ft_assert(ass);

	ass.t = "test 9";
	ass.s1 = Itoa((int) memchr(s1, 'y', 3));
	ass.s2 = Itoa((int) ft_memchr(s1, 'y', 3));
	ft_assert(ass);

	ass.t = "test 10";
	ass.s1 = Itoa((int) memchr(s3, 'y', 6));
	ass.s2 = Itoa((int) ft_memchr(s3, 'y', 6));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memcmp_test()
{
	t_assert ass = (t_assert){"MEMCMP_TEST", "", "", ""};

	const char s1[] = "aaa";
	const char s2[] = "aaa";
	const char s3[] = "aaz";
	const char s4[] = "";
	const char s5[] = "";

	ass.t = "test equal 1";
	ass.s1 = Itoa(memcmp(s1, s2, 4) == 0);
	ass.s2 = Itoa(ft_memcmp(s1, s2, 4) == 0);
	ft_assert(ass);

	ass.t = "test equal 2";
	ass.s1 = Itoa(memcmp(s1, s2, 3) == 0);
	ass.s2 = Itoa(ft_memcmp(s1, s2, 3) == 0);
	ft_assert(ass);

	ass.t = "test equal 3";
	ass.s1 = Itoa(memcmp(s4, s5, 0) == 0);
	ass.s2 = Itoa(ft_memcmp(s4, s5, 0) == 0);
	ft_assert(ass);

	ass.t = "test equal 3-1";
	ass.s1 = Itoa(memcmp(s4, s5, 1) == 0);
	ass.s2 = Itoa(ft_memcmp(s4, s5, 1) == 0);
	ft_assert(ass);

	ass.t = "test equal 4";
	ass.s1 = Itoa(memcmp(s3, s1, 2) == 0);
	ass.s2 = Itoa(ft_memcmp(s3, s1, 2) == 0);
	ft_assert(ass);

	ass.t = "test unequal 0";
	ass.s1 = Itoa(memcmp(s5, s3, 1) < 0);
	ass.s2 = Itoa(ft_memcmp(s5, s3, 1) < 0);
	ft_assert(ass);

	ass.t = "test unequal 1";
	ass.s1 = Itoa(memcmp(s1, s3, 4) < 0);
	ass.s2 = Itoa(ft_memcmp(s1, s3, 4) < 0);
	ft_assert(ass);

	ass.t = "test unequal 1-1";
	ass.s1 = Itoa(memcmp(s1, s3, 3) < 0);
	ass.s2 = Itoa(ft_memcmp(s1, s3, 3) < 0);
	ft_assert(ass);

	ass.t = "test unequal 2";
	ass.s1 = Itoa(memcmp(s5, s3, 1) < 0);
	ass.s2 = Itoa(ft_memcmp(s5, s3, 1) < 0);
	ft_assert(ass);

	const int arr1[10] = {1, 2, 3, INT_MAX, 5, INT_MIN, 7000000, 8, 9, 0};
	const int arr2[10] = {1, 2, 3, INT_MAX, 5, INT_MIN, 7000000, 8, 9, 0};
	ass.t = "test equal int 1";
	ass.s1 = Itoa(memcmp(arr1, arr2, 40) == 0);
	ass.s2 = Itoa(ft_memcmp(arr1, arr2, 40) == 0);
	ft_assert(ass);

	ass.t = "test equal int 2";
	ass.s1 = Itoa(memcmp(arr1, arr1, 40) == 0);
	ass.s2 = Itoa(ft_memcmp(arr1, arr1, 40) == 0);
	ft_assert(ass);

	const int arr3[10] = {1, 2, 3, INT_MAX, 5, INT_MIN, 7000000, 8, 9, 100};
	ass.t = "test unequal int";
	ass.s1 = Itoa(memcmp(arr1, arr3, 40) > 0);
	ass.s2 = Itoa(ft_memcmp(arr1, arr3, 40) > 0);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strlen_test()
{
	t_assert ass = (t_assert){"STRLEN_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strlen(null));
		ft_assert(ass);
	}

	ass.t = "test empty";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa((int)ft_strlen(str_empty));
	ft_assert(ass);

	ass.t = "test full";
	ass.s1 = Itoa(11);
	ass.s2 = Itoa((int)ft_strlen(str_full));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strdup_test()
{
	t_assert ass = (t_assert){"STRDUP_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;
	char *res;

	char *str_big = (char*)malloc(100000000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 100000000; i++)
	{
		str_big[i] = 'A';
	}

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strdup(null));
		ft_assert(ass);
	}

	ass.t = "test empty";
	ass.s1 = (char*)str_empty;
	res = ft_strdup(str_empty);
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	ass.t = "test full";
	ass.s1 = (char*)str_full;
	res = ft_strdup(str_full);
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	ass.t = "test big";
	ass.s1 = str_big;
	res = ft_strdup(str_big);
	ass.s2 = res;
	ft_assert(ass);
	free(res);
	free(str_big);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strcpy_test()
{
	t_assert ass = (t_assert){"STRCPY_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;


	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strcpy((char*)null, null));
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test part";
	res = ft_strcpy(res, str_full);
	res_e = strcpy(res_e, str_full);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	res = ft_strcpy(res, str_empty);
	res_e = strcpy(res_e, str_empty);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	res = ft_strcpy(res, str_full);
	res_e = strcpy(res_e, str_full);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	res = ft_strcpy(res, str_big);
	res_e = strcpy(res_e, str_big);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test filling_by_zeroes";
	res = ft_strcpy(res, str_full);
	res_e = strcpy(res_e, str_full);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	free(res);
	free(res_e);
	free(str_big);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strncpy_test()
{
	t_assert ass = (t_assert){"STRNCPY_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;


	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strncpy((char*)null, null, 100));
		ft_assert(ass);
	}


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test part";
	res = ft_strncpy(res, str_full, 5);
	res_e = strncpy(res_e, str_full, 5);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	res = ft_strncpy(res, str_empty, 0);
	res_e = strncpy(res_e, str_empty, 0);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	res = ft_strncpy(res, str_full, 11);
	res_e = strncpy(res_e, str_full, 11);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	res = ft_strncpy(res, str_big, 1000);
	res_e = strncpy(res_e, str_big, 1000);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test filling_by_zeroes";
	res = ft_strncpy(res, str_full, 100);
	res_e = strncpy(res_e, str_full, 100);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

/*void ft_strlcpy_test()
{
	t_assert ass = (t_assert){"STRLCPY_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;
	size_t a;
	size_t b;


	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	char *str_big = (char*)malloc(1000);
	if (!str_big)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		str_big[i] = 'B';
	}
	str_big[999] = 0;



	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strlcpy((char*)null, null, 123));
		ft_assert(ass);
	}

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test wrong len 1";
	a = ft_strlcpy(res, str_full, 5);
	b = strlcpy(res_e, str_full, 5);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test wrong len 2";
	a = ft_strlcpy(res, str_full, 500);
	b = strlcpy(res_e, str_full, 500);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test empty";
	a = ft_strlcpy(res, str_empty, 1);
	b = strlcpy(res_e, str_empty, 1);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;


	ass.t = "test full";
	a = ft_strlcpy(res, str_full, 12);
	b = strlcpy(res_e, str_full, 12);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test big";
	a = ft_strlcpy(res, str_big, 1000);
	b = strlcpy(res_e, str_big, 1000);
	ass.s1 = res_e;
	ass.s2 = res;
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	ass.t = "test filling";
	a = ft_strlcpy(res, str_full, 5);
	b = strlcpy(res_e, str_full, 5);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);


	free(res);
	free(res_e);
	free(str_big);

	if (PRINT_LOGS) {
		printf("\n");
	}
}*/

void ft_strcat_test()
{
	t_assert ass = (t_assert){"STRCAT_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strcat((char*)null, null));
		ft_assert(ass);
	}

	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[5] = 0;
	res_e[5] = 0;

	ass.t = "test empty";
	strcat(res_e, str_empty);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ft_strcat(res, str_empty);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[0] = 0;
	res_e[0] = 0;

	ass.t = "test full";
	strcat(res_e, str_full);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ft_strcat(res, str_full);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strncat_test()
{
	t_assert ass = (t_assert){"STRNCAT_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strncat((char*)null, null, 1));
		ft_assert(ass);
	}

	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[5] = 0;
	res_e[5] = 0;

	ass.t = "test empty";
	strncat(res_e, str_empty, 0);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ft_strncat(res, str_empty, 0);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[0] = 0;
	res_e[0] = 0;

	ass.t = "test full 1";
	strncat(res_e, str_full, 11);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ft_strncat(res, str_full, 11);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[10] = 0;
	res_e[10] = 0;

	ass.t = "test full 2";
	strncat(res_e, str_full, 5);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ft_strncat(res, str_full, 5);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[10] = 0;
	res_e[10] = 0;

	ass.t = "test full 3";
	strncat(res_e, str_full, 110);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	ft_strncat(res, str_full, 110);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strlcat_test()
{
	printf(BLUE "\nSecond test whith same name -");
	printf("\n  is checking strlcat-returned value");
	printf(WHITE);
	t_assert ass = (t_assert){"STRLCAT_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;
	size_t a;
	size_t b;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strlcat((char*)null, null, 0));
		ft_assert(ass);
	}

	char *res_e = (char*)malloc(1000);
	if (!res_e)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	char *res = (char*)malloc(1000);
	if (!res)
	{
		printf("\nNOT ALLOCED");
		return ;
	}
	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[5] = 0;
	res_e[5] = 0;

	ass.t = "test empty";
	a = strlcat(res_e, str_empty, 1000);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	b = ft_strlcat(res, str_empty, 1000);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);


	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[0] = 0;
	res_e[0] = 0;

	ass.t = "test full 1";
	a = strlcat(res_e, str_full, 11);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	b = ft_strlcat(res, str_full, 11);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[10] = 0;
	res_e[10] = 0;

	ass.t = "test full 2";
	a = strlcat(res_e, str_full, 5);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	b = ft_strlcat(res, str_full, 5);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	for (int i = 0; i < 1000; i++)
	{
		res_e[i] = 'A';
	}
	res_e[999] = 0;

	for (int i = 0; i < 1000; i++)
	{
		res[i] = 'A';
	}
	res[999] = 0;

	res[10] = 0;
	res_e[10] = 0;

	ass.t = "test full 3";
	a = strlcat(res_e, str_full, 110);
	ass.s1 = str_to_code_sentence(res_e, 1000);
	b = ft_strlcat(res, str_full, 110);
	ass.s2 = str_to_code_sentence(res, 1000);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);


	char str1[8] = "hello\0\0\0";
	char str2[8] = "hello\0\0\0";
	ass.t = "test by Ilyuha";
	a = strlcat(str1, "kek", 8);
	ass.s1 = str_to_code_sentence(str1, 8);
	b = ft_strlcat(str2, "kek", 8);
	ass.s2 = str_to_code_sentence(str2, 8);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	char str3[8] = "hello\0\0\0";
	char str4[8] = "hello\0\0\0";
	ass.t = "test zero-size 1";
	a = strlcat(str3, "kek", 0);
	ass.s1 = str_to_code_sentence(str1, 8);
	b = ft_strlcat(str4, "kek", 0);
	ass.s2 = str_to_code_sentence(str2, 8);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	char str5[1] = "";
	char str6[1] = "";
	ass.t = "test zero-len 2";
	a = strlcat(str5, "", 1);
	ass.s1 = str_to_code_sentence(str1, 1);
	b = ft_strlcat(str6, "", 1);
	ass.s2 = str_to_code_sentence(str2, 1);
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);

	char str7[2] = "\0";
	char str8[2] = "\0";
	ass.t = "test zero-size 3";
	a = strlcat(str7, "", 0);
	ass.s1 = str7;
	b = ft_strlcat(str8, "", 0);
	ass.s2 = str8;
	ft_assert(ass);
	ass.s1 = Itoa((int)a);
	ass.s2 = Itoa((int)b);
	ft_assert(ass);


	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strchr_test()
{
	t_assert ass = (t_assert){"STRCHR_TEST", "", "", ""};

	const char s1[] = "qwertyuio";
	const char s2[] = "aaaaa";
	const char s3[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strchr((char*)null, 7));
		ft_assert(ass);
	}

	ass.t = "test 1";
	ass.s1 = Itoa((int) strchr(s1, 'q'));
	ass.s2 = Itoa((int) ft_strchr(s1, 'q'));
	ft_assert(ass);

	ass.t = "test 2";
	ass.s1 = Itoa((int) strchr(s1, 'i'));
	ass.s2 = Itoa((int) ft_strchr(s1, 'i'));
	ft_assert(ass);

	ass.t = "test 3";
	ass.s1 = Itoa((int) strchr(s1, '0'));
	ass.s2 = Itoa((int) ft_strchr(s1, '0'));
	ft_assert(ass);

	ass.t = "test 4";
	ass.s1 = Itoa((int) strchr(s2, 'a'));
	ass.s2 = Itoa((int) ft_strchr(s2, 'a'));
	ft_assert(ass);

	ass.t = "test 5";
	ass.s1 = Itoa((int) strchr(s1, 0));
	ass.s2 = Itoa((int) ft_strchr(s1, 0));
	ft_assert(ass);

	ass.t = "test 6";
	ass.s1 = Itoa((int) strchr(s1, 1000));
	ass.s2 = Itoa((int) ft_strchr(s1, 1000));
	ft_assert(ass);

	ass.t = "test 7";
	ass.s1 = Itoa((int) strchr(s3, 'q'));
	ass.s2 = Itoa((int) ft_strchr(s3, 'q'));
	ft_assert(ass);

	ass.t = "test 8";
	ass.s1 = Itoa((int) strchr(s3, 0));
	ass.s2 = Itoa((int) ft_strchr(s3, 0));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strrchr_test()
{
	t_assert ass = (t_assert){"STRRCHR_TEST", "", "", ""};

	const char s1[] = "qwertyuio";
	const char s2[] = "aaaaa";
	const char s3[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strrchr((char*)null, 7));
		ft_assert(ass);
	}

	ass.t = "test 1";
	ass.s1 = Itoa((int) strrchr(s1, 'q'));
	ass.s2 = Itoa((int) ft_strrchr(s1, 'q'));
	ft_assert(ass);

	ass.t = "test 2";
	ass.s1 = Itoa((int) strrchr(s1, 'i'));
	ass.s2 = Itoa((int) ft_strrchr(s1, 'i'));
	ft_assert(ass);

	ass.t = "test 3";
	ass.s1 = Itoa((int) strrchr(s1, '0'));
	ass.s2 = Itoa((int) ft_strrchr(s1, '0'));
	ft_assert(ass);

	ass.t = "test 4";
	ass.s1 = Itoa((int) strrchr(s2, 'a'));
	ass.s2 = Itoa((int) ft_strrchr(s2, 'a'));
	ft_assert(ass);

	ass.t = "test 5";
	ass.s1 = Itoa((int) strrchr(s1, 0));
	ass.s2 = Itoa((int) ft_strrchr(s1, 0));
	ft_assert(ass);

	ass.t = "test 6";
	ass.s1 = Itoa((int) strrchr(s1, 1000));
	ass.s2 = Itoa((int) ft_strrchr(s1, 1000));
	ft_assert(ass);

	ass.t = "test 7";
	ass.s1 = Itoa((int) strrchr(s3, 'q'));
	ass.s2 = Itoa((int) ft_strrchr(s3, 'q'));
	ft_assert(ass);

	ass.t = "test 8";
	ass.s1 = Itoa((int) strrchr(s3, 0));
	ass.s2 = Itoa((int) ft_strrchr(s3, 0));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strstr_test()
{
	t_assert ass = (t_assert){"STRSTR_TEST", "", "", ""};

	const char s1[] = "qwertyuio";
	const char s2[] = "aaaaa";
	const char s3[] = "";
	const char *null = 0;

	if (CHECK_NULL)
	{
		ass.t = "test null";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strstr((const char*)null, (const char*)null));
		ft_assert(ass);
	}

	ass.t = "test 1";
	ass.s1 = Itoa((int) strstr(s1, "q"));
	ass.s2 = Itoa((int) ft_strstr(s1, "q"));
	ft_assert(ass);

	ass.t = "test 2";
	ass.s1 = Itoa((int) strstr(s1, "i"));
	ass.s2 = Itoa((int) ft_strstr(s1, "i"));
	ft_assert(ass);

	ass.t = "test 3";
	ass.s1 = Itoa((int) strstr(s1, "0"));
	ass.s2 = Itoa((int) ft_strstr(s1, "0"));
	ft_assert(ass);

	ass.t = "test 4";
	ass.s1 = Itoa((int) strstr(s2, "a"));
	ass.s2 = Itoa((int) ft_strstr(s2, "a"));
	ft_assert(ass);

	ass.t = "test 5";
	ass.s1 = Itoa((int) strstr(s1, "\0"));
	ass.s2 = Itoa((int) ft_strstr(s1, "\0"));
	ft_assert(ass);

	ass.t = "test 6";
	ass.s1 = Itoa((int) strstr(s3, "q"));
	ass.s2 = Itoa((int) ft_strstr(s3, "q"));
	ft_assert(ass);

	ass.t = "test 7";
	ass.s1 = Itoa((int) strstr(s3, ""));
	ass.s2 = Itoa((int) ft_strstr(s3, ""));
	ft_assert(ass);

	ass.t = "test 8";
	ass.s1 = Itoa((int) strstr(s1, "erty"));
	ass.s2 = Itoa((int) ft_strstr(s1, "erty"));
	ft_assert(ass);

	ass.t = "test 9";
	ass.s1 = Itoa((int) strstr(s1, "erto"));
	ass.s2 = Itoa((int) ft_strstr(s1, "erto"));
	ft_assert(ass);

	ass.t = "test 10";
	ass.s1 = Itoa((int) strstr("abcdedef", "def"));
	ass.s2 = Itoa((int) ft_strstr("abcdedef", "def"));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strnstr_test()
{
	t_assert ass = (t_assert){"STRNSTR_TEST", "", "", ""};

	const char s1[] = "qwertyuio";
	const char s2[] = "aaaaa";
	const char s3[] = "";

	ass.t = "test 1";
	ass.s1 = Itoa((int) strnstr(s1, "q", 100));
	ass.s2 = Itoa((int) ft_strnstr(s1, "q", 100));
	ft_assert(ass);

	ass.t = "test 1-0";
	ass.s1 = Itoa((int) strnstr(s1, "q", 0));
	ass.s2 = Itoa((int) ft_strnstr(s1, "q", 0));
	ft_assert(ass);

	ass.t = "test 1-1";
	ass.s1 = Itoa((int) strnstr(s1, "q", 1));
	ass.s2 = Itoa((int) ft_strnstr(s1, "q", 1));
	ft_assert(ass);

	ass.t = "test 1-2";
	ass.s1 = Itoa((int) strnstr(s1, "q", 2));
	ass.s2 = Itoa((int) ft_strnstr(s1, "q", 2));
	ft_assert(ass);

	ass.t = "test 1-3";
	ass.s1 = Itoa((int) strnstr(s1, "q", 3));
	ass.s2 = Itoa((int) ft_strnstr(s1, "q", 3));
	ft_assert(ass);

	ass.t = "test 2";
	ass.s1 = Itoa((int) strnstr(s1, "i", 5));
	ass.s2 = Itoa((int) ft_strnstr(s1, "i", 5));
	ft_assert(ass);

	ass.t = "test 3";
	ass.s1 = Itoa((int) strnstr(s1, "0", 5));
	ass.s2 = Itoa((int) ft_strnstr(s1, "0", 5));
	ft_assert(ass);

	ass.t = "test 4";
	ass.s1 = Itoa((int) strnstr(s2, "a", 5));
	ass.s2 = Itoa((int) ft_strnstr(s2, "a", 5));
	ft_assert(ass);

	ass.t = "test 5";
	ass.s1 = Itoa((int) strnstr(s1, "\0", 7));
	ass.s2 = Itoa((int) ft_strnstr(s1, "\0", 7));
	ft_assert(ass);

	ass.t = "test 6";
	ass.s1 = Itoa((int) strnstr(s3, "q", 3));
	ass.s2 = Itoa((int) ft_strnstr(s3, "q", 3));
	ft_assert(ass);

	ass.t = "test 7";
	ass.s1 = Itoa((int) strnstr(s3, "", 6));
	ass.s2 = Itoa((int) ft_strnstr(s3, "", 6));
	ft_assert(ass);

	ass.t = "test 8";
	ass.s1 = Itoa((int) strnstr(s1, "erty", 15));
	ass.s2 = Itoa((int) ft_strnstr(s1, "erty", 15));
	ft_assert(ass);

	ass.t = "test 9";
	ass.s1 = Itoa((int) strnstr(s1, "erto", 15));
	ass.s2 = Itoa((int) ft_strnstr(s1, "erto", 15));
	ft_assert(ass);

	ass.t = "test 10";
	ass.s1 = Itoa((int) strnstr(s1, "erty", 5));
	ass.s2 = Itoa((int) ft_strnstr(s1, "erty", 5));
	ft_assert(ass);

	ass.t = "test 11";
	ass.s1 = Itoa((int) strnstr("abcdedef", "def", 9));
	ass.s2 = Itoa((int) ft_strnstr((const char *)"abcdedef", (const char *)"def", 9));
	ft_assert(ass);
	
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strcmp_test()
{
	t_assert ass = (t_assert){"STRCMP_TEST", "", "", ""};

	const char s1[] = "aaa";
	const char s2[] = "aaa";
	const char s3[] = "aab";
	const char s4[] = "";
	const char s5[] = "";

	ass.t = "test equal 1";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(ft_strcmp(s1, s2));
	ft_assert(ass);

	ass.t = "test equal 2";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(ft_strcmp(s4, s5));
	ft_assert(ass);

	ass.t = "test equal 3";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(ft_strcmp(s4, s5));
	ft_assert(ass);

	ass.t = "test unequal 1";
	ass.s1 = Itoa(strcmp(s1, s3) < 0);
	ass.s2 = Itoa(ft_strcmp(s1, s3) < 0);
	ft_assert(ass);

	ass.t = "test unequal 2";
	ass.s1 = Itoa(strcmp(s3, s5) > 0);
	ass.s2 = Itoa(ft_strcmp(s3, s5) > 0);
	ft_assert(ass);

	ass.t = "test non_ascii 1";
	ass.s1 = Itoa(strcmp("\200\0", "\200\0") == 0);
	ass.s2 = Itoa(ft_strcmp("\200\0", "\200\0") == 0);
	ft_assert(ass);

	ass.t = "test non_ascii 2";
	ass.s1 = Itoa(strcmp("\200\0", "\0") < 0);
	ass.s2 = Itoa(ft_strcmp("\200\0", "\0") < 0);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strncmp_test()
{
	t_assert ass = (t_assert){"STRNCMP_TEST", "", "", ""};

	const char s1[] = "aaa";
	const char s2[] = "aaa";
	const char s3[] = "aaz";
	const char s4[] = "";
	const char s5[] = "";

	ass.t = "test equal 1";
	ass.s1 = Itoa(strncmp(s1, s2, 10) == 0);
	ass.s2 = Itoa(ft_strncmp(s1, s2, 10) == 0);
	ft_assert(ass);

	ass.t = "test equal 2";
	ass.s1 = Itoa(strncmp(s1, s2, 3) == 0);
	ass.s2 = Itoa(ft_strncmp(s1, s2, 3) == 0);
	ft_assert(ass);

	ass.t = "test equal 3";
	ass.s1 = Itoa(strncmp(s4, s5, 0) == 0);
	ass.s2 = Itoa(ft_strncmp(s4, s5, 0) == 0);
	ft_assert(ass);

	ass.t = "test equal 4";
	ass.s1 = Itoa(strncmp(s3, s1, 2) == 0);
	ass.s2 = Itoa(ft_strncmp(s3, s1, 2) == 0);
	ft_assert(ass);

	ass.t = "test equal 5";
	ass.s1 = Itoa(strncmp(s5, s3, 0) == 0);
	ass.s2 = Itoa(ft_strncmp(s5, s3, 0) == 0);
	ft_assert(ass);

	ass.t = "test unequal 1";
	ass.s1 = Itoa(strncmp(s1, s3, 3) < 0);
	ass.s2 = Itoa(ft_strncmp(s1, s3, 3) < 0);
	ft_assert(ass);

	ass.t = "test unequal 2";
	ass.s1 = Itoa(strncmp(s5, s3, 1) < 0);
	ass.s2 = Itoa(ft_strncmp(s5, s3, 1) < 0);
	ft_assert(ass);

	ass.t = "test non_ascii 1";
	ass.s1 = Itoa(strncmp("\200\0", "\200\0", 2) == 0);
	ass.s2 = Itoa(ft_strncmp("\200\0", "\200\0", 2) == 0);
	ft_assert(ass);

	ass.t = "test non_ascii 2";
	ass.s1 = Itoa(strncmp("\200\0", "\0", 2) < 0);
	ass.s2 = Itoa(ft_strncmp("\200\0", "\0", 2) < 0);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_atoi_test()
{
	t_assert ass = (t_assert){"ATOI_TEST", "", "", ""};

	ass.t = "test 0";
	ass.s1 = Itoa(atoi("0"));
	ass.s2 = Itoa(ft_atoi("0"));
	ft_assert(ass);

	ass.t = "test INT_MAX";
	ass.s1 = Itoa(atoi(Itoa(INT_MAX)));
	ass.s2 = Itoa(ft_atoi(Itoa(INT_MAX)));
	ft_assert(ass);

	ass.t = "test INT_MIN";
	ass.s1 = Itoa(atoi(Itoa(INT_MIN)));
	ass.s2 = Itoa(ft_atoi(Itoa(INT_MIN)));
	ft_assert(ass);

	ass.t = "test num";
	ass.s1 = Itoa(atoi(Itoa(-1000001)));
	ass.s2 = Itoa(ft_atoi(Itoa(-1000001)));
	ft_assert(ass);

	ass.t = "test spaces";
	ass.s1 = Itoa(atoi("\t\n\v-1232 666"));
	ass.s2 = Itoa(ft_atoi("\t\n\v-1232 666"));
	ft_assert(ass);

	ass.t = "test signs";
	ass.s1 = Itoa(atoi("--1232 666"));
	ass.s2 = Itoa(ft_atoi("--1232 666"));
	ft_assert(ass);

	ass.t = "test plus";
	ass.s1 = Itoa(atoi("+1"));
	ass.s2 = Itoa(ft_atoi("+1"));
	ft_assert(ass);

	ass.t = "test letters 1";
	ass.s1 = Itoa(atoi("aaaa1"));
	ass.s2 = Itoa(ft_atoi("aaaa1"));
	ft_assert(ass);

	ass.t = "test letters 2";
	ass.s1 = Itoa(atoi("1aaa1"));
	ass.s2 = Itoa(ft_atoi("1aaa1"));
	ft_assert(ass);

	ass.t = "test bell";
	ass.s1 = Itoa(atoi("1\a1"));
	ass.s2 = Itoa(ft_atoi("1\a1"));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_isalpha_test()
{
	t_assert ass = (t_assert){"ISALPHA_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -2000000; i < 2000000; i++)
	{
		if (isalpha(i) != ft_isalpha(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_isdigit_test()
{
	t_assert ass = (t_assert){"ISDIGIT_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -2000000; i < 2000000; i++)
	{
		if (isdigit(i) != ft_isdigit(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_isalnum_test()
{
	t_assert ass = (t_assert){"ISALNUM_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -1000; i < 1000; i++)
	{
		if (isalnum(i) != ft_isalnum(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_isascii_test()
{
	t_assert ass = (t_assert){"ISASCII_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -2000000; i < 2000000; i++)
	{
		if (isascii(i) != ft_isascii(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_isprint_test()
{
	t_assert ass = (t_assert){"ISPRINT_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -2000000; i < 2000000; i++)
	{
		if (isprint(i) != ft_isprint(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_toupper_test()
{
	t_assert ass = (t_assert){"TOUPPER_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -2000000; i < 2000000; i++)
	{
		if (toupper(i) != ft_toupper(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_tolower_test()
{
	t_assert ass = (t_assert){"TOLOWER_TEST", "", "", ""};

	int err_count = 0;

	for(int i = -2000000; i < 2000000; i++)
	{
		if (tolower(i) != ft_tolower(i))
		{
			err_count++;
		}
	}

	ass.t = "test all";
	ass.s1 = Itoa(0);
	ass.s2 = Itoa(err_count);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memalloc_test()
{
	t_assert ass = (t_assert){"MEMALOC_TEST", "", "", ""};
	{
		ass.t = "test NULL";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int)ft_memalloc(-1));
		ft_assert(ass);
	}
	{
		ass.t = "test filling";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa(0);

		char *ptr = (char*)ft_memalloc(1000000);
		for (size_t i = 0; i < 1000000; i++)
		{
			if (ptr[i] != 0)
			{
				ass.s2 = Itoa(ptr[i]);
			}
		}
		ft_assert(ass);
		free(ptr);
	}
	{
		void *ptr = ft_memalloc(10);
		free(ptr);
		if (PRINT_LOGS)
		{
			printf(BOLD "\nMEMALOC_TEST:");
			printf(WHITE "test alloc: ");
			printf(GREEN "OK");
			printf(WHITE);
		}
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_memdel_test()
{
	t_assert ass = (t_assert){"MEMDEL_TEST", "", "", ""};
	{
		if (CHECK_NULL)
		{
			void **ptr = 0;
			ft_memdel(ptr);
			if (PRINT_LOGS)
			{
				printf("\nMEMDEL_TEST:test null **ptr: OK");
			}
			total++;
			success++;
		}
	}
	{
		if (CHECK_NULL)
		{
			void *ptr = 0;
			ft_memdel(&ptr);
			if (PRINT_LOGS)
			{
				printf("\nMEMDEL_TEST:test null *ptr: OK");
			}
			total++;
			success++;
		}
	}
	{
		void *ptr = malloc(1000000);
		if (!ptr)
		{
			printf(BLUE "\n my MALLOC ERROR!!");
			return ;
		}
		if (ptr)
		{
			ft_memdel(&ptr);
			ass.t = "test free and zeroing ptr";
			ass.s1 = Itoa(0);
			ass.s2 = Itoa((int)ptr);
			ft_assert(ass);
		}
		else
		{
			if (PRINT_LOGS)
			{
				printf("MEMDEL_TEST:test free and zeroing ptr:   not alloced");
			}
		}
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strnew_test()
{
	t_assert ass = (t_assert){"STRNEW_TEST", "", "", ""};
	{
		ass.t = "test NULL";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa((int) ft_strnew(-2));
		ft_assert(ass);

	}
	{
		ass.t = "test filling";
		ass.s1 = Itoa(0);
		ass.s2 = Itoa(0);

		char *ptr = ft_strnew(1000000);
		for (size_t i = 0; i < 1000001; i++)
		{
			if (ptr[i] != 0)
			{
				ass.s2 = Itoa(ptr[i]);
			}
		}
		ft_assert(ass);
		free(ptr);
	}
	{
		char *ptr = ft_strnew(1000000);
		free(ptr);
		if (PRINT_LOGS)
		{
			printf(BOLD "\nSTRNEW_TEST:");
			printf(WHITE "test alloc: ");
			printf(GREEN "OK");
			printf(WHITE);
		}
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strdel_test()
{
	t_assert ass = (t_assert){"STRDEL_TEST", "", "", ""};
	{
		if (CHECK_NULL)
		{
			char **ptr = 0;
			ft_strdel(ptr);
			if (PRINT_LOGS)
			{
				printf("\nSTRDEL_TEST:test null **ptr: OK");
			}
			total++;
			success++;
		}
	}
	{
		if (CHECK_NULL)
		{
			char *ptr = 0;
			ft_strdel(&ptr);
			if (PRINT_LOGS)
			{
				printf("\nSTRDEL_TEST:test null *ptr: OK");
			}
			total++;
			success++;
		}
	}
	{
		char *ptr = malloc(1000000);
		if (ptr)
		{
			ft_strdel(&ptr);
			ass.t = "test free and zeroing ptr";
			ass.s1 = Itoa(0);
			ass.s2 = Itoa((int)ptr);
			ft_assert(ass);
		}
		else
		{
			if (PRINT_LOGS)
			{
				printf("STRDEL_TEST:test free and zeroing ptr:   not alloced");
			}
		}
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strclr_test()
{
	t_assert ass = (t_assert){"STRCLR_TEST", "", "", ""};

	char str_full[] = "HELLO_world";
	char str_empty[] = "";
	char *null = 0;

	if (CHECK_NULL)
	{
		ft_strclr(null);
		if (PRINT_LOGS) {
			printf("\nSTRCLR_TEST:test null: OK");
		}
		total++;
		success++;
	}

	ass.t = "test empty";
	ass.s1 = "0";
	ft_strclr(str_empty);
	ass.s2 = str_to_code_sentence(str_empty, 1);
	ft_assert(ass);

	ass.t = "test full";
	ass.s1 = "000000000000";
	ft_strclr(str_full);
	ass.s2 = str_to_code_sentence(str_full, 12);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void f1(char *c)
{
	*c = 'A';
}

void f2(unsigned int i, char *c)
{
	*c = i;
}

char f3(char c)
{
	c++;
	return 'A';
}

char f4(unsigned int i, char c)
{
	c++;
	return ((char)i);
}

void ft_striter_test()
{
	t_assert ass = (t_assert){"STRITER_TEST", "", "", ""};

	char str_full[] = "HELLO_world";
	char str_empty[] = "";
	char *null = 0;

	if (CHECK_NULL)
	{
		ft_striter(null, f1);
		if (PRINT_LOGS) {
			printf("\nSTRITER_TEST:test null: OK");
		}
		total++;
		success++;
	}

	ass.t = "test empty";
	ass.s1 = "0";
	ft_striter(str_empty, f1);
	ass.s2 = str_to_code_sentence(str_empty, 1);
	ft_assert(ass);

	ass.t = "test full";
	ass.s1 = "65656565656565656565650";
	ft_striter(str_full, f1);
	ass.s2 = str_to_code_sentence(str_full, 12);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_striteri_test()
{
	t_assert ass = (t_assert){"STRITERI_TEST", "", "", ""};

	char str_full[] = "HELLO_world";
	char str_empty[] = "";
	char *null = 0;

	if (CHECK_NULL)
	{
		ft_striteri(null, f2);
		if (PRINT_LOGS) {
			printf("\nSTRITERI_TEST:test null: OK");
		}
		total++;
		success++;
	}

	ass.t = "test empty";
	ass.s1 = "0";
	ft_striteri(str_empty, f2);
	ass.s2 = str_to_code_sentence(str_empty, 1);
	ft_assert(ass);

	ass.t = "test full";
	ass.s1 = "0123456789100";
	ft_striteri(str_full, f2);
	ass.s2 = str_to_code_sentence(str_full, 12);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strmap_test()
{
	t_assert ass = (t_assert){"STRMAP_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;
	char *str;

	if (CHECK_NULL)
	{
		str = ft_strmap(null, f3);
		if (PRINT_LOGS) {
			printf("\nSTRMAP_TEST:test null: OK");
		}
		total++;
		success++;
	}

	ass.t = "test empty";
	ass.s1 = "0";
	str = ft_strmap(str_empty, f3);
	ass.s2 = str_to_code_sentence(str, 1);
	ft_assert(ass);

	ass.t = "test full";
	ass.s1 = "65656565656565656565650";
	str = ft_strmap(str_full, f3);
	ass.s2 = str_to_code_sentence(str, 12);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strmapi_test()
{
	t_assert ass = (t_assert){"STRMAPI_TEST", "", "", ""};

	const char str_full[] = "HELLO_world";
	const char str_empty[] = "";
	const char *null = 0;
	char *str;

	if (CHECK_NULL)
	{
		str = ft_strmap(null, f3);
		if (PRINT_LOGS) {
			printf("\nSTRMAPI_TEST:test null: OK");
		}
		total++;
		success++;
	}

	ass.t = "test empty";
	ass.s1 = "0";
	str = ft_strmapi(str_empty, f4);
	ass.s2 = str_to_code_sentence(str, 1);
	ft_assert(ass);

	ass.t = "test full";
	ass.s1 = "0123456789100";
	str = ft_strmapi(str_full, f4);
	ass.s2 = str_to_code_sentence(str, 12);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strequ_test()
{
	t_assert ass = (t_assert){"STREQU_TEST", "", "", ""};

	const char s1[] = "aaa";
	const char s2[] = "aaa";
	const char s3[] = "aab";
	const char s4[] = "";
	const char s5[] = "";

	ass.t = "test equal 1";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strequ(s1, s2));
	ft_assert(ass);

	ass.t = "test equal 2";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strequ(s4, s5));
	ft_assert(ass);

	ass.t = "test unequal 1";
	ass.s1 = "0";
	ass.s2 = Itoa(ft_strequ(s1, s3));
	ft_assert(ass);

	ass.t = "test unequal 2";
	ass.s1 = "0";
	ass.s2 = Itoa(ft_strequ(s5, s3));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strnequ_test()
{
	t_assert ass = (t_assert){"STRNEQU_TEST", "", "", ""};

	const char s1[] = "aaa";
	const char s2[] = "aaa";
	const char s3[] = "aab";
	const char s4[] = "";
	const char s5[] = "";

	ass.t = "test equal 1";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strnequ(s1, s2, 10));
	ft_assert(ass);

	ass.t = "test equal 2";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strnequ(s1, s2, 3));
	ft_assert(ass);

	ass.t = "test equal 3";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strnequ(s4, s5, 0));
	ft_assert(ass);

	ass.t = "test equal 4";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strnequ(s3, s1, 2));
	ft_assert(ass);

	ass.t = "test equal 5";
	ass.s1 = "1";
	ass.s2 = Itoa(ft_strnequ(s5, s3, 0));
	ft_assert(ass);

	ass.t = "test unequal 1";
	ass.s1 = "0";
	ass.s2 = Itoa(ft_strnequ(s1, s3, 3));
	ft_assert(ass);

	ass.t = "test unequal 2";
	ass.s1 = "0";
	ass.s2 = Itoa(ft_strnequ(s5, s3, 1));
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strsub_test()
{
	t_assert ass = (t_assert){"STRSUB_TEST", "", "", ""};

	const char str1[] = "0123456789ABCDEFGH";
	char *res;

	ass.t = "test normal";
	ass.s1 = "3456789ABC";
	res = ft_strsub(str1, 3, 10);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test 1 char";
	ass.s1 = "0";
	res = ft_strsub(str1, 0, 1);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test extreme";
	ass.s1 = "0123456789ABCDEFGH";
	res = ft_strsub(str1, 0, 19);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test zero len";
	ass.s1 = "";
	res = ft_strsub(str1, 5, 0);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test null_terminator sub";
	ass.s1 = "";
	res = ft_strsub(str1, 18, 1);
	ass.s2 = res;
	ft_assert(ass);

	const char str2[] = "";

	ass.t = "test empty source from 0";
	ass.s1 = "";
	res = ft_strsub(str2, 0, 0);
	ass.s2 = res;
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_strjoin_test()
{
	t_assert ass = (t_assert){"STRJOIN_TEST", "", "", ""};

	const char s1[] = "12345";
	const char s2[] = "abc";
	const char s3[] = "";
	const char s4[] = "";
	char *res;

	ass.t = "test norm + norm";
	ass.s1 = "12345abc";
	res = ft_strjoin(s1, s2);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test norm + empty";
	ass.s1 = "12345";
	res = ft_strjoin(s1, s3);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test empty + norm";
	ass.s1 = "abc";
	res = ft_strjoin(s4, s2);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test empty + empty";
	ass.s1 = "";
	res = ft_strjoin(s4, s3);
	ass.s2 = res;
	ft_assert(ass);

	printf("\n");
}

void ft_strtrim_test()
{
	t_assert ass = (t_assert){"STRTRIM_TEST", "", "", ""};

	const char s1[] = "     012345\t\t\t";
	const char s2[] = "abc    ";
	const char s3[] = "       abc";
	const char s4[] = "           ";
	const char s5[] = "0123456789";
	const char s6[] = "";
	const char s7[] = "   gg   gg   ";
	const char s8[] = "vvvvvvgg   ggvvvvvvvvv";

	char *res;

	ass.t = "test both sides";
	ass.s1 = "012345";
	res = ft_strtrim(s1);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test right side";
	ass.s1 = "abc";
	res = ft_strtrim(s2);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test left side";
	ass.s1 = "abc";
	res = ft_strtrim(s3);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test all spaces";
	ass.s1 = "";
	res = ft_strtrim(s4);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test no spaces";
	ass.s1 = "0123456789";
	res = ft_strtrim(s5);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test empty";
	ass.s1 = "";
	res = ft_strtrim(s6);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test mid spaces";
	ass.s1 = "gg   gg";
	res = ft_strtrim(s7);
	ass.s2 = res;
	ft_assert(ass);

	ass.t = "test mid spaces 2";
	ass.s1 = "vvvvvvgg   ggvvvvvvvvv";
	res = ft_strtrim(s8);
	ass.s2 = res;
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

char *words_table_to_str(char **tab)
{
	int i;
	char *res = (char*)malloc(2048);
	if (!res)
	{
		printf("\n ALLOC ERR");
		return (0);
	}
	res[0] = 0;

	i = 0;
	if (!tab)
		return res;
	while (tab[i])
	{
		strlcat(res, "<", 2048);
		strlcat(res, tab[i++], 2048);
		strlcat(res, "> ", 2048);
	}
	return res;
}

void ft_strsplit_test()
{
	t_assert ass = (t_assert){"STRSPLIT_TEST", "", "", ""};

	const char s1[] = "||||||aaa||||ggg||||ttt|4|s|r|tewggegege||||||";
	const char s2[] = "01234567890";
	const char s3[] = "|||||||||||||||";
	const char s4[] = "";
	const char s5[] = "aaa|||vvv|||eee|||t|r|yyyy";
	char *res;

	ass.t = "test norm";
	ass.s1 = "<aaa> <ggg> <ttt> <4> <s> <r> <tewggegege> ";
	res = words_table_to_str(ft_strsplit(s1, '|'));
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	ass.t = "test 2x6";
	ass.s1 = "<aaa> <vvv> <eee> <t> <r> <yyyy> ";
	res = words_table_to_str(ft_strsplit(s5, '|'));
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	ass.t = "test no spaces";
	ass.s1 = "<01234567890> ";
	res = words_table_to_str(ft_strsplit(s2, '|'));
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	ass.t = "test only spaces";
	ass.s1 = "";
	res = words_table_to_str(ft_strsplit(s3, '|'));
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	ass.t = "test empty";
	ass.s1 = "";
	res = words_table_to_str(ft_strsplit(s4, '|'));
	ass.s2 = res;
	ft_assert(ass);
	free(res);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_itoa_test()
{
	t_assert ass = (t_assert){"ITOA_TEST", "", "", ""};

	ass.t = "test INT_MIN";
	ass.s1 = "-2147483648";
	ass.s2 = ft_itoa(INT_MIN);
	ft_assert(ass);

	ass.t = "test ZERO";
	ass.s1 = "0";
	ass.s2 = ft_itoa(0);
	ft_assert(ass);

	ass.t = "test INT_MAX";
	ass.s1 = "2147483647";
	ass.s2 = ft_itoa(INT_MAX);
	ft_assert(ass);

	ass.t = "test num1";
	ass.s1 = "-100000001";
	ass.s2 = ft_itoa(-100000001);
	ft_assert(ass);

	ass.t = "test num2";
	ass.s1 = "1";
	ass.s2 = ft_itoa(1);
	ft_assert(ass);

	ass.t = "test num3";
	ass.s1 = "-45";
	ass.s2 = ft_itoa(-45);
	ft_assert(ass);

	ass.t = "test num4";
	ass.s1 = "-1";
	ass.s2 = ft_itoa(-1);
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putchar_test()
{
	t_assert ass = (t_assert){"PUTCHAR_TEST", "", "", ""};

	char buffer[100 + 1] = {0};
	int out_pipe[2];
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if( pipe(out_pipe) != 0 ) {
		exit(1);
	}
	dup2(out_pipe[1], STDOUT_FILENO);
	close(out_pipe[1]);

	ft_putchar('A');

	fflush(stdout);
	read(out_pipe[0], buffer, 100);
	dup2(saved_stdout, STDOUT_FILENO);

	ass.t = "test put 'A'";
	ass.s1 = "A";
	ass.s2 = (char*)buffer;
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putstr_test()
{
	t_assert ass = (t_assert){"PUTSTR_TEST", "", "", ""};


	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putstr("KO");

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test str 'KO'";
		ass.s1 = "KO";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putstr("1234567890qwertyuiopasdfghjkl;");

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test long str";
		ass.s1 = "1234567890qwertyuiopasdfghjkl;";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putstr("");

		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		read(out_pipe[0], buffer, 100);

		ass.t = "test empty str";
		ass.s1 = "";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putstr("A");

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test str 'A'";
		ass.s1 = "A";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putendl_test()
{
	t_assert ass = (t_assert){"PUTENDL_TEST", "", "", ""};

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putendl("KO");

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test str 'KO'";
		ass.s1 = "KO\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putendl("1234567890qwertyuiopasdfghjkl;");

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test long str";
		ass.s1 = "1234567890qwertyuiopasdfghjkl;\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putendl("");

		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		read(out_pipe[0], buffer, 100);

		ass.t = "test empty str";
		ass.s1 = "\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putendl("A");

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test str 'A'";
		ass.s1 = "A\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putnbr_test()
{
	t_assert ass = (t_assert){"PUTNBR_TEST", "", "", ""};

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putnbr(INT_MIN);

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test INT_MIN";
		ass.s1 = Itoa(INT_MIN);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putnbr(0);

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test ZERO";
		ass.s1 = Itoa(0);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putnbr(INT_MAX);

		fflush(stdout);
		dup2(saved_stdout, STDOUT_FILENO);
		read(out_pipe[0], buffer, 100);

		ass.t = "test INT_MAX";
		ass.s1 = Itoa(INT_MAX);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDOUT_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDOUT_FILENO);
		close(out_pipe[1]);

		ft_putnbr(-10000001);

		fflush(stdout);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDOUT_FILENO);

		ass.t = "test -10000001";
		ass.s1 = Itoa(-10000001);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putchar_fd_test()
{
	t_assert ass = (t_assert){"PUTCHAR_FD_TEST", "", "", ""};

	char buffer[100 + 1] = {0};
	int out_pipe[2];
	int saved_stdout;

	saved_stdout = dup(STDERR_FILENO);
	if( pipe(out_pipe) != 0 ) {
		exit(1);
	}
	dup2(out_pipe[1], STDERR_FILENO);
	close(out_pipe[1]);

	ft_putchar_fd('A', 2);

	fflush(stderr);
	read(out_pipe[0], buffer, 100);
	dup2(saved_stdout, STDERR_FILENO);

	ass.t = "test put 'A'";
	ass.s1 = "A";
	ass.s2 = (char*)buffer;
	ft_assert(ass);

	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putstr_fd_test()
{
	t_assert ass = (t_assert){"PUTSTR_FD_TEST", "", "", ""};


	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putstr_fd("KO", 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test str 'KO'";
		ass.s1 = "KO";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putstr_fd("1234567890qwertyuiopasdfghjkl;", 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test long str";
		ass.s1 = "1234567890qwertyuiopasdfghjkl;";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putstr_fd("", 2);

		fflush(stderr);
		dup2(saved_stdout, STDERR_FILENO);
		read(out_pipe[0], buffer, 100);

		ass.t = "test empty str";
		ass.s1 = "";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putstr_fd("A", 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test str 'A'";
		ass.s1 = "A";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putendl_fd_test()
{
	t_assert ass = (t_assert){"PUTENDL_FD_TEST", "", "", ""};

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putendl_fd("KO", 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test str 'KO'";
		ass.s1 = "KO\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putendl_fd("1234567890qwertyuiopasdfghjkl;", 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test long str";
		ass.s1 = "1234567890qwertyuiopasdfghjkl;\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putendl_fd("", 2);

		fflush(stderr);
		dup2(saved_stdout, STDERR_FILENO);
		read(out_pipe[0], buffer, 100);

		ass.t = "test empty str";
		ass.s1 = "\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putendl_fd("A", 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test str 'A'";
		ass.s1 = "A\n";
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

void ft_putnbr_fd_test()
{
	t_assert ass = (t_assert){"PUTNBR_FD_TEST", "", "", ""};

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putnbr_fd(INT_MIN, 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test INT_MIN";
		ass.s1 = Itoa(INT_MIN);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putnbr_fd(0, 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test ZERO";
		ass.s1 = Itoa(0);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putnbr_fd(INT_MAX, 2);

		fflush(stderr);
		dup2(saved_stdout, STDERR_FILENO);
		read(out_pipe[0], buffer, 100);

		ass.t = "test INT_MAX";
		ass.s1 = Itoa(INT_MAX);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}

	{
		char buffer[100 + 1] = {0};
		int out_pipe[2];
		int saved_stdout;

		saved_stdout = dup(STDERR_FILENO);
		if( pipe(out_pipe) != 0 ) {
			exit(1);
		}
		dup2(out_pipe[1], STDERR_FILENO);
		close(out_pipe[1]);

		ft_putnbr_fd(-10000001, 2);

		fflush(stderr);
		read(out_pipe[0], buffer, 100);
		dup2(saved_stdout, STDERR_FILENO);

		ass.t = "test -10000001";
		ass.s1 = Itoa(-10000001);
		ass.s2 = (char*)buffer;
		ft_assert(ass);
	}
	if (PRINT_LOGS) {
		printf("\n");
	}
}

int test_all()
{
	total = 0;
	success = 0;

	if (PRINT_LOGS)
	{
		printf(BLUE "\n\n      *** BEGIN ***\n\n");
		printf(WHITE "");
	}

	ft_memset_test();
	ft_bzero_test();
	ft_memcpy_test();
	ft_memccpy_test();
	ft_memmove_test();
	ft_memchr_test();
	ft_memcmp_test();
	ft_strlen_test();
	ft_strdup_test();
	ft_strcpy_test();
	ft_strncpy_test();
	/*ft_strlcpy_test();*/
	ft_strcat_test();
	ft_strncat_test();
	ft_strlcat_test();
	ft_strchr_test();
	ft_strrchr_test();
	ft_strstr_test();
	ft_strnstr_test();
	ft_strcmp_test();
	ft_strncmp_test();
	ft_atoi_test();
	ft_isalpha_test();
	ft_isdigit_test();
	ft_isalnum_test();
	ft_isascii_test();
	ft_isprint_test();
	ft_toupper_test();
	ft_tolower_test();

	ft_memalloc_test();
	ft_memdel_test();
	ft_strnew_test();
	ft_strdel_test();
	ft_strclr_test();
	ft_striter_test();
	ft_striteri_test();
	ft_strmap_test();
	ft_strmapi_test();
	ft_strequ_test();
	ft_strnequ_test();
	ft_strsub_test();
	ft_strjoin_test();
	ft_strtrim_test();
	ft_strsplit_test();
	ft_itoa_test();
	ft_putchar_test();
	ft_putstr_test();
	ft_putendl_test();
	ft_putnbr_test();
	ft_putchar_fd_test();
	ft_putstr_fd_test();
	ft_putendl_fd_test();
	ft_putnbr_fd_test();

	print_total();
	return (total == success);
}

#include <limits.h>

int main() {

	test_all();

	return (0);
}
