#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int linii;	 //nr de linii
	int coloane; //nr de coloane
	int **a;	 //matricea
} matrix;

typedef struct {
	int N;		  //nr de elemente din vector
	int cap;	  //capacitatea
	matrix *d; //vectorul in care se retin matrici

} arraylist;

void add(arraylist *array, matrix element)
{
	if (array->N == array->cap) {
		int new_cap = array->cap + 1;
		array->d = realloc(array->d, new_cap * sizeof(matrix));
		array->cap = new_cap;
	}
	array->d[array->N] = element;
	array->N++;
}

matrix *al_mat(int m, int n)
{
	int **d;
	matrix *mat = malloc(sizeof(matrix));
	d = malloc(m * sizeof(int *));
	for (int i = 0; i < m; i++) {
		d[i] = (int *)malloc(n * sizeof(int));
		if (!d[i]) {
			fprintf(stderr, "malloc() failed\n");
			while (--i >= 0)
				free(d[i]);
			free(d[i]);
			return NULL;
		}
	for (int j = 0 ; j < n; j++)
		d[i][j] = 0;
	}
	mat->linii = m;
	mat->coloane = n;
	mat->a = d;

	return mat;
}

matrix *realloc_mem(matrix *d, int capacity)
{
	matrix *aux;
	aux = realloc(d, capacity * sizeof(matrix));

	return aux;
}

void free_matrix(matrix mat)
{
	for (int i = 0; i < mat.linii; i++)
		free(mat.a[i]);
	free(mat.a);
}

