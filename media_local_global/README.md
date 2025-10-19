## Cálculo de média com MPI

### Autor
Lucas Pires de Camargo Sarai - 10418013 - 06D

### O que ele faz
O programa gera valores aleatórios para cada processo e, ao final, soma todos os valores e retorna uma média global no processo raiz (0). <br>

**Observação**
- Para gerar valores distintos entre os processos, usa srand(time(NULL) + rank_do_processo), o que criará sementes bem diferentes.

### Compilação e execução

Foi montado um Makefile com as seguintes características:

**Compilação**

- Usa o comando abaixo:
> mpicc media_local_global.c -o media_local_global

- Além disso, foi configurado para apenas recompilar se houver mudança no código fonte.

**Execução** 
> mpirun -np=$(NP) media_local N
- NP -> Configurado com valor padrão 2, gerando 2 processos
- N -> Configurado com valor 5, montando vetores de 5 valores aleatórios
- Ou seja, se não receber um dos valores anteriores, usa os valores padrão

**Exemplos** 
> make
1. Compila se houver alterações no código fonte
2. Gera 2 processos com 5 valores em cada vetor local
3. Apaga arquivo executável

>make NP=4 N=10
1. Compila se houver alterações no código fonte
2. Gera 4 processos com 10 valores em cada vetor local
3. Apaga arquivo executável

### Testes 

#### Padrão: NP=2, N=5
```
[DEBUG - Processo 0] Dados gerados : [ 0.425796 0.742393 0.623153 0.731425 0.739717 ]
[DEBUG - Processo 0] Soma Local = 3.262485, Media Local: 0.652497
[DEBUG - Processo 1] Dados gerados : [ 0.782486 0.153948 0.923268 0.549434 0.671974 ]
[DEBUG - Processo 1] Soma Local = 3.081110, Media Local: 0.616222
[RESULTADO - Processo 0] Soma global = 6.343595
[RESULTADO - Processo 0] Media global = 3.171797
```

#### NP=3, N=2
```
[DEBUG - Processo 2] Dados gerados : [ 0.470453 0.576568 ]
[DEBUG - Processo 2] Soma Local = 1.047021, Media Local: 0.523511
[DEBUG - Processo 0] Dados gerados : [ 0.257463 0.255475 ]
[DEBUG - Processo 0] Soma Local = 0.512937, Media Local: 0.256469
[DEBUG - Processo 1] Dados gerados : [ 0.111300 0.162927 ]
[DEBUG - Processo 1] Soma Local = 0.274227, Media Local: 0.137114
[RESULTADO - Processo 0] Soma global = 1.834185
[RESULTADO - Processo 0] Media global = 0.611395
```

#### NP=4, N=10
```
[DEBUG - Processo 0] Dados gerados : [ 0.941350 0.336433 0.150508 0.606178 0.251610 0.533697 0.297100 0.839099 0.018833 0.127480 ]
[DEBUG - Processo 0] Soma Local = 4.102288, Media Local: 0.410229
[DEBUG - Processo 2] Dados gerados : [ 0.157132 0.660162 0.753631 0.245243 0.616892 0.972627 0.017764 0.925982 0.626446 0.795156 ]
[DEBUG - Processo 2] Soma Local = 5.771035, Media Local: 0.577103
[DEBUG - Processo 1] Dados gerados : [ 0.801984 0.251686 0.956658 0.929076 0.688170 0.258649 0.161570 0.637081 0.829177 0.716410 ]
[DEBUG - Processo 1] Soma Local = 6.230462, Media Local: 0.623046
[DEBUG - Processo 3] Dados gerados : [ 0.012733 0.070742 0.055498 0.062209 0.547758 0.692507 0.375256 0.717039 0.930761 0.875891 ]
[DEBUG - Processo 3] Soma Local = 4.340395, Media Local: 0.434040
[RESULTADO - Processo 0] Soma global = 20.444180
[RESULTADO - Processo 0] Media global = 5.111045
```

