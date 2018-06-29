#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>
#include <stdio.h>
using namespace std;
int dim;
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

int menor_grau(int a[],int tam, int* vetcores){
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

  int *a;
  ifstream arq(arquivo.c_str(),std::ifstream::in);
  if(arq.is_open()){
    arq >> dim;
        //cout << "Dimensao: "<< dimensao <<endl;
    a = new int[dim*dim];
    for(int i=0;i<dim*dim;i++){
      arq >> a[i];
    }
  }
  arq.close();
  return a;
}


__device__
void zera_aresta(int *a,int dim, int v, int* d_vetcores){

  if(d_vetcores[v] == 0){
    d_vetcores[v] = -1;
  }
  for(int i = 0; i < dim; i++){
    if(i == v){
      for(int j = 0; j < dim; j++){
        a[j + i*dim] = 0;
      }
    }
  }
}

__global__
void d_main(int dim, int* d_vetcores, int* w, int* u, int vzin, int num_threads){
  int aux = blockDim.x * blockIdx.x + threadIdx.x;
  int i;
  for(i = aux; i < dim; i += blockDim.x * num_threads){
    if(vzin == i){
      for(int j =0; j < dim; j++){
        if(w[j +i*dim] == 1){
          zera_aresta(w,dim,j,d_vetcores);
        }
      }
      zera_aresta(w,dim,i,d_vetcores);
      zera_aresta(u,dim,i,d_vetcores);
    }
    __syncthreads();
  }
}

int main(){
    //variaveis da cpu
  int *u = retornaMatriz();
  int *vetcores = new int[dim];
  //variaveis da gpu
  int *d_u, *d_vetcores, *d_w;
  int *w = new int[dim*dim];
  int vzin;
  int cor_atual = 1;
  //alocando acesso pra gpu
  cudaMalloc(&d_vetcores,dim*sizeof(int));
  cudaMalloc(&d_u,       dim*dim*sizeof(int));
  cudaMalloc(&d_w,       dim*dim*sizeof(int));

  int num_threads = 16;
  int num_blocks  = 32;
  clock_t tStart = clock();
  double tfor = 0;
  for (int i=0; i<dim; i++){
    vetcores[i] = 0;
  }
  while (ha_elementos_a_colorir(vetcores, dim)){
        memcpy(w, u, dim*dim*sizeof(int));
        cudaMemcpy(d_w, w, dim*dim*sizeof(int), cudaMemcpyHostToDevice);// w = u
        cudaMemcpy(d_u, w, dim*dim*sizeof(int), cudaMemcpyHostToDevice);// w = u
        for(int i = 0; i < dim; i++){
          if(vetcores[i] == -1){
            vetcores[i] = 0;
          }
        }
        while(possuiAresta(w,dim*dim)){
            vzin = menor_grau(w,dim, vetcores);// acha o vertice de menor grau em w
            vetcores[vzin] = cor_atual ;// colore
            cudaMemcpy(d_vetcores, vetcores, dim*sizeof(int),cudaMemcpyHostToDevice);
            tStart = clock();
            d_main<<<num_threads,num_blocks>>>(dim, d_vetcores, d_w, d_u, vzin, num_threads);
            tfor +=  ((double)(clock() - tStart)/CLOCKS_PER_SEC);
            cudaMemcpy(vetcores, d_vetcores, dim*sizeof(int),cudaMemcpyDeviceToHost);
            cudaMemcpy(w, d_w, dim*dim*sizeof(int), cudaMemcpyDeviceToHost);// w = u
            cudaMemcpy(u, d_u, dim*dim*sizeof(int), cudaMemcpyDeviceToHost);// w = u

          //   cout << "vetcores: ";
          //   for (int i = 0; i < dim; ++i)
          //   {
          //       cout << vetcores[i] << ", ";
          //   }
          //   cout  << endl;

          //   cout << "w: \n";
          //   for (int i = 0; i < dim*dim; ++i)
          //   {
          //       cout << w[i] << ", ";
          //       if(i%dim == dim-1)
          //           cout << endl;
          //   }
          //   cout  << endl;

          //   cout << "u: \n";
          //   for (int i = 0; i < dim*dim; ++i)
          //   {
          //       cout << u[i] << ", ";
          //       if(i%dim == dim-1)
          //           cout << endl;
          //   }
          //   cout  << endl;
          }
          cor_atual++;
        }
        for(int i = 0; i < dim; i++){
          // cout << "vetcores[" << i << "]: " << vetcores[i] << endl;
        }
        cout << tfor;
        return 0;

      }