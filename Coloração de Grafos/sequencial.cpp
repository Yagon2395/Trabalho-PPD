#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

int dim;
int *vetcores;
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
    int menor = tam;
    bool primeiro = true;
    int vertice_menor_grau;

    for(int i = 0; i < tam; i++){
        grau = 0;
        for(int j = 0; j < tam; j++){
            grau = grau + a[j + i*dim];
        }
        if((primeiro || grau < menor) && vetcores[i] == 0){
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
        //cout << "Dimensao: "<< dimensao <<endl;
        a = new int[dimensao*dimensao];
        for(int i=0;i<dimensao*dimensao;i++){
            arq >> a[i];
        }
    }
    arq.close();
    return a;
}

void zera_aresta(int *a,int dim, int v){

if(vetcores[v] == 0){
    vetcores[v] = -1;
}

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
    double tfor = 0;
    dim = retornaDimensao();
    vetcores = new int[dim];
    int *u = retornaMatriz();
    int *w = new int[dim*dim];
    int vzin;
    int cor_atual = 1;

    //inicializa o vetor de cores
    for (int i=0; i<dim; i++){
        vetcores[i] = 0;
    }

    while (ha_elementos_a_colorir(vetcores, dim)){
        memcpy(w, u, dim*dim*sizeof(int));// w = u
        for(int i = 0; i < dim; i++){
            if(vetcores[i] == -1){
                vetcores[i] = 0;
            }
        }
        //cout << "cor: " << cor_atual << endl;
        while(possuiAresta(w,dim*dim)){
            //cout << "--------------------------------------------" << endl;
            vzin = menor_grau(w,dim);// acha o vertice de menor grau em w
            vetcores[vzin] = cor_atual ;// colore

            /*for (int i = 0; i < dim; i++){
                for(int j = 0; j < dim; j++){
                  cout << w[j + i*dim] << " ";
                }
                cout << endl;
             }*/
             //cout << "vzin: " << vzin << endl;
            tStart = clock();
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
            // cout << "vetcores: ";
            // for (int i = 0; i < dim; ++i)
            // {
            //     cout << vetcores[i] << ", ";
            // }
            // cout  << endl;

            // cout << "w: \n";
            // for (int i = 0; i < dim*dim; ++i)
            // {
            //     cout << w[i] << ", ";
            //     if(i%dim == dim-1)
            //         cout << endl;
            // }
            // cout  << endl;

            // cout << "u: \n";
            // for (int i = 0; i < dim*dim; ++i)
            // {
            //     cout << u[i] << ", ";
            //     if(i%dim == dim-1)
            //         cout << endl;
            // }
            // cout  << endl;
        }
        cor_atual++;
    }

    for(int i = 0; i < dim; i++){
         // cout << "vetcores[" << i << "]: " << vetcores[i] << endl;
    }
    
    //ompwtime
    cout << tfor;
    return 0;
}

