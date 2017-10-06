#include"assig1.h"


double cal_vector_dis(double *v1, double *v2, int len)
{
    double sum = 0;
    for(int i = 0; i < len ; i++)
        sum += (*(v1+i) - *(v2+i)) * (*(v1+i) - *(v2+i));

    return sqrt(sum);
}


double** cal_dists(double (**v1), double (**v2), int row1, int col1, int row2, int col2)
{
    double (*res)[row2] = NULL;

    res =  (double (*)[row2])malloc(sizeof(double)*row1*row2);

    for(int i = 0; i < row1; i++)
        for(int j = 0; j < row2; j++)
        {
            res[i][j] = cal_vector_dis((double (*)[col1])(v1+i), (double (*)[col2])(v2+j), col1);
        }

    return res;
    
}
