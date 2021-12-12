#include "backsubst.h"
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	int n = sizeof(b)/sizeof(b[0])
	int m = sizeof(x)/sizeof(x[0])
	int h = sizeof(mat)/sizeof(mat[0])
	if (n != m || m != h*h || n != h*h)
		return 2;
 	for( int w= n-1; w >= 0; w-- ) {
		double s = 0;
		for( int k= w+1; k < n; k++ )
			s += mat[w*n+k]*x[k];
		if( mat[w*n+w] == 0)
			return 1;
		x[w] = ( b[w] - s ) / mat[w*n+w];
	}
	return 0;
}
