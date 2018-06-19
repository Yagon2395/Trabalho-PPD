#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <time.h>

using namespace std;

int dim;
int *vetCores;

int retornaDimensao(){
  ifstream arq ("grafo.txt",std::ifstream::in);
  int d = 0;
  if(arq.is_open()){
    arq >> d;
  }
  arq.close();
  return d;
}

//função para descobrir se existe 0 no vetor de cores (caso exista 0, é porque tem ainda de colorir o vértice)
bool ha_elementos_a_colorir (int vet[], int tam){
    bool aux = false;
    //#pragma omp parallel for reduction (||:aux)
    for (int i = 0; i < tam; i++){
        if (vet[i] == 0 || vet[i] == -1){
            aux = true;
        }
    }
    return aux;
}

bool possuiAresta (int vet[], int tam){
	bool aux = false;
	//#pragma omp parallel for reduction (||:aux)
    for (int i = 0; i < tam; i++){
        if (vet[i] == 1){
            aux = true;
        }
    }
    return aux;
}

int menor_grau(int a[],int tam){
    int grau;
    int temp;
    int menor = tam;
    bool primeiro = true;
    int vertice_menor_grau;

    for(int i = 0; i < tam; i++){
        grau = 0;
        //#pragma omp parallel for private (temp) reduction (+:grau)
        for(int j = 0; j < tam; j++){
            temp = temp + a[j + i*dim];
        }
        if((primeiro || grau < menor) && vetCores[i] == 0){
            primeiro = false;
            menor = grau;
            vertice_menor_grau = i;
        }
    }
    return vertice_menor_grau;
}

int* retornaMatriz(){
    int dimensao;
    int *a;
    ifstream arq("grafo.txt",std::ifstream::in);
    if(arq.is_open()){
        arq >> dimensao;
        //cout << "Dimensao: "<< dimensao <<endl;
        a = new int[dimensao*dimensao];
        for(int i = 0; i < dimensao*dimensao; i++){
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
//#pragma omp parallel for
    for(int i = 0; i < dim; i++){
        if(i == v){
            for(int j = 0; j < dim; j++){
                a[j + i*dim] = 0;
            }
        }
    }
}

int main(){
    clock_t tStart = clock();
    dim = retornaDimensao();
    vetCores = new int[dim];
    int *u = retornaMatriz();
    int *w = new int[dim*dim];
    int vzin;
    int cor_atual = 1;

    //inicializa o vetor de cores
    for (int i=0; i<dim; i++){
        vetCores[i] = 0;
    }

    while (ha_elementos_a_colorir(vetCores, dim)){
        memcpy(w, u, dim*dim*sizeof(int));// w = u
        for(int i = 0; i < dim; i++){
            if(vetCores[i] == -1){
                vetCores[i] = 0;
            }
        }
        //cout << "cor: " << cor_atual << endl;
        while(possuiAresta(w,dim*dim)){
            //cout << "--------------------------------------------" << endl;
            vzin = menor_grau(w,dim);// acha o vertice de menor grau em w
            vetCores[vzin] = cor_atual ;// colore
            //cout << "vzin: " << vzin << endl;

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
        }
        cor_atual++;
    }
/*
    for(int i = 0; i < dim; i++){
        cout << "vetCores[" << i << "]: " << vetCores[i] << endl;
    }
*/
    cout << "Tempo de execução: " << ((double)(clock() - tStart)/CLOCKS_PER_SEC) << " segundos" << endl;
    //ompwtime

    return 0;
}


