#ifndef boundary_h   
#define boundary_h  

double wL(int j, double **sol);

double wR(int j, double **sol);

int boundary_Lagrange(double x[], double **sol);

#endif 
