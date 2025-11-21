#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

#include <time.h>

#define INT_MAX 2147483647

#define MAX_VERTICES 64
#define MAX_ARESTAS 256

int n;
float adj[MAX_VERTICES][MAX_VERTICES];
int tempo;

int tem_arco_de_retorno(int v, int *cor)
    {
        cor[v]=1;
        
        for (int i=0; i<n; i++)
        {
            //verifica se os vertices estao conectados
            if (adj[v][i] == 1)
            {
                //verifica se o vertice estÃ¡ sendo percorrido
                if (cor[i] == 1)
                {
                    printf("\n ciclo encontrado (%d->%d)\n", v, i);
                    
                    return 1;
                }
                
                //verifica se o vertice nÃ£o foi percorrido
                if (cor[i] == 0)
                {
                    printf("\n verifica %d->%d\n", v, i);
                    
                    //verifica se achou um ciclo
                    if (tem_arco_de_retorno(i, cor)==1)
                    {
                        printf("\n ciclo encontrado (%d->%d)\n", v, i);
                        
                       return 1;
                    }
                }
            }
        }
        
        //NÃ£o achou um ciclo a partir desse vertice
        cor[v]=2;
        printf("\nfim do caminho %d\n", v);


        return 0;
    }

int tem_ciclo()
    {
       int cor[MAX_VERTICES]={0};
        
        for (int i=0; i<n; i++)
        {
            printf("verificando vertice %d\n",i);
            if (cor[i] == 0)
            {
                if (tem_arco_de_retorno(i, cor)==1)
                {
                   printf("\ntem ciclo\n");
                   return 1;
                }
            }
            else
            {
                printf("vertice jÃ¡ verificado %d\n",i);
            }
        }
        
        printf("\nnao tem ciclo");

        return 0;
    }
    
    
    void visita_matriz(int *cor, int *parent, int *d, int *f, int u, float matriz[MAX_VERTICES][MAX_VERTICES])
  {
      cor[u]=1;
      tempo=tempo+1;
      d[u]=tempo;
      
      printf("%d = (%d/) - Cinza \n", u, d[u]);
      
      for (int i=0; i<n; i++)
        {
            if (matriz[u][i] == 1)
            {
                if (cor[i] == 0)
                {
                    parent[i]= u;
                    visita_matriz(cor, parent, d, f, i, matriz);
                }
            }
        }
     cor[u]=2;
     tempo=tempo+1;
     f[u]=tempo;
     
     printf("%d = (%d/%d) - Preto\n", u, d[u], f[u]);
  }
  
  void busca_profundidade_matriz(){
      
    int cor[MAX_VERTICES]={0};
    int d[MAX_VERTICES]={0};
    int f[MAX_VERTICES]={0};
    
    int parent[n];
    
    tempo = 0;
    
    for (int i=0; i<n; i++)
    {
        if (cor[i] == 0)
        {
            visita_matriz(cor, parent, d, f, i, adj);
            parent[n]=-1;
        }
    }
  }
  
             void Kosaraju(){
              
        //dfs
        
        int cor[MAX_VERTICES]={0};
        int d[MAX_VERTICES]={0};
        int f[MAX_VERTICES]={0};
        
        int parent[MAX_VERTICES];
        
        tempo = 0;
        
        for (int i=0; i<n; i++)
        {
            if (cor[i] == 0)
            {
                visita_matriz(cor, parent, d, f, i, adj);
                parent[n]=-1;
            }
        }
        
        //matriz transposta
        
        float adj_t[MAX_VERTICES][MAX_VERTICES];
    
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++)
            {
                adj_t[i][j]=adj[j][i];
            }
        }         
        
        //Criacao do vetor ordem
        
        int ordem[MAX_VERTICES]={-1};
        
        int f_ord[MAX_VERTICES][2];
        
        for (int i=0; i<n; i++)
        {
            f_ord[i][0]=f[i];
            f_ord[i][1]=i;
        }
        
        //Bubble sort guardando a posicao inicial
        
        for (int i=0; i<n; i++){
            for (int j=0; j<n - i -1; j++)
            {
                if (f_ord[j][0]>f_ord[j+1][0])
                {
                    int aux[2];
                    aux[0]= f_ord[j][0];
                    aux[1]= f_ord[j][1];
                    
                    f_ord[j][0]=f_ord[j+1][0];
                    f_ord[j][1]=f_ord[j+1][1];
                    
                    f_ord[j+1][0]=aux[0];
                    f_ord[j+1][1]=aux[1];
                }
            }
        }
        
        printf("\nordem: ");
    
        for (int i=0; i<n; i++){
            ordem[i]=f_ord[i][1];
            printf("%d ", ordem[i]);
        }
        
        printf("\n\n");
            
        tempo=0;
        
        int ultimo_cor2[MAX_VERTICES]={0};
        int cor2[MAX_VERTICES]={0};
        int d2[MAX_VERTICES]={0};
        int f2[MAX_VERTICES]={0};
        
        //Inicializa vetor
        
        int componentes[n][n];
        
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                componentes[i][j]=-1;
            }
        }
        int comp_i=0;
        
        for (int i=n-1; i>=0; i--)
        {
            if (cor2[ordem[i]] == 0)
            {
                visita_matriz(cor2, parent, d2, f2, ordem[i], adj_t);
                parent[n]=-1;
            }
            
            for (int j=0; j<n; j++)
            {
                if (cor2[j]==2 && ultimo_cor2[j]==0)
                {
                    componentes[comp_i][j]=j;
                }
            }
            
            for (int j=0; j<n; j++)
            {
                if (cor2[j]!=ultimo_cor2[j])
                {
                    comp_i++;
                    j=n;
                }
            }
            
            for (int i=0; i<n; i++)
            {
                ultimo_cor2[i]=cor2[i];
            }
        }
        
        printf("\nComponentes: [ ");
        for (int i=0; i<n && i<comp_i; i++)
        {
          printf("{");
          for (int j=0; j<n; j++){
              if (componentes[i][j]!=-1)
              {
                printf(" %d ",  componentes[i][j]);
              }
          }
          printf("} ");
        }
        printf("]");
    }
        
        
        
        

