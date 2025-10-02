#include <stdio.h>  
#include <stdlib.h>

#include "mpi.h"

#define NUMBERS_AMOUNT 40

/**
 * @author Lucas Pires de Camargo Sarai - 10418013
 *         Turma 06D (manha)
 */

int main(int argc, char** argv){
    int current_process, total_process;
    int full_data[NUMBERS_AMOUNT];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    MPI_Comm_size(MPI_COMM_WORLD, &total_process);

    //Processo raiz monta vetor original com valores de 1 a 40
    if(current_process == 0){
    printf("[INI] Vetor global: [ ");
        for(int i = 0; i < NUMBERS_AMOUNT; i++){
            full_data[i] = i+1;
            printf("%d ", full_data[i]);
        }
        printf("]\n");
    }

    //Dividindo dados entre os processos
    //Cada um recebera 40/num_processos
    int process_data_size = NUMBERS_AMOUNT/total_process;
    int* process_data = (int*)malloc(process_data_size * sizeof(int));

    MPI_Scatter(full_data, process_data_size, MPI_INT, process_data, process_data_size, MPI_INT, 0, MPI_COMM_WORLD);

    //Processando localmente
    int local_result = 0;
    printf("[DEBUG] Processo %d recebeu [ ", current_process);
    for(int i = 0; i < process_data_size; i++){
        printf("%d ", process_data[i]);
        local_result += process_data[i] * process_data[i]; // Soma de quadrados
    }
    printf("]\n[DEBUG] Processo %d calculou %d\n", current_process, local_result);

    //Enviando ao processo raiz o resultado local para processar o resultado esperado
    //Cada 40/num_processos enviados a cada processo, 1 valor unico de resultado eh retornado
    int global_result = 0;
    MPI_Reduce(&local_result,&global_result,1,MPI_INT,MPI_SUM,0, MPI_COMM_WORLD);

    //Processo raiz ira validar resultado calculado com esperado
    if(current_process == 0){
        int expected_result = (NUMBERS_AMOUNT * (NUMBERS_AMOUNT + 1) * (2 * NUMBERS_AMOUNT + 1))/6;

        printf("[RESULTADO] Processo root (0): \n");
        printf("Resultado esperado: %d\n", expected_result);
        printf("Resultado obtido: %d\n", global_result);
        if(global_result == expected_result){
            printf("[SUCESSO] Resultado %d corresponde ao esperado!\n", global_result);
        }
        else{
            printf("[ERRO] Resultado %d diverge do resultado esperado %d!\n", global_result, expected_result);
            return EXIT_FAILURE;
        }

    }

    MPI_Finalize();
    return EXIT_SUCCESS;

}