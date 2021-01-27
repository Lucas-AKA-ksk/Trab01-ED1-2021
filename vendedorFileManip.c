#include <stdio.h>
#include <string.h>
#include "vendedorFileManip.h"
#include "structDeclarations.h"
#include "utilityFunctions.h"

void cadastro_vendedor(FILE *arq, int *id){
    char cpf[12];
    int sair = 1;
    vendedor new;
    
    do{
        do{
            printf("\nDigite o CPF do vendedor a ser cadastrado: ");
			setbuf(stdin,NULL);
            fgets(cpf,sizeof(cpf),stdin);
            check_newline(cpf);
        }while(validarCPF(cpf)==0);

        if(pesquisa_vnddr_CPF(arq,cpf)==-1){
            strcpy(new.cpf, cpf);
			printf("valor que será inserido: %s",new.cpf); //TESTING PURPOSES
            printf("\nDigite a matricula do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.matricula, sizeof(new.matricula),stdin);
            check_newline(new.matricula);
            printf("valor que será inserido: %s",new.matricula); //TESTING PURPOSES
            printf("\nDigite o nome do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.nome, sizeof(new.nome),stdin);
            check_newline(new.nome);
			printf("valor que será inserido: %s",new.nome); //TESTING PURPOSES
            printf("\nDigite o email do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.email, sizeof(new.email),stdin);
            check_newline(new.email);
			printf("valor que será inserido: %s",new.email); //TESTING PURPOSES
            printf("\nDigite o telefone do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.telefone, sizeof(new.telefone),stdin);
            check_newline(new.telefone);
			printf("valor que será inserido: %s",new.telefone); //TESTING PURPOSES
            setbuf(stdin,NULL);
            printf("\nDigite a senha do vendedor: ");
			setbuf(stdin,NULL);
            fgets(new.password, sizeof(new.password),stdin);
            check_newline(new.password);
            printf("valor que será inserido: %s",new.password); //TESTING PURPOSES
            setbuf(stdin,NULL);
            new.id = *id;
			printf("\nValor da ID: %lu",new.id);
			(*id)++;
            fseek(arq,0,SEEK_END);
            fwrite(&new,sizeof(vendedor),1,arq);
        }
        else
            printf("\nCPF já cadastrado!! Operação cancelada!!");
        printf("\nDeseja Cadastrar outro Vendedor?\n\n1->Sim\t2->Não");
        scanf("%d",&sair);
    }while(sair!=2);
}

void listar_vendedores(FILE *arq){
    vendedor r;
    fseek(arq,0,SEEK_SET);
    printf("\nListagem de Vendedores");
    printf("\nID\t\tMATRICULA\t\tNOME\t\t\t\tCPF\t\tEMAIL\t\t\tTELEFONE");
    while(fread(&r,sizeof(vendedor),1,arq))
        printf("\n%lu\t\t%s\t\t%s\t\t\t\t%s\t\t%s\t\t\t%s",r.id,r.matricula,r.nome,r.cpf,r.email,r.telefone);
}

int pesquisa_vnddr_CPF(FILE *arq,char* cpf){
   	vendedor r;
   	int posicao=0;
   	fseek(arq,0,SEEK_SET);
   	
   	while(fread(&r,sizeof(vendedor),1,arq)==1){
    	if(strcmp(r.cpf,cpf)==0)
        	return posicao;
      	else
         	posicao++;
   	}
   	return -1;
}
