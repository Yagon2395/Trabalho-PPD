#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

using namespace std;

int dim;
int* retornaMatriz(){

    int *a;
    ifstream arq("grafo.txt",std::ifstream::in);
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
void zera_aresta(int *a, int dim, int *vetcores, int v){// ok
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

__device__
bool possui_aresta(int vet[], int tam){
  for (int i=0; i< tam; i++){
        if (vet[i] == 1){
            return true;
        }
    }
    return false;
}

__device__
bool ha_elementos_a_colorir(int vet[], int tam){// ok
  for (int i=0; i< tam; i++){
        if (vet[i] == 0 || vet[i] == -1){
            return true;
        }
    }
    return false;
}

__global__
void teste_kernel(int dim, int *u, int *vetcores){

int cor_atual = 1;// iniciando c a primeira cor valendo 1
int vzin;// vertice de menor grau
int idx = __umul24( blockDim.x, blockIdx.x) + threadIdx.x;
zera_aresta(u,dim,vetcores,0);
  for (int i = 0; i < dim; i++){
     for(int j = 0; j < dim; j++){
       if(u[j + i*dim] == 1)
        u[j + i*dim] = idx;
     }
  }

//iniciando o vetor de cores
  for (int i = 0; i < dim; i ++){

    vetcores[i] = 0;
  }


}


int main(){

  //variaveis da cpu
  int *u = retornaMatriz();
  int *vetcores = new int[dim];
  //variaveis da gpu
  int *d_u, *d_vetcores, *d_w;

  //iniciando o vetor de cores
  for (int i=0; i<dim; i++){
        vetcores[i] = 0;
    }
  //alocando acesso pra gpu
  cudaMalloc(&d_vetcores,dim*sizeof(int));
  cudaMalloc(&d_u,       dim*dim*sizeof(int));
  cudaMalloc(&d_w,       dim*dim*sizeof(int));
  //copiando a matriz pra gpu
  cudaMemcpy(d_u,u,dim*dim*sizeof(int),cudaMemcpyHostToDevice);
  //executando função da gpu
  teste_kernel<<<16,16>>>(dim,d_u,d_vetcores);
  //esperando acabar o processamento da gpu
  cudaDeviceSynchronize();
  //pegando o resultado da gpu e jogando pro processador
  cudaMemcpy(u,d_u,dim*dim*sizeof(int),cudaMemcpyDeviceToHost);
  cudaMemcpy(vetcores,d_vetcores,dim*sizeof(int),cudaMemcpyDeviceToHost);


  for (int i = 0; i < dim; i++){
   for(int j = 0; j < dim; j++){
     cout << u[j + i*dim] << " ";
   }
   cout << endl;
}

for (int i=0; i<dim; i++){
        cout << i << " " << vetcores[i] << endl;
    }

  cudaFree(d_u);
  cudaFree(d_vetcores);

  return 0;

}