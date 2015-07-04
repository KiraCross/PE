#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MV 50
#define MP 500

int abrirArquivo(FILE *arq, char caminhoarquivo[MV]) //identificar se o arquivo existe ou não
{	
	arq = fopen(caminhoarquivo,"r");
	
	if(arq==NULL){
	printf("Arquivo Não Encontrado\n");
	return 0;}
	
	else	return 1;	
}
	   

int processaEntrada (FILE *arq, char caminhoarquivo[MV])
{	
	typedef struct {
		float pvpl[200];
	} depart;
	depart departamento[MP];
	int valor;
	int quantidade[100];
	int qtotal=0;
	float lucro;
	int fimq = 0,fimv=0,fimp=0,fimd=0;
	int i=0,j=0,h=0,k=0;
	int mj=0,mh=0;
	int v[MV],o=0; //criada pra guardar quantos espaços H serão usados em cada struct
	
	
	arq = fopen(caminhoarquivo,"r");
	
	while(fimd != -1){ //Encerra Departamentos
	fscanf(arq,"%d",&k); // k é o numero do departamento
	fimd = k;
	
		if(k != -1){
		
			while(fimp != -1){ //Encerra os Produtos do Departamento
			fscanf(arq,"%f",&departamento[k].pvpl[h]); // pergunta produto
			fimp = departamento[k].pvpl[h];
			
			if(mh>MP){ //Verifica se o numero de produtos do arquivo atinge o maior que o permitido.
								printf("Numero de Produtos Excedido. Conserte o Arquivo e Reinicie o Programa\n");
								fimq=-1; fimp=-1; fimv=-1; fimd=-1; return 0;}
			else{
				mh++;
				if(fimp != -1){
				fscanf(arq,"%d",&valor);
				fscanf(arq,"%f",&lucro);
				
					if(departamento[k].pvpl[h] != -1){
					h++;
					
						while(fimv != -1){ //Encerra os Vendedores do Departamento
						fscanf(arq,"%f",&departamento[k].pvpl[h]); //pergunta vendedor
						fimv = departamento[k].pvpl[h];
						
							if(departamento[k].pvpl[h] != -1){
								if(mj>MV){ //Verifica se o numero de vendedores do arquivo atinge o maior que o permitido.
								printf("Numero de Vendedores Excedido. Conserte o Arquivo e Reinicie o Programa\n");
								fimq=-1; fimp=-1; fimv=-1; fimd=-1; return 0;}
								else{
								mj++; h++;
												
									while(fimq != -1){ //Encerra a leitura de Quantidades e Passa pro proximo Vendedor Caso Encontre o Valor -1
										fscanf(arq,"%d",&quantidade[i]);
										fimq = quantidade[i];
										
										if (quantidade[i] != -1){
									    qtotal = qtotal + quantidade[i];
										i++;
										}

									}
								departamento[k].pvpl[h]=qtotal*valor;
								h++;
								departamento[k].pvpl[h]=departamento[k].pvpl[h-1]*lucro;
								h++;
								fimq=0; qtotal=0; i=0;
								}
							}  departamento[k].pvpl[h]=departamento[k].pvpl[h-4]; h++;
											
						}
						fimv=0; j=0;
					}
				}
			}
			}
			fimp=0;v[o]=h; o++; h=0;
		}
	}
	fimd=0; k=0;

for (k=1; k<=2;k++){
	for (h=0; h<v[0]; h++){
		printf ("%.2f\n",departamento[k].pvpl[h]);
	}
}
	fclose(arq);
	return 1;

}

void vendasValor(){

}
void vendasQuantidade(){

}
void produtoValor(){
	
}
void produtoLucro(){
	
}

int menu (){ //Responsável pela impressão do menu
	int op;
	fflush(stdin);
	printf("|=========================================================================|\n");
	printf("|===================================MENU==================================|\n");
	printf("|=========================================================================|\n");
	printf("|==   1.Ranking de Vendedores Decrescente Pelo Valor Total de Vendas    ==|\n");
	printf("|==   2.Ranking de Vendedores Decrescente Pela Quantidade de Vendas     ==|\n");
	printf("|==   3.Lista de Produtos Decrecente Pelo Valor Total de Vendas         ==|\n");
	printf("|==       4.Lista de Produtos Decrescente Pelo Lucro Obtido             ==|\n");
	printf("|==                              0. Sair                                ==|\n");
	printf("|=========================================================================|\n");
	printf("\nDigite uma opção do menu: ");	scanf("%d",&op);

	return op;
}


int main()
{
	FILE *arqEntrada=NULL;
	char caminhoarquivo[50]="C:\\Users\\Renato\\Desktop\\entrada.txt";
	int k=1;
	
	if (abrirArquivo(arqEntrada,caminhoarquivo) && processaEntrada(arqEntrada,caminhoarquivo) == 1){

	
		do{//Exibir menu
			switch(menu()){
				
			case 1: //Ranking Total de Vendas
				vendasValor();										break;
			case 2: //Ranking Quantidade de Vendas
				vendasQuantidade();									break;
			case 3: //Lista Produtos por Valor
				produtoValor();										break;
			case 4: //Lista Produtos por Lucro
				produtoLucro();										break;
			case 0: //Sair
				printf("PROGRAMA FINALIZADO \n\n"); k=0;			break;
			default://Numero Inválido
				printf("Numero Inválido, repita a operação\n\n");	break;
		}
	}while(k!=0);
	} 
	
	else printf("PROGRAMA FINALIZADO \n\n");

	return 0;
}
