double *solve( ur_t ur ) {
	int n = ur->n;
	if( n <= 0 )
		return NULL;
	double *x = malloc( n * sizeof *x );
	// Przekształcam u tak, aby A stała się macierzą górną trójkątną
	double *A = ur->a;
	double *b = ur->b;
	for( int k= 0; k < n-1; k++ ) {
		for( int w= k+1; w < n; w++ ) {
			double q = A[w*n+k] / A[k*n+k];     // A[i*n+j] to A(i,j)
			for( int i= k; i < n; i++ )
				A[w*n+i] -= q * A[k*n+i];
			b[w] -= q*b[k] ;
		}
	}
	for( int w= n-1; w >= 0; w-- ) {
		double s = 0;
		for( int k= w+1; k < n; k++ )
			s += A[w*n+k]*x[k];
		x[w] = ( b[w] - s ) / A[w*n+w];
	}
	return x;
}
