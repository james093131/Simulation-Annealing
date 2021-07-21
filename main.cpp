#include "normal.hpp"

int main(int argc, const char *argv[])
{
    int Run = atoi(argv[1]);
    int Iteration = atoi(argv[2]);
    int Dim = atoi(argv[3]);
    double T = atof(argv[4]);
    double R_t = atof(argv[5]);
    SA sa;
    sa.run(Run, Iteration, Dim, T, R_t);
}