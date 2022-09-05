#ifndef evolution_h   
#define evolution_h    

int rhs(int j, double x[], double **sol, double RHS[]);

int evolution(double x[], double t[], double **sol1 , double **sol2);

#endif 
