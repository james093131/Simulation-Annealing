#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <time.h>
using namespace std;
typedef vector<char> c1d;
typedef vector<c1d> c2d;
typedef vector<c2d> c3d;
typedef vector<c3d> c4d;
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<i2d> i3d;
typedef vector<i3d> i4d;
typedef vector<double> d1d;
typedef vector<d1d> d2d;
typedef vector<d2d> d3d;
typedef vector<d3d> d4d;

class SA
{
public:
    i1d Run_result;
    i1d Run_iteration;

public:
    void run(int Run, int Iter, int Dim, double T, double Rt)
    {
        srand((unsigned)time(NULL));
        Run_set(Iter, Run);
        double START, END;

        START = clock();
        for (int i = 0; i < Run; i++)
        {
            int iteration = 0;
            Set(Dim);
            Initial();
            while (iteration < Iter)
            {
                i1d New_H = Transition();
                int New_Objective = Evaluation(New_H);
                Determination(New_H, New_Objective, T, Rt);
                Run_iteration[iteration] += Objective;
                iteration++;
            }
            Run_result[i] = Objective;
        }
        END = clock();

        Output(Run, Iter, Dim, START, END);
    }

private:
    i1d H;
    int Objective;

private:
    void Run_set(int iteration, int Run)
    {
        Run_iteration.resize(iteration, 0);
        Run_result.resize(Run, 0);
    }
    inline int randomInt(int min, int max)
    {
        return (rand() % (max - min + 1) + min);
    }
    inline double randomDouble() //uniform distribution [0, 1)
    {
        return (double)rand() / (double)RAND_MAX;
    }
    void Set(int Dim)
    {
        H.clear();
        H.swap(H);
        H.resize(Dim, 0);
        Objective = 0;
    }
    void Initial()
    {
        for (int i = 0; i < H.size(); i++)
        {
            H[i] = randomInt(0, 1);
        }
        Objective = Evaluation(H);
    }
    i1d Transition()
    {
        i1d temp;
        temp = NeighborSelection();

        return temp;
    }
    int Evaluation(i1d arr)
    {
        int OBJ = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            OBJ += arr[i];
        }
        return OBJ;
    }
    void Determination(i1d NEW_H, int NEW_OBJ, double &T, double Rt)
    {
        if (NEW_OBJ >= Objective)
        {
            H = NEW_H;
            Objective = NEW_OBJ;
        }
        else
        {
            double R = randomDouble();
            double delta_f = NEW_OBJ - Objective;
            double P = exp(delta_f / T);
            if (R < P)
            {
                H = NEW_H;
                Objective = NEW_OBJ;
            }
        }
        T *= Rt;
    }
    i1d NeighborSelection()
    {
        int Change_index = randomInt(0, H.size() - 1);
        i1d temp = H;
        if (temp[Change_index] == 0)
            temp[Change_index] = 1;
        else
            temp[Change_index] = 0;

        return temp;
    }

    void Output(int run, int iteration, int dim, double START, double END)
    {
        int Run_AVG = 0;
        int Run_Best = 0;
        for (int i = 0; i < run; i++)
        {
            Run_AVG += Run_result[i];

            if (Run_result[i] > Run_Best)
                Run_Best = Run_result[i];
        }

        Run_AVG /= run;
        for (int i = 0; i < iteration; i++)
        {
            cout << i + 1 << ' ' << double(Run_iteration[i]) / run << endl; //using double to observe average convergence status.
        }
        cout << "# Run : " << run << endl;
        cout << "# Iteration : " << iteration << endl;
        cout << "# Dimension : " << dim << endl;
        cout << "# Best Objective : " << Run_Best << endl;
        cout << "# Average Objective : " << Run_AVG << endl;
        cout << "# Execution Time : " << (END - START) / CLOCKS_PER_SEC << "(s)" << endl;
    }
};
