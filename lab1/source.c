#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX(a, b)				(((a) > (b)) ? a : b)
#define NAME_BUF				256
#define FGETC_BUF				2

static const char beware[] =	"---\nMax sumbols for the first name \
or the last name is 254\n---\n";
static const char etfn[] =		"Enter the first name: ";
static const char etln[] =		"Enter the last name: ";
static const char menu[] =		"----------\nChoise:\n1 - (A) ^ (B)\
\n2 - (A) U (B)\n3 - (A) \\ (B)\
\n4 - Universum\n5 - A\
\n6 - B\n7 - Vectors of the Universum,A,B\n8 - print menu\n0 - exit\n\n";

static char	tfn[NAME_BUF];
static char tln[NAME_BUF];
static char c[FGETC_BUF];

static void printf_u (const char *u)
{
	if (!u) return;
	uint8_t i = 0;
	printf("{ ");
	for (; u[i];) {
		printf("%c ", u[i++]);
	}
	printf("}");
}

static char *get_universum_of_tfntln (const char *a, const char *b)
{
	if (!*a && !*b) return NULL;
	uint8_t i, j;
	uint16_t u;
	u = i = j = 0;
	char* U = (char*)malloc(sizeof(char) * (strlen(a) + strlen(b) + 1));
	if (!U) return NULL;
	for (;a[i] || b[j];) {
		if (a[i] && b[j]) {
			if (a[i] == b[j]) {
				*(U + u++) = a[i++];
				j++;
			} else
				a[i] > b[j] ? (*(U + u) = b[j], u++, j++) : (*(U + u) = a[i], u++, i++);
		}
		else if (a[i] && !b[j])
			for (; a[i];)
				*(U + u++) = a[i++];
		else if (!a[i] && b[j])
			for (; b[j];)
				*(U + u++) = b[j++];
	}
	*(U + u) = 0;
	return U;
}

static void get_and_of_tfntln (const char *a, const char *b)
{
	if (!*a && !*b) return;
	uint8_t i, j;
	i = j = 0;
	printf("(A) ^ (B) = { ");
	for (;a[i] && b[j];) {
		if (a[i] == b[j]) {
			printf("%c ", a[i++]);
			j++;
		} else
			a[i] > b[j] ? j++ : i++;
	}
	printf("}\n");
}

static void get_minus_of_tfntln (const char *a, const char *b)
{
	if (!*a) return;
	uint8_t i, j, m;
	m = i = j = 0;
	char *minus = (char*)malloc(sizeof(char) * (strlen(a) + 1));
	if (!minus) return;
	for (; a[i];) {
		if (b[j]) {
			if (a[i] == b[j]) {
				i++; j++;
			} else {
				while (b[j] && b[j] < a[i]) j++;
				if (b[j] > a[i]) *(minus + m++) = a[i++];
			}
		} else
			for (; a[i];)
				*(minus + m++) = a[i++];
	}
	*(minus + m) = 0;
	printf("(A) \\ (B) = { ");
	for (m = 0; *(minus + m);)
		printf("%c ", *(minus + m++));
	printf("}\n");
	free(minus);
}

static void get_vectors_of_tfntln (const char *u, const char *a, const char *b)
{
	if (!*u) return;
	uint8_t i, n;
	i = n = 0;
	printf("(U) = ");
	printf_u(u);
	fputc('\n', stdout);
	printf("(A) = ( ");
	for (; u[n];) {
		if (a[i]) {
			if (a[i] == u[n]) {
				printf("1 ");
				i++; n++;
			} else {
				while (a[i] && a[i] > u[n]) {
					printf("0 ");
					n++;
				}
			}
		} else {
			for (; u[n]; n++)
				printf("0 ");
		}
	}
	printf(")\n");
	printf("(B) = ( ");
	for (i = n = 0; u[n];) {
		if (b[i]) {
			if (b[i] == u[n]) {
				printf("1 ");
				i++; n++;
			} else {
				while (b[i] && b[i] > u[n]) {
					printf("0 ");
					n++;
				}
			}
		} else {
			for (; u[n]; n++)
				printf("0 ");
		}
	}
	printf(")\n");
}

int main()
{
	printf(beware);
	// input
	uint8_t i = 0;
	printf(etfn);
	while ((*c = fgetc(stdin)) != '\n') {
		if (!strstr(tfn, (const char*)c))
			tfn[i++] = *c;
		if (i == 255) break;
	}
	qsort(tfn, i, sizeof(char), (int (*)(const void*, const void*)) strcmp);
	*c = i = 0;
	printf(etln);
	while ((*c = fgetc(stdin)) != '\n')
		if (!strstr(tln, (const char*)c)) {
			tln[i++] = *c;
		if (i == 255) break;
	}
	qsort(tln, i, sizeof(char), (int (*)(const void*, const void*)) strcmp);
	char *U = get_universum_of_tfntln((const char*)tfn, (const char*)tln);
	if (!U) {
		U = (char*)malloc(sizeof(char) * 2);
		if (U) {
			U[0] = ' ';
			U[1] = 0;
		} else {
			perror("U");
			exit(1);
		}
	}

	//output A and B then Menu
	printf("----------\nA = ");
	printf_u((const char*)tfn);
	printf("\nB = ");
	printf_u((const char*)tln);
	fputc(0xa, stdout);
	printf(menu);
	for (char c_menu = 0; (c_menu = fgetc(stdin));) {
		switch (c_menu) {
			case '1':
				get_and_of_tfntln((const char*)tfn, (const char*)tln);
				break;
			case '2':
				printf("(A) U (B) = ");
				printf_u((const char*)U);
				fputc(0xa, stdout);
				break;
			case '3':
				get_minus_of_tfntln((const char*)tfn, (const char*)tln);
				break;
			case '4':
				printf("(U) = ");
				printf_u((const char*)U);
				fputc(0xa, stdout);
				break;
			case '5':
				printf("(A) = ");
				printf_u((const char*)tfn);
				fputc(0xa, stdout);
				break;
			case '6':
				printf("(B) = ");
				printf_u((const char*)tln);
				fputc(0xa, stdout);
				break;
			case '7':
				get_vectors_of_tfntln((const char*)U, (const char*)tfn, (const char*)tln);
				break;
			case '8':
				printf(menu);
				break;
			case '0':
				break;

			default: break;
		}
		if (c_menu == '0') break;
	}
	if (U)
		free(U);
	return 0;
}
