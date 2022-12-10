#include "../../../include.h"

int main()
{
	int n;
	size_t i, j;
	char **c;
	char C;
	i = j = 0;
	scanf("%d", &n);
	c = (char**)malloc(sizeof(char*) * n);
	for (; i < n; i++) {
		c[i] = (char*)malloc(n);
		for (j = 0; j < n;) {
			C = fgetc(stdin);
			if (C == '1' || C == '0')
				c[i][j++] = C;
		}
	}
	printf("%d\n", n - 1);
	for (i = 0; i < n; i++) {
		int h = 0;
		for (j = 0; j < n; j++)
			if (c[i][j] == '1')
				h++;
		if (i < n - 1)
			printf("%d ", h);
		if (i == n - 1)
			printf("%d\n", h);
	}
	return 0;
}
