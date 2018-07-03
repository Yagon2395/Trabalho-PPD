#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

using namespace std;

int dim;
int *vetCores;
string arquivo = "grafo2500.txt";

int retornaDimensao(){
  ifstream arq (arquivo.c_str(),std::ifstream::in);
  int d = 0;
  if(arq.is_open()){
    arq >> d;
  }
  arq.close();
  return d;
}

//função para descobrir se existe 0 no vetor de cores (caso exista 0, é porque tem ainda de colorir o vértice)
bool ha_elementos_a_colorir (int vet[], int tam){
    for (int i=0; i< tam; i++){
        if (vet[i] == 0 || vet[i] == -1){
            return true;
        }
    }
    return false;
}

bool possuiAresta (int vet[], int tam){

    for (int i=0; i< tam; i++){
        if (vet[i] == 1){
            return true;
        }
    }
    return false;
}

int menor_grau(int a[],int tam){
    int grau;
    int temp;
    int menor = tam;
    bool primeiro = true;
    int vertice_menor_grau;

    //#pragma omp parallel for num_threads(4)
    for(int i = 0; i < tam; i++){
        grau = 0;
        #pragma omp parallel for reduction (+:temp)
        for(int j = 0; j < tam; j++){
            temp += a[j + i*dim];
        }
        if((primeiro || grau < menor) && vetCores[i] == 0){
            primeiro = false;
            menor = grau;
            vertice_menor_grau =i;
        }
    }
    return vertice_menor_grau;
}

int* retornaMatriz(){
    int dimensao;
    int *a;
    ifstream arq(arquivo.c_str(),std::ifstream::in);
    if(arq.is_open()){
        arq >> dimensao;
        a = new int[dimensao*dimensao];
        for(int i=0;i<dimensao*dimensao;i++){
            arq >> a[i];
        }
    }
    arq.close();
    return a;
}

void zera_aresta(int *a,int dim, int v){

    if(vetCores[v] == 0){
        vetCores[v] = -1;
    }
    #pragma omp parallel for num_threads(4)
    for(int i = 0; i < dim; i++){
        if(i == v){
            for(int j = 0; j < dim; j++){
                a[j + i*dim] = 0;
            }
        }
    }
}

int main(){
    clock_t tStart;
    clock_t texec = clock();
    double tfor = 0;
    dim = retornaDimensao();
    vetCores = new int[dim];
    int *u = retornaMatriz();
    int *w = new int[dim*dim];
    int vzin;
    int cor_atual = 1;
    //inicializa o vetor de cores
    
    #pragma omp parallel for num_threads(4)
    for (int i=0; i<dim; i++){
        vetCores[i] = 0;
    }
    while (ha_elementos_a_colorir(vetCores, dim)){
        memcpy(w, u, dim*dim*sizeof(int));// w = u
        #pragma omp parallel for num_threads(4)
        for(int i = 0; i < dim; i++){
            if(vetCores[i] == -1){
                vetCores[i] = 0;
            }
        }
        while(possuiAresta(w,dim*dim)){
            vzin = menor_grau(w,dim);// acha o vertice de menor grau em w
            vetCores[vzin] = cor_atual ;// colore
            tStart = clock();
            //#pragma omp parallel for num_threads(4)
            for(int i = 0; i < dim; i++){
                if(vzin == i){
                    for(int j =0; j < dim; j++){
                        if(w[j +i*dim] == 1){
                            zera_aresta(w,dim,j);
                        }
                    }
                    zera_aresta(w,dim,i);
                    zera_aresta(u,dim,i);
                }
            }
            tfor += ((double)(clock() - tStart)/CLOCKS_PER_SEC);
        }
        cor_atual++;
        //cout << cor_atual << endl;
    }
    
    
    cout << "Tempo de execução do for: " << tfor/4 << endl;
    cout << "Tempo de execução do algoritmo: " << ((double)(clock() - texec)/CLOCKS_PER_SEC)/4 << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Saida do vetor contendo os vértices coloridos: " << endl;
    for(int i = 0; i < dim; i++){
        cout << "vetcores[" << i << "]: " << vetCores[i] << endl;
    }

    return 0;
}


