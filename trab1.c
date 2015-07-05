#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MV 50
#define MP 500

	typedef struct {
		float pvpl[200];
	} depart;

int abrirArquivo(FILE *arq, char caminhoarquivo[MV]) //identificar se o arquivo existe ou não
{	
	arq = fopen(caminhoarquivo,"r");
	
	if(arq==NULL){
	printf("Arquivo Não Encontrado\n");
	return 0;}
	
	else	return 1;	
}
	   

int processaEntrada (FILE *arq, char caminhoarquivo[MV],depart departamento[MP],int v[MP], int *quantdepartamentos)
{	
	int valor;
	int quantidade[100];
	int qtotal=0;
	float lucro;
	int fimq = 0,fimv=0,fimp=0,fimd=0;
	int i=0,j=0,h=0,k=0;
	int mj=0,mh=0;
	int o=0; //criada pra guardar quantos espaços H serão usados em cada struct
	*quantdepartamentos=0;
	
	arq = fopen(caminhoarquivo,"r");
	
	while(fimd != -1){ //Encerra Departamentos
	fscanf(arq,"%d",&k); // k é o numero do departamento
	fimd = k;
	
		if(k != -1){
		
			while(fimp != -1){ //Encerra os Produtos do Departamento
			fscanf(arq,"%f",&departamento[*quantdepartamentos].pvpl[h]); // pergunta produto
			fimp = departamento[*quantdepartamentos].pvpl[h];
			
			if(mh>MP){ //Verifica se o numero de produtos do arquivo atinge o maior que o permitido.
								printf("Numero de Produtos Excedido. Conserte o Arquivo e Reinicie o Programa\n");
								fimq=-1; fimp=-1; fimv=-1; fimd=-1; return 0;}
			else{
				mh++;
				if(fimp != -1){
				fscanf(arq,"%d",&valor);
				fscanf(arq,"%f",&lucro);
				
					if(departamento[*quantdepartamentos].pvpl[h] != -1){
					h++;
					
						while(fimv != -1){ //Encerra os Vendedores do Departamento
						fscanf(arq,"%f",&departamento[*quantdepartamentos].pvpl[h]); //pergunta vendedor
						fimv = departamento[*quantdepartamentos].pvpl[h];
						
							if(departamento[*quantdepartamentos].pvpl[h] != -1){
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
								departamento[*quantdepartamentos].pvpl[h]=qtotal;
								h++;
								departamento[*quantdepartamentos].pvpl[h]=qtotal*valor;
								h++;
								departamento[*quantdepartamentos].pvpl[h]=departamento[*quantdepartamentos].pvpl[h-1]*lucro;
								h++;
								fimq=0; qtotal=0; i=0;
								}
							}  departamento[*quantdepartamentos].pvpl[h]=departamento[*quantdepartamentos].pvpl[h-4]; h++;
											
						}
						fimv=0; j=0;
					}
				}
			}
			}
			fimp=0;v[o]=h-2; o++; h=0; 
		} *quantdepartamentos=*quantdepartamentos+1;
	} *quantdepartamentos=*quantdepartamentos-2;
	fimd=0; k=0;
	fclose(arq);
	return 1;
}

