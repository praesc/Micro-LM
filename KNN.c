#include "ELM.h"

#ifdef KNN

#include "KNN.h"
#include <stdio.h>

#include "math.h"
#include <stdlib.h> // To check if works on STM32
#include <string.h> // To check if works on STM32


struct neighbour{
        int id;
        int score;
    };
int struct_cmp_by_score_dec(const void *, const void *);

//int regressionLabels[N_CLASS]; //Attention!!!!!!!!


#ifdef DS_TEST
void knn_test_dataset(bool isRegression) {
    // KNN
    // https://www.geeksforgeeks.org/weighted-k-nn/
    struct neighbour neighbours[N_TRAIN];

    int nCorrect = 0;
    int i = 0;
    printf("here, %d", N_FEATURE);
    int predictedLabels[N_TEST];
    int X_te[N_FEATURE];
    for(i=0; i < N_TEST; i++) {
            /*int *X_t = preprocess(X_test[i]);
            for (int f=0; f< N_FEATURE; f++)
                 X_te[f] = X_t[f];*/
            predictedLabels[i] = knn_classification(X_test[i]);
            if (predictedLabels[i] == y_test[i]) {
                nCorrect++;
            }
    }
    printf("\nK-nn rate: %f\n", (float)nCorrect*100.0f/(float)N_TEST);
    return;
}
#endif

#ifndef REGRESSION
int knn_classification(int X[]) {
    // KNN
    // https://www.geeksforgeeks.org/weighted-k-nn/
    struct neighbour neighbours[N_TRAIN];

    int j;
    for(j=0; j < N_TRAIN; j++){
        neighbours[j].id = j;

        int acc=0;
        bool skip=false;
        int k;
        //int *X_t_ = preprocess(X_train[j]);
        for(k=0; k < N_FEATURE; k++){
            acc+=abs(X[k] - X_train[j][k]);
            //printf("%d %d \n",X[k], X_t_[k]);
            }

        neighbours[j].score = acc;            
    }
    qsort(neighbours, N_TRAIN, sizeof(struct neighbour), struct_cmp_by_score_dec);
    
    {
        int n;
        int scores[N_CLASS];
        memset(scores, 0, N_CLASS*sizeof(int)); 
        for(n=0; n<K; n++) {
            scores[y_train[neighbours[n].id]] += neighbours[n].score;      
	}
        int bestScore=0;
        int bestClass;
        for(n=0; n<N_CLASS; n++) {
            if (scores[n] > bestScore) {
                bestScore = scores[n];
                bestClass = n;
            }
        }
        return(bestClass);
    }
}
#endif


/* qsort struct comparision function (price float field) */ 
int struct_cmp_by_score_dec(const void *a, const void *b) 
{ 
    struct neighbour *ia = (struct neighbour *)a;
    struct neighbour *ib = (struct neighbour *)b;
    return (int)(ia->score - ib->score);
	/* float comparison: returns negative if b > a 
	and positive if a > b. We multiplied result by 100.0
	to preserve decimal fraction */ 
    //Decreasing
} 
#endif




