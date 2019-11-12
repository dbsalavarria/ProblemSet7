#include <stdio.h>

int main() 
{
    FILE *fp; // pointer to FILE
    fp = popen("gnuplot --persist -e \"plot \\\"< head -100 sine.dat\\\" using 1:2 with lines\"", "r"); // fopen to open gnuplot and plot sine.dat
    
    if (fp == NULL) // check if FILE exists
    {
        printf("Error al abrir archivo.");
        return 1;
    }
    pclose(fp);
}