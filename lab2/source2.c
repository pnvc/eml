#include "../../../include.h"

int main()
{
	char w[] = "----------\n";
	int n, m;
	scanf("%d%d", &n, &m);
	char **c = (char**)malloc(sizeof(char*)*n);
	char C;
	int i, j;
	for (i = 0; i < n; i++) {
		c[i] = (char*)malloc(m);
		for (j = 0; j < m;) {
			C = fgetc(stdin);
			if (C == '1' || C == '0')
				c[i][j++] = C;
		}
	}
	char **s = (char**)malloc(sizeof(char*) * n);
	for (i = 0; i < n; i++) {
		s[i] = (char*)malloc(n);
		memset(s[i], '0', n);
	}
	for (i = 0; i < n; i++) {
		int y;
		for (y = j = 0; j < m; j++, y++) {
			if (y == i) y++;
			if (c[i][j] == '1')
				s[i][y] = '1';
		}
	}  
	write(1, (const char*)w, sizeof(w));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%c ", s[i][j]);
		}
		putchar('\n');
	}
	for (i = 0; i < n; i++) {
		free(c[i]);
		free(s[i]);
	}
	free(c);
	free(s);
	return 0;
}
