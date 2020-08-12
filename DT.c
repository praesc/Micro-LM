#include "ELM.h"

#ifdef DT

#include "DT.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#ifdef DS_TEST
void decisionTree_test_dataset(bool isRegression)
{

    #ifndef REGRESSION
        int predictedLabels[N_TEST];
    #else
        float predictions[N_TEST];
    #endif

    int nCorrect = 0;
    int i = 0;

    for (i = 0; i < N_TEST; i++)
    {
        #ifndef REGRESSION
        {
            //float *X_t = preprocess(X_test[i]);
            predictedLabels[i] = decisionTree_classification(X_test[i]);
            if (predictedLabels[i] == y_test[i])
            {
                nCorrect++;
            }
        }
        #else
        {
            predictions[i] = decisionTree_regression(X_test[i]);
        }
        #endif
    }

    #ifndef REGRESSION
    {
        printf("\nDecision tree rate: %f\n", (float)nCorrect * 100.0f / (float)N_TEST);
        fflush(stdout);
    }
    #else
    {
        //TBD, figure for regression
    }
    #endif
}
#endif

#ifndef REGRESSION
int decisionTree_classification(int X[])
{
    int currentNode = 0;
    int fNode = 0;
    while (1)
    {
        fNode = feature[currentNode];
        if (fNode >= 0)
        {
            if ((X[fNode] - u_x[fNode]) * 100 / s_x[fNode] <= threshold[currentNode])
            {
                currentNode = children_left[currentNode];
            }
            else
            {
                currentNode = children_right[currentNode];
            }
        }
        else
        { // Leaf node
            {
                int j;
                int maxClass;
                int maxValue = 0;
                for (j = 0; j < N_CLASS; j++)
                {
                    if (values[currentNode][j] >= maxValue)
                    {
                        maxValue = values[currentNode][j];
                        maxClass = target_classes[j];
                    }
                }
                return maxClass;
            }
            break;
        }
    }
}
#else
float decisionTree_regression(float X[])
{
    int currentNode = 0;
    while (1)
    {
        if (feature[currentNode] >= 0)
        {
            if (X[feature[currentNode]] <= threshold[currentNode])
            {
                currentNode = children_left[currentNode];
            }
            else
            {
                currentNode = children_right[currentNode];
            }
        }
        else
        { // Leaf node
            return values[currentNode][0];
        }
    }
}
#endif

#endif