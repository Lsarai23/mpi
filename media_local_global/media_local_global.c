#include <stdio.h>  
#include <stdlib.h>
#include <time.h>

#include "mpi.h"

int main(int argc, char** argv){
    int current_process, total_process;
    
    if(argc == 1){
        printf("[ERRO] Uso: mpirun [-np=<numero de processos>] ./executavel <N: o tamanho do vetor local que será gerado por cada processo>\n");
        return EXIT_FAILURE;
    }
    
    int arrays_size = atoi(argv[1]);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &current_process);
    MPI_Comm_size(MPI_COMM_WORLD, &total_process);
    
    srand(time(NULL) + current_process);
    
    //Montando dados locais de cada processo
    float* process_data = (float*)malloc(arrays_size * sizeof(float));
    
    //Processando localmente
    float local_sum = 0;
    printf("[DEBUG - Processo %d] Dados gerados : [ ", current_process);
    for(int i = 0; i < arrays_size; i++){
        process_data[i] = rand() / (float)RAND_MAX;
        printf("%f ", process_data[i]);
        local_sum += process_data[i];
    }
    float local_avg = local_sum/arrays_size;
    printf("]\n[DEBUG - Processo %d] Soma Local = %f, Media Local: %f\n", current_process, local_sum, local_avg);

    free(process_data);
    
    //Enviando ao processo raiz as somas locais pra processar a media global
    float global_sum = 0;
    MPI_Reduce(&local_sum,&global_sum,1,MPI_FLOAT,MPI_SUM,0, MPI_COMM_WORLD);

    //Processo raiz ira gerar a media global
    if(current_process == 0){
        float global_avg = global_sum/(float)total_process;
        printf("[RESULTADO - Processo %d] Soma global = %f\n", current_process, global_sum);
        printf("[RESULTADO - Processo %d] Media global = %f\n", current_process, global_avg);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;

}