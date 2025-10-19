## Transformação Paralela com MPI

### Autor
Lucas Pires de Camargo Sarai - 10418013 - 06D

### O que ele faz
O programa divide um vetor de 100 elementos entre 5 processos (20 elementos para cada), transforma cada elemento em seu quadrado e retorna ao processo raiz(0) para exibir o vetor transformado<br>

### Compilação e execução

Foi montado um Makefile com as seguintes características:

**Compilação**

- Usa o comando abaixo:
> mpicc transformacao_paralela.c -o transformacao_paralela

- Além disso, foi configurado para apenas recompilar se houver mudança no código fonte.

**Execução** 
> mpirun -np=5 ./transformacao_paralela

**Uso** 
> make
1. Compila se houver alterações no código fonte
2. Executa com 5 processos e 20 valores em cada vetor local
3. Apaga arquivo executável

### Testes 

Não foi possível realizar para o desafio pedido, pois não havia núcleos o suficiente.
Para verificar a solução, foi feito testes com até 4 núcleos

#### 2 núcleos

```
[INI] Vetor global: [ 1 a 100]
[DEBUG] Processo 0 recebeu [1 - 50]
[DEBUG] Processo 0 transformou para [1 - 2500]
[DEBUG] Processo 1 recebeu [51 - 100]
[DEBUG] Processo 1 transformou para [2601 - 10000]
[RESULTADO] Vetor final: [1 - 10000]
```

#### 4 núcleos
```
[INI] Vetor global: [ 1 a 100]
[DEBUG] Processo 0 recebeu [1 - 25]
[DEBUG] Processo 0 transformou para [1 - 625]
[DEBUG] Processo 1 recebeu [26 - 50]
[DEBUG] Processo 1 transformou para [676 - 2500]
[DEBUG] Processo 2 recebeu [51 - 75]
[DEBUG] Processo 2 transformou para [2601 - 5625]
[DEBUG] Processo 3 recebeu [76 - 100]
[DEBUG] Processo 3 transformou para [5776 - 10000]
[RESULTADO] Vetor final: [1 - 10000]
```