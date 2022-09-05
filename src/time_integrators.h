#ifndef time_integrators_h   
#define time_integrators_h  

int RK3_grid(double x[], double **sol1 , double **sol2, int (*rhs)(), int (*boundary)());

#endif 