void vendasValor(depart departamento[MP],int v[MP], int *quantdepartamentos){
int vendedorproduto[100];
int n,k;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM PREÇO E VENDEDOR!
	for (k=3;k<v[n];k=k+5){
		vendedorproduto[i]=departamento[n].pvpl[k]; //passaando valor do preço
		i++;
		vendedorproduto[i]=departamento[n].pvpl[k-2]; // passando valor do vendedor
		i++;
		w++; // Conta a quantidade de vendedores
	}
}
for (n=0;n<=*quantdepartamentos;n++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[n]*2)/5;n=n+2){
			if (vendedorproduto[n]<vendedorproduto[n+2]){
				k=vendedorproduto[n];
				vendedorproduto[n]=vendedorproduto[n+2];
				vendedorproduto[n+2]=k;
				k=vendedorproduto[n+1];
				vendedorproduto[n+1]=vendedorproduto[n+3];
				vendedorproduto[n+3]=k;
			}
		}
	}
}
for (n=0;n<2*w;n=n+2)
	printf ("Vendedor %d  -  R$ %d\n", vendedorproduto[n+1], vendedorproduto[n]);
}
void vendasQuantidade(depart departamento[MP],int v[MP], int *quantdepartamentos){
int vendedorproduto[100];
int n,k;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM PREÇO E VENDEDOR!
	for (k=2;k<v[n];k=k+5){
		vendedorproduto[i]=departamento[n].pvpl[k]; //passaando valor do preço
		i++;
		vendedorproduto[i]=departamento[n].pvpl[k-1]; // passando valor do vendedor
		i++;
		w++; // Conta a quantidade de vendedores
	}
}
for (n=0;n<=*quantdepartamentos;n++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[n]*2)/5;n=n+2){
			if (vendedorproduto[n]<vendedorproduto[n+2]){
				k=vendedorproduto[n];
				vendedorproduto[n]=vendedorproduto[n+2];
				vendedorproduto[n+2]=k;
				k=vendedorproduto[n+1];
				vendedorproduto[n+1]=vendedorproduto[n+3];
				vendedorproduto[n+3]=k;
			}
		}
	}
}
for (n=0;n<2*w;n=n+2)
	printf ("Vendedor %d  -  Quantidade total de vendas %d\n", vendedorproduto[n+1], vendedorproduto[n]);

}
void produtoValor(depart departamento[MP],int v[MP], int *quantdepartamentos){
int produtovalor[100];
int n,k;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM PREÇO E VENDEDOR!
	for (k=3;k<v[n];k=k+5){
		produtovalor[i]=departamento[n].pvpl[k]; //passaando valor do preço
		i++;
		produtovalor[i]=departamento[n].pvpl[k-3]; // passando valor do vendedor
		i++;
		w++; // Conta a quantidade de vendedores
	}
}
for (n=0;n<=*quantdepartamentos;n++){ //JUNTAR PRODUTOS REPETIDOS
	for (i=1;i<=(float)((v[n]*2)/5);i=i+2){
		for (k=1;k<=(float)((v[n]*2)/5);k++){
			if (produtovalor[i]==produtovalor[i+(2*k)]){
				produtovalor[i-1]=produtovalor[i-1]+produtovalor[i+(2*k)-1];
				produtovalor[i+(2*k)]=0;
				produtovalor[i+(2*k)-1]=0;
				w=w-1;
			}
		}
	}
}
for (n=0;n<=*quantdepartamentos;n++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[n]*2)/5;n=n+2){
			if (produtovalor[n]<produtovalor[n+2]){
				k=produtovalor[n];
				produtovalor[n]=produtovalor[n+2];
				produtovalor[n+2]=k;
				k=produtovalor[n+1];
				produtovalor[n+1]=produtovalor[n+3];
				produtovalor[n+3]=k;
			}
		}
	}
}

for (n=0;n<2*w;n=n+2)
	printf ("Produto %d  -  R$ %d\n", produtovalor[n+1], produtovalor[n]);

}
void produtoLucro(depart departamento[MP],int v[MP], int *quantdepartamentos){
int produtovalor[100];
int n,k;
int i=0;
int w=0;
for (n=0;n<=*quantdepartamentos;n++){ //ORGANIZAR UM VETOR SOMENTE COM PREÇO E VENDEDOR!
	for (k=4;k<v[n];k=k+5){
		produtovalor[i]=departamento[n].pvpl[k]; //passaando valor do preço
		i++;
		produtovalor[i]=departamento[n].pvpl[k-4]; // passando valor do vendedor
		i++;
		w++; // Conta a quantidade de vendedores
	}
}
for (n=0;n<=*quantdepartamentos;n++){ //JUNTAR PRODUTOS REPETIDOS
	for (i=1;i<=(float)((v[n]*2)/5);i=i+2){
		for (k=1;k<=(float)((v[n]*2)/5);k++){
			if (produtovalor[i]==produtovalor[i+(2*k)]){
				produtovalor[i-1]=produtovalor[i-1]+produtovalor[i+(2*k)-1];
				produtovalor[i+(2*k)]=0;
				produtovalor[i+(2*k)-1]=0;
				w=w-1;
			}
		}
	}
}
for (n=0;n<=*quantdepartamentos;n++){
	for (i=0;i<50;i++){ //TECNICA DA BOLHA PRA ORDERNAR
		for (n=0;n<=(float)(v[n]*2)/5;n=n+2){
			if (produtovalor[n]<produtovalor[n+2]){
				k=produtovalor[n];
				produtovalor[n]=produtovalor[n+2];
				produtovalor[n+2]=k;
				k=produtovalor[n+1];
				produtovalor[n+1]=produtovalor[n+3];
				produtovalor[n+3]=k;
			}
		}
	}
}

for (n=0;n<2*w;n=n+2)
	printf ("Produto %d  -  Lucro obtido R$ %d\n", produtovalor[n+1], produtovalor[n]);
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
	depart vetor[MP];
	int dado1[MP]; // indica ate que numero cada struct foi usado internamente
	int quantdepusados; //Vai marcar quantos structs(departamentos) foram usados
	
	if (abrirArquivo(arqEntrada,caminhoarquivo) && processaEntrada(arqEntrada,caminhoarquivo,vetor, dado1, &quantdepusados) == 1){
	
		do{//Exibir menu
			switch(menu()){
				
			case 1: //Ranking Total de Vendas
				vendasValor(vetor,dado1,&quantdepusados);										break;
			case 2: //Ranking Quantidade de Vendas
				vendasQuantidade(vetor,dado1,&quantdepusados);									break;
			case 3: //Lista Produtos por Valor
				produtoValor(vetor,dado1,&quantdepusados);										break;
			case 4: //Lista Produtos por Lucro
				produtoLucro(vetor,dado1,&quantdepusados);										break;
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
