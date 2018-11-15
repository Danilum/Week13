#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    int x;
    fscanf(input_file, "%d", &x);
    int total_processes;
    fscanf(input_file, "%d", &total_processes);

    int *Ematrix = malloc(sizeof(int) * x);
    int *Amatrix = malloc(sizeof(int) * x);
    int **Cmatrix = malloc(sizeof(int *) * total_processes);
    int **Rmatrix = malloc(sizeof(int *) * total_processes);
    char *Pmatrix = malloc(sizeof(char) * total_processes);

    for (int i = 0; i < x; ++i) 
        fscanf(input_file, "%d", Ematrix + i);
    for (int i = 0; i < x; ++i) 
        fscanf(input_file, "%d", Amatrix + i);
    for (int j = 0; j < total_processes; ++j) 
        Cmatrix[j] = malloc(sizeof(int *) * x);
    for (int k = 0; k < total_processes; ++k) 
        for (int i = 0; i < x; ++i) 
            fscanf(input_file, "%d", Cmatrix[k] + i);
    for (int j = 0; j < total_processes; ++j) 
        Rmatrix[j] = malloc(sizeof(int *) * x);
    for (int k = 0; k < total_processes; ++k) 
        for (int i = 0; i < x; ++i) 
            fscanf(input_file, "%d", Rmatrix[k] + i);
    for (int n = 0; n < total_processes; ++n) 
        Pmatrix[n] = 0;
    while (1) {
        int selected = -1;
        for (int i = 0; i < total_processes && selected == -1; ++i) {
            fflush(stdout);
            if (!Pmatrix[i]) {
                int all = 1;
                for (int j = 0; j < x && all; ++j) 
                    if (Amatrix[j] < Rmatrix[i][j]) 
                        all = 0;
                if (all) 
                    selected = i;
            }
        }
        if (selected != -1) {
            Pmatrix[selected] = 1;
            for (int i = 0; i < x; ++i) 
                Amatrix[i] += Cmatrix[selected][i];
        } 
        else 
            break;
    }
    int flag = 1;
    for (int l = 0; l < total_processes && flag; ++l) 
        flag = Pmatrix[l];
    if (flag) {
        FILE *result = fopen("output_ok", "w+");
        fprintf(result, "No deadlock is detected");
    } 
    else {
        FILE *result = fopen("output_dl", "w+");
        fprintf(result, "Amount of processes that are deadlocked:\n");
        for (int i = 0; i < total_processes; ++i)
            if (!Pmatrix[i])
                fprintf(result, "%d ", i + 1);
    }
}
