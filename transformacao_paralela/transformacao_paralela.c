#include <stdio.h>  
#include <stdlib.h>

#include "mpi.h"

#define NUMBERS_AMOUNT 100

int main(int argc, char** argv){
    int current_process, total_process;
    int full_data[NUMBERS_AMOUNT];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    MPI_Comm_size(MPI_COMM_WORLD, &total_process);

    //Processo raiz monta vetor original com valores de 1 a 100
    if(current_process == 0){
    printf("[INI] Vetor global: [ 1 a 100]\n");
        for(int i = 0; i < NUMBERS_AMOUNT; i++){
            full_data[i] = i+1;
        }
    }

    //Dividindo dados entre os processos
    //Cada um recebera 100/num_processos
    int process_data_size = NUMBERS_AMOUNT/total_process;
    int* process_data = (int*)malloc(process_data_size * sizeof(int));

    MPI_Scatter(full_data, process_data_size, MPI_INT, process_data, process_data_size, MPI_INT, 0, MPI_COMM_WORLD);

    //Processando localmente
    printf("[DEBUG] Processo %d recebeu [%d - %d]\n", current_process, process_data[0], process_data[process_data_size-1]);
    for(int i = 0; i < process_data_size; i++){
        process_data[i] = process_data[i] * process_data[i];
    }
    printf("[DEBUG] Processo %d transformou para [%d - %d]\n", current_process, process_data[0], process_data[process_data_size-1]);

    //Enviando ao processo raiz o resultado local para exibir vetor completo transformado
    MPI_Gather(process_data,process_data_size,MPI_INT,full_data,process_data_size,MPI_INT,0, MPI_COMM_WORLD);

    if(current_process == 0){
        printf("[RESULTADO] Vetor final: [%d - %d]\n", full_data[0], full_data[NUMBERS_AMOUNT-1]);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;

}