matrix *read_matrix(int m, int n)
{
	matrix *mat = al_mat(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%d ", &mat->a[i][j]);

	return mat;
}

void d_matrix (arraylist *array)
{
	int index_d; //indexul matricei pt care se doreste det dimensiunii
	scanf("%d", &index_d);
	if (index_d > array->N) {
		printf("No matrix with the given index\n");
	} else {
		printf("%d ", array->d[index_d].linii);
		printf("%d\n", array->d[index_d].coloane);
	}
}

void t_matrix (arraylist *array)
{
	int index_t, **aux;//indexul matricei pt care se doreste det
	scanf("%d", &index_t);
	if (index_t > array->N) {
		printf("No matrix with the given index\n");
	} else {
		aux = malloc(array->d[index_t].coloane * sizeof(int **));
		for (int i = 0; i < array->d[index_t].coloane; i++)
			aux[i] = malloc(array->d[index_t].linii * sizeof(int *));
		for (int i = 0; i < array->d[index_t].linii; i++) {
			for (int j = 0; j < array->d[index_t].coloane; j++)
				aux[j][i] = array->d[index_t].a[i][j];
		}
		int tmp;
		free_matrix(array->d[index_t]);
		tmp = array->d[index_t].linii;
		array->d[index_t].linii = array->d[index_t].coloane;
		array->d[index_t].coloane = tmp;
		array->d[index_t].a = aux;
	}
}

int sum_matrix(matrix mat)
{
	int sum = 0;

	for (int i = 0; i < mat.linii; i++) {
		for (int j = 0; j < mat.coloane; j++) {
			sum = (sum + mat.a[i][j]) % 10007;
			if (sum < 0)
				sum += 10007;
		}
	}

	return sum;
}

void p_matrix (arraylist array)
{
	int index_p; //indexul matricei pt care se doreste det dimensiunii
	scanf("%d", &index_p);
	if (index_p >= array.N || index_p < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (int i = 0; i < array.d[index_p].linii; i++) {
			for (int j = 0; j < array.d[index_p].coloane; j++)
				printf("%d ", array.d[index_p].a[i][j]);
			printf("\n");
		}
	}
	// printf("sum = %d\n", sum_matrix(array.d[index_p]));
}

arraylist *m_matrix (arraylist *arr)
{
	int s, **aux, i1, i2;
	scanf("%d %d", &i1, &i2);
	if ((i1 >= arr->N || i2 >= arr->N) || (i1 < 0 || i2 < 0)) {
		printf("No matrix with the given index\n");
	return NULL;
	} else {
		if (arr->d[i1].coloane != arr->d[i2].linii) {
			printf("Cannot perform matrix multiplication\n");
	return NULL;
	} else {
		matrix *t = al_mat(arr->d[i1].linii, arr->d[i2].coloane);
		aux = t->a;
		for (int i = 0; i < arr->d[i1].linii; i++)
			for (int j = 0; j < arr->d[i2].coloane; j++) {
				aux[i][j] = 0;
				s = 0;
				for (int k = 0; k < arr->d[i1].coloane; k++) {
					s = (s + arr->d[i1].a[i][k] * arr->d[i2].a[k][j]) % 10007;
					if (s < 0)
						s = s + 10007;
				}
				aux[i][j] = s;
			}
		add(arr, *t);
		free(t);
		return arr;
		}
	}
}

void q_matrix (arraylist array)
{
	for (int i = 0; i < array.N; i++) {
		for (int j = 0; j < array.d[i].linii; j++)
			free(array.d[i].a[j]);
		free(array.d[i].a);
	}
	free(array.d);
}

void f_matrix(arraylist *array)
{
	int index_mat; //indexul matricei pe care vrem sa o stergem
	scanf("%d", &index_mat);
	if (index_mat >= array->N || index_mat < 0) {
		printf("No matrix with the given index\n");
	} else {
		//MAI TREBUIE SA ELIBEREZ PENTRU TOATA MATRICEA
		matrix aux = array->d[index_mat];
		for (int i = index_mat; i < array->N - 1; i++)
			array->d[i] = array->d[i + 1];
		array->N--;
		free_matrix(aux);
	}
}

void c_matrix(arraylist *array)
{
	int index_c; //indexul matricei pt care se doreste a fi redimensionata
	int nr_lines, nr_cols, *lines = NULL, *cols = NULL;
	scanf("%d", &index_c);
	if (index_c >= array->N || index_c < 0) {
		printf("No matrix with the given index\n");
		scanf("%d", &nr_lines);
		int c;
		for (int i = 0; i < nr_lines; i++)
			scanf("%d", &c);
		scanf("%d", &nr_cols);
		for (int i = 0; i < nr_cols; i++)
			scanf("%d", &c);
	} else {
		scanf("%d", &nr_lines);
		lines = (int *)malloc(nr_lines * sizeof(int));
		if (!lines) {
			free(lines); return;
			}
		for (int i = 0; i < nr_lines; i++)
			scanf("%d", &lines[i]);
		scanf("%d", &nr_cols);
		cols = (int *)malloc(nr_cols * sizeof(int));
		if (!cols) {
			free(lines); free(cols); return;
			}
		for (int i = 0; i < nr_cols; i++)
			scanf("%d", &cols[i]);
		// alocam dinamic memorie pentru o noua matrice care va fi
		// rezultatul redimensionarii
		matrix *new_mat = al_mat(nr_lines, nr_cols);
		matrix src = array->d[index_c];
		for (int i = 0; i < nr_lines; i++) {
			for (int j = 0; j < nr_cols; j++) {
				(new_mat->a)[i][j]
				=
				src.a[lines[i]][cols[j]];
			}
		}
		new_mat->coloane = nr_cols;
		new_mat->linii = nr_lines;
		free_matrix(array->d[index_c]);
		array->d[index_c] = *new_mat;
		free(new_mat);
		free(lines);
		free(cols);
	}
}

void o_matrix(arraylist *array)
{
	matrix aux;
	for (int i = 0; i < array->N - 1; i++) {
		for (int j = i + 1; j < array->N; j++) {
			if (sum_matrix(array->d[i]) > sum_matrix(array->d[j])) {
				aux = array->d[i];
				array->d[i] = array->d[j];
				array->d[j] = aux;
			}
		}
	}
}

int main(void)
{
	char c;
	int m, n;
	arraylist array;
	array.N = 0;
	array.cap = 2;
	array.d = malloc(array.cap * sizeof(matrix));
	if (!array.d) {
		fprintf(stderr, "malloc failed\n");
		return -1;
	}
	scanf("%c", &c);
	do {
		if (!strchr("LDPCOTMFQ\n", c))
			printf("Unrecognized command\n");
		if (c == 'L') {
			scanf("%d %d", &m, &n);
			matrix *mat = read_matrix(m, n);
			add(&array, *mat);
			free(mat);
		} else if (c == 'D') {
			d_matrix(&array);
		} else if (c == 'T') {
			t_matrix(&array);
		} else if (c == 'P') {
			p_matrix(array);
		} else if (c == 'M') {
			m_matrix(&array);
		} else if (c == 'F') {
			f_matrix(&array);
		} else if (c == 'C') {
			c_matrix(&array);
		} else if (c == 'O') {
			o_matrix(&array);
		}
		scanf("%c", &c);
	} while (c != 'Q');
	q_matrix(array);

	return 0;
}
