#include "Preprocess.h"
#include <stdio.h>
//ccc

int X_t[N_FEATURE];
int tmp[N_ORIG_FEATURE];

#ifdef STANDARD_SCALING
int  *normalize_std(int *X, int *s_x, int *u_x){
int i=0;
for (i=0; i<N_ORIG_FEATURE; i++) {
    tmp[i] = (X[i] - u_x[i]) * 100 / s_x[i];
}
return tmp;
}
#elif defined(MINMAX_SCALING)
int *normalize_mm(int *X, int *s_x){
int i=0;
for (i=0; i<N_ORIG_FEATURE; i++) {
    tmp[i] = 100 * s_x[i] * X[i];
}
return tmp;
}
#endif

int *PCA_transform(int *X){
int i=0, j=0;
/*float debug[N_ORIG_FEATURE];
for (j=0; j<N_ORIG_FEATURE; j++) {
    debug[j]=X[j];
}*/
for (i=0; i<N_FEATURE; i++) {
    X_t[i]=0;
    for (j=0; j<N_ORIG_FEATURE; j++) {
        X_t[i] += X[j]*pca_components[i][j];
    }
}
return X_t;
}

int *preprocess(int *X)
{
    #ifdef STANDARD_SCALING
        int *tmp = normalize_std(X, s_x, u_x);
    #elif defined(MINMAX_SCALING)
        int *tmp = normalize_mm(X, s_x);
    #endif
    return tmp;//PCA_transform(tmp);
}