void printa_grafo(float matriz_ruas[MAX_VERTICES][MAX_VERTICES], bool vertices[MAX_VERTICES], int size){
    
    printf("   ");
    for (int i=0; i<size; i++)
    {
        if (vertices[i])
        {
            if (i<10)
            {
                printf("0");
            }
            
            printf("%d  ",i);
        }
        else
        {
            printf("X   ");
        }
    }
    printf("\n");
    
    for (int i=0; i<size; i++)
    {
        if (vertices[i])
        {
            if (i<10)
            {
                printf("0");
            }
            
            printf("%d ",i);
        }
        else
        {
            printf("X  ");
        }
        
        for (int j=0; j<size; j++)
        {
            printf("%.1f ",matriz_ruas[i][j]);
        }
        printf("\n");
    }
}

bool tem_saida(float matriz_ruas[MAX_VERTICES][MAX_VERTICES], bool *visitas, int vertice, int size) //Verifica se eh ultimo vertice para a partir dele construir as cores
{
    for (int j=0; j<size; j++)
    {
        if (matriz_ruas[vertice][j]>0 && !visitas[j])
        {
            return true;
        }
    }
    return false;
}

void visita(float matriz_ruas[MAX_VERTICES][MAX_VERTICES], int size, int pai, int vertice, float *dist, bool *visitas, int *caminho){
    
    if (visitas[vertice] == true)
    {
        return;
    }
    
    visitas[vertice] = true;

    if (!tem_saida(matriz_ruas, visitas, vertice, size))
    {
        return;
    }
    
    for (int j=0; j<size; j++)
    {
        if (matriz_ruas[vertice][j]>0)
        {	
            float custo_aresta=matriz_ruas[vertice][j];
            
            if(dist[j] > (dist[vertice] + custo_aresta))
            {
                dist[j] = dist[vertice] + custo_aresta;
                
                caminho[j]=vertice;
                
                visita(matriz_ruas,size, vertice, j, dist, visitas, caminho);
            }
        }
    }
}

