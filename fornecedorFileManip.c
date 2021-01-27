#include <stdio.h>
#include <string.h>
#include "fornecedorFileManip.h"
#include "structDeclarations.h"
#include "utilityFunctions.h"

void cadastro_fornecedor(FILE *arq, int *id){
    char cnpj[15];
    int sair = 1;
    fornecedor new;
    
    do{
        do{
            printf("\nDigite o CNPJ do fornecedor a ser cadastrado: ");
			setbuf(stdin,NULL);
            fgets(cnpj,sizeof(cnpj),stdin);
            check_newline(cnpj);
        }while(validarCNPJ(cnpj)==0);

        if(pesquisa_frncdr_CNPJ(arq,cnpj)==-1){
            strcpy(new.cnpj, cnpj);
			printf("valor que será inserido: %s",new.cnpj); //TESTING PURPOSES
            printf("\nDigite o nome do fornecedor: ");
			setbuf(stdin,NULL);
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
			printf("valor que será inserido: %s",new.nome); //TESTING PURPOSES
            printf("\nDigite o email do fornecedor: ");
			setbuf(stdin,NULL);
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
			printf("valor que será inserido: %s",new.email); //TESTING PURPOSES
            printf("\nDigite o telefone do fornecedor: ");
			setbuf(stdin,NULL);
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("valor que será inserido: %s",new.telefone); //TESTING PURPOSES
            setbuf(stdin,NULL);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(fornecedor),1,arq);
        }
        else
            printf("\nCNPJ já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Fornecedor\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
    }while(sair!=2);
}

void listar_fornecedores(FILE *arq){
    fornecedor r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Clientes");
    printf("\nID\t\tNOME\t\t\t\tCNPJ\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(cliente),1,arq))
        printf("\n%lu\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.nome,r.cnpj,r.email,r.telefone);
}

int pesquisa_frncdr_CNPJ(FILE *arq,char* cnpj){
    fornecedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(fornecedor),1,arq)==1){
    	if(strcmp(r.cnpj,cnpj)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}
