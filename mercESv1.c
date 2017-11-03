#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/* Nome do programa: MercES v1.
   Autor: Gustavo H. N. Santos.
   Data: 24/02/2017.
   Fun��o Global:
    - Este software � para um super mercado, para consultar, inserir produto no estoque e
	vender suas mercadorias inseridas.
   Linguagem de Implementa��o: C. */

typedef struct{
	int cod, qtd; char nome[30]; float preco;
}Produto; // Estrutura de produto.
// Variavel Global de produto.
Produto produto[99];
// Prototipos de fun��o.
void inserirProduto (float *saldo, int MAX);
void imprimirProduto(int MAX1);
void venda (float *saldo, float *venda, int MAX2);
// Fun��o principal
int main()	
{
	int i, MAXX=0, opcao=1, qtdV;
	float saldo=3000.00/*Saldo inicial de 3000 reais.*/, saldo_caixa=0;
	setlocale (LC_ALL, "Portuguese");
	// Inicio do menu com as op��es.
	do{
		system("clear || cls");// Limpar a tela sempre que voltar para o menu.
		printf("\tEscolha uma Op��o:\n");
	   	printf("\t1 - Inserir produto no Estoque.\n");
		printf("\t2 - Venda.\n");
		printf("\t3 - Saldo.\n");
		printf("\t4 - Consultar estoque.\n");
		printf("\t0 - Sair.\n");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1: 
				printf("Digite quantos produtos ser�o inseridos: \n"); 
				scanf("%d", &MAXX);// Aqui � pra saber quantos produtos vai estar no estoque.
				inserirProduto(&saldo, MAXX);// Chamando fun��o inserir produto
				system("PAUSE");
				getchar();
				break; 
			case 2:
				printf("Digite quantas vendas sera feita: \n"); // Verifica quantas vezes vai ser executada a fun��o venda
				scanf("%d", &qtdV);
				for(i=0; i<qtdV; i++)
				{
					venda(&saldo, &saldo_caixa, MAXX);// Chamando fun��o venda e retornando os 2 saldos.
                                                      // *Saldo total do dono.
                                                      // *Saldo_caixa saldo do caixa.
				}
				system("PAUSE");
				getchar();
				break;
			case 3:
	   	   		printf("Saldo: %3.2f\n", saldo);// Do dono.
	   	   		printf("Saldo do caixa: %3.2f\n", saldo_caixa); //  Saldo do caixa.
	   	   		system("PAUSE");
	   	   		getchar();
   	   			break;
   	   		case 4:
				imprimirProduto(MAXX);//Fun��o para imprimir todo o estoque.
				system("PAUSE");
				getchar();
				break;
			case 0:
                printf("Saindo do sistema.");// value 0, programa finalizado.
                break;	
			default:	
				printf("Codigo invalido!\n");
				break;	
		}			
    }while(opcao);
	
	return 0;
}
//Inicio das fun��es.
void inserirProduto (float *saldo, int MAX)
{/* Nessa fun��o vai inserir os valores na struct Produto. */
	int i;
	for(i=0; i<MAX; i++)
	{
		//Inserindo valores do produto.
		fflush(stdin);
		printf("Nome do produto:\n"); 
		fgets(produto[i].nome,30, stdin);// fgets para poder dar espa�o.
		
		printf("Quantidade do produto:\n"); 
		scanf("%d", &produto[i].qtd);
		 
		printf("Codigo do produto:\n"); 
		scanf("%d", &produto[i].cod);
		 
		printf("Pre�o do produto:\n"); 
		scanf("%f", &produto[i].preco);
		 
		*saldo= *saldo - (produto[i].qtd * produto[i].preco); // Est� retirando o valor do produto do saldo.
													         //  Saldo em ponteiro.
    }
}
void imprimirProduto (int MAX1)
{
	/* Aqui imprimira todo o estoque */
	int i;
	for(i=0; i<MAX1; i++)
	{
		printf("Produto: %s \tCodigo do produto: %d \n\tPre�o: %3.2f\n\tQuantidade: %d\n\n", produto[i].nome, produto[i].cod, produto[i].preco, produto[i].qtd);
	}
}
void venda (float *saldo, float *venda, int MAX2)
{
	/* Nessa fun��o ira primeiro colocar os valores de codigo do produto e quantidade,
	   Logo apos ele ira verificar se tem o produto no estoque, e depois mostrara as informa��es do produto,
	   E depois verifica se tem a quantidade necessario pra venda. */
	int i, cod, qtd, vendas=2;
	system("clear || cls");// Limpar a tela
	imprimirProduto(MAX2);
	while(vendas){
	printf("Insira o numero do cod do produto: \n");
	scanf("%d", &cod);
	
	printf("Insira a quantidade de produto: \n"); 
	scanf("%d", &qtd);
	for(i=0; i<MAX2; i++)
	{
		if(produto[i].cod==cod && qtd<=produto[i].qtd)// verifica o codigo do produto.
		{
			printf("Nome: %s", produto[i].nome);
			
			printf("\tPre�o: %3.2f\n\t", produto[i].preco);
			
			printf("Quantidade: %d\n", produto[i].qtd);
			
			printf("\tVenda feita com sucesso\n\n");
				
			produto[i].qtd = produto[i].qtd - qtd;
				
			*venda=*venda + (produto[i].preco*qtd);// Guarda o valor vendido. Saldo do caixa.
				
			*saldo=*saldo + (0.25*(produto[i].preco*qtd));//Acrescenta 25% no saldo em cima do valor do produto vendido.
			vendas=0;
		}
		else if(produto[i].cod<cod)
			vendas=0;
		else
			{
				printf("Quantidade insuficiente no estoque.\n\n");// Se n�o tiver a quantidade no estoque a venda j� � finalizada.
				vendas=1;
			}
	}
}	
}