void calcular_rota(float matriz_ruas[MAX_VERTICES][MAX_VERTICES], int size, int vertice_origem, int vertice_destino, int *caminho)
{
    float dist[size];
    bool visitas[size];
    
    for (int i=0; i<size; i++)
    {
        dist[i]=INT_MAX;
        visitas[i] = false;
        caminho[i]=-1;
    }
    
    dist[vertice_origem]=0;
    
    for (int j=0; j<size; j++)
    {
        if (matriz_ruas[vertice_origem][j]>0)
        {	
            float custo_aresta=matriz_ruas[vertice_origem][j];
            
            if(dist[j] > (dist[vertice_origem] + custo_aresta))
            {
                dist[j] = dist[vertice_origem] + custo_aresta;
                
                caminho[j]=vertice_origem;
                
                visita(matriz_ruas,size, vertice_origem, j, dist, visitas, caminho);
            }
        }
    }
    
    //printf("distancia: %.1f ",dist[vertice_destino]);
}


int main()
{
    srand(time(NULL)); 
    
    int numero=0;
    bool continuar_programa=true;
    
    bool vertices[MAX_VERTICES]={false};
    
    float matriz_ruas[MAX_VERTICES][MAX_VERTICES];
    
    for (int i=0; i<MAX_VERTICES; i++)
    {
        for (int j=0; j<MAX_VERTICES; j++){
            matriz_ruas[i][j]=0;
        }
    }
    
    
    while (continuar_programa) {
        
        printf("Escolha a opcao (0 para ajuda): \n");
        scanf("%d", &numero); // LÃª o nÃºmero digitado pelo utilizador

        // Se o utilizador digitar 0, mostra a ajuda
        switch (numero)
        {
            case -1: {
                
                continuar_programa=false;
                
                break;
            }
            case 0: {
                printf("-1 Encerrar a aplicaÃ§Ã£o\n");
                printf("0 Ajuda\n");
                printf("1 Ler dados de arquivo.txt\n");
                printf("2 Gravar dados de arquivo.txt\n");
                printf("3 Inserir vertice\n");
                printf("4 Inserir aresta\n");
                printf("5 Remove vertice\n");
                printf("6 Remove aresta\n");
                printf("7 Mostrar conteudo do arquivo\n");
                printf("8 Mostrar grafo\n");
                printf("9 Apresentar a conexidade do grafo e o reduzido\n");
                printf("10 Calcular rota\n");
                printf("11 Descobrir grau dos vertices\n");
                printf("12 Korasaju\n");
                
                break;
            }
            case 1: {
                
                FILE *arquivo;
                int tipo_grafo, num_vertices, num_arestas, vertice_origem, vertice_destino;
                float peso_aresta;
    
                arquivo = fopen("grafo.txt", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo!\n");
                    return 1;
                }
                fscanf(arquivo, "%d", &tipo_grafo);
                
                fscanf(arquivo, "%d", &num_vertices);
                
                int vertice_num;
                for (int i=0; i<num_vertices; i++)
                {
                    fscanf(arquivo, "%d", &vertice_num);
                    
                    vertices[vertice_num]=true;
                    
                }
                
                fscanf(arquivo, "%d", &num_arestas);
                
                for (int i=0; i<num_arestas; i++)
                {
                    fscanf(arquivo, "%d %d %f", &vertice_origem, &vertice_destino, &peso_aresta);
                    
                    matriz_ruas[vertice_origem][vertice_destino] = (peso_aresta);
                    
                }
                
                fclose(arquivo);
                
                printf("Arquivo lido com sucesso\n\n");
                
                break;
            }
            case 2: {
                
                FILE *arquivo;
                int tipo_grafo, num_vertices, num_arestas, vertice_origem, vertice_destino;
                float peso_aresta;
    
                arquivo = fopen("grafo.txt", "w");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo!\n");
                    return 1;
                }
                
                tipo_grafo=6;
                fprintf(arquivo,"%d\n", tipo_grafo);     

                num_vertices=0;
                
                for (int i=0; i<MAX_VERTICES; i++)
                {
                    if (vertices[i])
                    {
                        num_vertices++;
                    }
                }

                fprintf(arquivo,"%d\n", num_vertices); 
                
                for (int i=0; i<MAX_VERTICES; i++)
                {
                    if (vertices[i])
                    {
                        fprintf(arquivo,"%d\n", i); 
                    }
                }

                num_arestas=0;
                for (int i=0; i<num_vertices; i++)
                {
                    for (int j=0; j<num_vertices; j++)
                    {
                        if (matriz_ruas[i][j]>0)
                        {
                            num_arestas++;
                        }
                    }
                }
                fprintf(arquivo,"%d\n", num_arestas); 
                
                for (int i=0; i<num_vertices; i++)
                {
                    for (int j=0; j<num_vertices; j++)
                    {
                        if (matriz_ruas[i][j]>0)
                        {
                            fprintf(arquivo,"%d %d %f\n", i, j, matriz_ruas[i][j]); 
                        }
                    }
                }
                
                fclose(arquivo);
                
                printf("Arquivo salvo com sucesso\n\n");
                
                break;
            }
            case 3: {
                
                int _vertice;
                
                printf("Adicione um vertice: ");
                scanf("%d",&_vertice);
                
                if (_vertice==-1)
                {
                    for (int i=0; i<60; i++)
                    {
                        vertices[i]=true;
                    }
                }
                
                if (vertices[_vertice]==true)
                {
                    printf("Vertice ja existe\n\n");
                }
                else
                {
                    vertices[_vertice]=true;
                    
                    printf("Vertice adicionado\n\n");
                }
                
                break;
            }
            case 4: {
                
                printf("Adicione uma aresta:\n");
                
                int vertice_saida, vertice_entrada;
                float distancia, movimentacao, luminosidade, acidentes, criminalidade;
                
                scanf("%d %d %f %f %f %f %f",&vertice_saida, &vertice_entrada, &distancia, &movimentacao, &luminosidade, &acidentes, &criminalidade);
                
                
                if (!vertices[vertice_saida])
                {
                    printf("Vertice de saida nao existe\n\n");
                }
                else
                if (!vertices[vertice_entrada])
                {
                    printf("Vertice de entrada nao existe\n\n");
                }
                else
                {
                    matriz_ruas[vertice_saida][vertice_entrada] = (10*distancia + 5*movimentacao + 2*luminosidade + 8*acidentes + 9* criminalidade);
                    printf("Aresta adicionada\n\n");
                }
                
                break;
            }
            case 5: {
                
                int _vertice;
                
                printf("Remova um vertice: ");
                scanf("%d",&_vertice);
                
                if (!vertices[_vertice])
                {
                    printf("Vertice nao existe");
                }
                else
                {
                    vertices[_vertice]=false;
                    
                    for (int i=0; i<MAX_VERTICES; i++)
                    {
                        //Zera linha
                        matriz_ruas[_vertice][i]=0;
                        
                        //Zera coluna
                        matriz_ruas[i][_vertice]=0;
                    }
                    
                    printf("Vertice removido\n");
                }
                break;
            }
            case 6: {
                
                printf("Remova uma aresta (saida entrada):\n");
                
                int vertice_saida=0; int vertice_entrada=0;
                scanf("%d %d",&vertice_saida, &vertice_entrada);
                
                if (!vertices[vertice_saida])
                {
                    printf("Vertice de saida nao existe\n\n");
                }
                else
                if (!vertices[vertice_entrada])
                {
                    printf("Vertice de entrada nao existe\n\n");
                }
                else
                {
                    matriz_ruas[vertice_saida][vertice_entrada] = 0;
                    printf("Aresta removida\n\n");
                }
                
                break;
            }
            case 7: {
                
                FILE *arquivo;

                arquivo = fopen("grafo.txt", "r");
                if (arquivo == NULL) {
                    printf("Erro ao abrir o arquivo!\n");
                    return 1;
                }
                
                char caractere;
                while ((caractere = fgetc(arquivo)) != EOF) {
                    printf("%c", caractere);
                }
                
                fclose(arquivo);
                
                break;
            }
            case 8: {
                
                int num_vertices=0;
                
                int vetor_caminho[MAX_VERTICES]={-1};
                
                for (int i=MAX_VERTICES-1; i>=0; i--)
                {
                    if (vertices[i])
                    {
                        num_vertices=i+1;
                        i=-1;
                    }
                }
                
                printa_grafo(matriz_ruas,vertices,num_vertices);
                
                int sum=0;
                for (int i=0; i<num_vertices; i++)
                {
                     for (int j=0; j<num_vertices; j++)
                    {
                        if (matriz_ruas[i][j]!=0)
                        {
                            sum++;
                        }
                    }
                }
                printf(" arestas: %d\n\n",sum);
                
                break;
            }
            case 9: {
                printf("grafo nÃ£o direcionado");
                
                break;
            }
            case 10: {
                
                int num_vertices=0;
                
                int vetor_caminho[MAX_VERTICES]={-1};
                
                for (int i=MAX_VERTICES-1; i>=0; i--)
                {
                    if (vertices[i])
                    {
                        num_vertices=i+1;
                        i=-1;
                    }
                }
                
                int vertice_origem;
                printf("Vertice original: ");
                scanf("%d",&vertice_origem);
                
                int vertice_destino;
                printf("Vertice destino: ");
                scanf("%d",&vertice_destino);
                
                calcular_rota(matriz_ruas, num_vertices, vertice_origem, vertice_destino, vetor_caminho);
                
                int caminho_em_ordem[MAX_VERTICES]={-1};
                int caminho_index=0;
                
                int i=vertice_destino;

                if (vetor_caminho[i]==-1)
                {
                    printf("Sem caminho\n\n");
                }
                else
                {
                    while (i!=vertice_origem)
                    {
                        caminho_em_ordem[caminho_index]=i;
                        caminho_index++;
                        
                        i = vetor_caminho[i];
                        
                    }
                    
                    caminho_em_ordem[caminho_index]=i;
                    
                    for (int i=caminho_index; i>0; i--)
                    {
                        printf("%d -> ",caminho_em_ordem[i]);
                    }
                    
                    printf("%d ",caminho_em_ordem[0]);
                    
                    printf("\n\n");
                }
    
                break;
            }
            // 11, 12 e 13 estudadas na disciplina com a finalidade de descobrir pelo menos três características do problema modelado.
            case 11:
            {
                //mostra_qual_o_grau_kd_vertice
                
                int num_vertices=0;
                
                int vetor_caminho[MAX_VERTICES]={-1};
                
                for (int i=MAX_VERTICES-1; i>=0; i--)
                {
                    if (vertices[i])
                    {
                        num_vertices=i+1;
                        i=-1;
                    }
                }
                
                int graus_entrada[MAX_VERTICES];
                int graus_saida[MAX_VERTICES];
                for (int i=0; i<MAX_VERTICES; i++)
                {
                    for (int j=0; j<MAX_VERTICES; j++)
                    {
                        if (matriz_ruas[i][j] != 0)
                        {
                            graus_saida[i]++;
                            graus_entrada[j]++;
                        }
                    }
                }
                
                printf("vertices:      ");
                for (int i=0; i<num_vertices; i++)
                {
                    if (vertices[i])
                    {
                        printf("%d ", i);
                    }
                    else
                    {
                        printf("X ");
                    }
                }
                printf("\n");
                
                printf("graus entrada: ");
                for (int i=0; i<num_vertices; i++)
                {
                    printf("%d ", graus_entrada[i]);
                }
                
                printf("\n");
                
                printf("graus saida:   ");
                for (int i=0; i<num_vertices; i++)
                {
                    printf("%d ", graus_saida[i]);
                }
                
                printf("\n");
                
                break;
            }
            case 12:
            {
                int num_vertices=0;
                
                int vetor_caminho[MAX_VERTICES]={-1};
                
                for (int i=MAX_VERTICES-1; i>=0; i--)
                {
                    if (vertices[i])
                    {
                        num_vertices=i+1;
                        i=-1;
                    }
                }
                
                n = num_vertices;
                
                for(int i=0; i<MAX_VERTICES; i++)
                {
                    for (int j=0; j<MAX_VERTICES; j++)
                    {
                        adj[i][j]=matriz_ruas[i][j];
                    }
                }
                Kosaraju();
                //mostra_se_e_euleriano
                break;
            }
            default:
            {
                printf("opcao invalida");
            }
            
        }
    }
    
    return 0;
}
