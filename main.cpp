#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdlib>
#define TAM 10


using namespace std;

bool verificaNum(string x){
    if(x == "")
        return false;
    else
    if(!isdigit(x.at(0)))
        return false;
    else
    for(unsigned int i=1; i<x.length(); i++)
        if(!isdigit(x.at(i)))
            return false;
    return true;
}

int menu(){
    int n;
    string x;
    bool valida;
    do{
    system("cls");
    cout << "--------- Acervo de Livros ---------" << endl;
    cout << "1)Inclusao de Livros." << endl;
    cout << "2)Consultar Livros." << endl;
    cout << "3)Excluir um livro" << endl;
    cout << "4)Aquisicao de um Livro." << endl;
    cout << "5)Relatorio do Acervo." << endl;
    cout << "6)Sair." << endl;
    cout << "------------------------------------" << endl;
    cout << "Digite opcao desejada: "; getline(cin, x);
    valida = verificaNum(x);
    }while(!valida);
    n = atoi(x.c_str());
    system("cls");
    return n;
}

int verificada(int cont, string busca, string ISBN[]){
    for(int i=0; i<cont; i++){
        if(busca == ISBN[i]){
         return i;
        }
    }
    return -1;
}

bool verificaISBN(string busca){
    if(busca == ""){
        return false;
    }

    if(busca.size() != 17){
        return false;
    }
    if(!isdigit(busca.at(0))){
       return false;
    }
    if(busca.at(3) != '-' and busca.at(5) != '-' and busca.at(8) != '-' and busca.at(15) != '-')
        return false;

    return true;
}

bool verificaNome(string nome){
    if(nome=="")
        return false;
    for(unsigned int i=0; i<nome.length(); i++)
        if(!isalpha(nome.at(i)) and nome.at(i)!=' ')
            return false;
    return true;
}

void transformaAutor(string auxNome, char &sigla1, char &sigla2, string &ultNome){
    unsigned int i = auxNome.size() -1, j=0;
    string somaNome, excessoes[5] = {"do", "dos", "da", "das", "de"};
    bool validade = true;

    ultNome = "";
    sigla1 = toupper(auxNome.at(0));
    while(auxNome.at(i) != ' '){
        i--;
    }
    for(unsigned int j = i+1; j < auxNome.size(); j++){
        ultNome += toupper(auxNome.at(j));
    }

    i=0;
    while(auxNome.at(i) != ' '){
        i++;
    }

    j = i + 1;
    while(auxNome.at(j) != ' '){
        somaNome += auxNome.at(j);
        j++;
    }
    for(int z=0; z<5; z++){
        if(somaNome == excessoes[z]){
            sigla2 = toupper(auxNome.at(j+1));
            validade = false;
        }
    }

    if(validade){
        sigla2 = toupper(auxNome.at(i+1));
    }
}


void ordenacaoAlfabetica(int cont, string titulos[], string autores[], string editoras[], string ISBN[], int quantidade[]){
    int j;
    int i, auxQuanti, pos;
    string auxTitulo, auxAutor, auxEditora, auxISBN;

    for(i = 0; i<=cont-1; i++){
        pos = i;
        for(j=i+1; j<=cont-1; j++){
            if(titulos[j] < titulos[pos]){
                pos = j;
            }
        }
        auxTitulo = titulos[pos];
        auxAutor = autores[pos];
        auxEditora = editoras[pos];
        auxISBN = ISBN[pos];
        auxQuanti = quantidade[pos];
        titulos[pos] = titulos[i];
        autores[pos] = autores[i];
        editoras[pos] = editoras[i];
        ISBN[pos] = ISBN[i];
        quantidade[pos] = quantidade[i];
        titulos[i] = auxTitulo;
        autores[i] = auxAutor;
        editoras[i] = auxEditora;
        ISBN[i] = auxISBN;
        quantidade[i] = auxQuanti;
    }
}



void opcao1(int &cont, string titulos[], string autores[], string editoras[], string ISBN[], int quantidade[]){
    int isbnPosicao;
    string busca, quantidades, nome, nomeLivro;
    bool valida;
        do{
        system("cls");
        cout << "--------- Inclusao de Livros ---------" << endl;
        cout << "\nDigite a ISBN do livro: "; getline(cin,busca);
        valida = verificaISBN(busca);
        }while(!valida);
        isbnPosicao = verificada(cont, busca, ISBN);
        if(isbnPosicao == -1){
        ISBN[cont] = busca;
        do{
        cout << "\nDigite o titulo do livro: "; getline(cin, nomeLivro);
        valida = verificaNome(nomeLivro);
        }while(!valida);
        titulos[cont] = nomeLivro;
        do{
        cout << "\nDigite o autor do livro: "; getline(cin, nome);
        valida = verificaNome(nome);
        }while(!valida);
        autores[cont] = nome;
        cout << "\nDigite a editora do livro: "; getline(cin,editoras[cont]);
        do{
        cout << "\nDigite a quantidade de exemplares: "; getline(cin, quantidades);
        valida = verificaNum(quantidades);
        }while(!valida);
        quantidade[cont] = atoi(quantidades.c_str());
        cout << "====================================" << endl;
        cout << "Livro adicionado com sucesso!" << endl;
        cout << "====================================" << endl;
        cont++;
        }else{
            cout << "===================" << endl;
            cout << "Livro existe!!!" << endl;
            cout << "===================" << endl;
        }
        cout << "Aperte [ENTER] para voltar ao menu: ";
        getchar();
}

void opcao2(int cont, string titulos[], string autores[], string editoras[], string ISBN[], int quantidade[]){
    int isbnPosicao;
    string busca;
    bool valida;

    do{
    cout << "--------- Busca de Livros ---------";
    cout << "\nDigite o ISBN do livro que deseja buscar: "; getline(cin, busca);
    valida = verificaISBN(busca);
    }while(!valida);
    isbnPosicao = verificada(cont, busca, ISBN);
        if(busca == ISBN[isbnPosicao]){
            cout << "\nISBN do Livro: " << ISBN[isbnPosicao];
            cout << "\nTitulo do Livro: " << titulos[isbnPosicao];
            cout << "\nAutor do Livro: " << autores[isbnPosicao];
            cout << "\nEditora do Livro: " << editoras[isbnPosicao];
            cout << "\nQuantidade de exemplares: " << quantidade[isbnPosicao] << endl;
        }else{
            cout << "=======================================" << endl;
            cout << "Livro NAO ENCONTRADO!" << endl;
            }
            cout << "=======================================" << endl;
            cout << "Aperte [ENTER] para voltar ao menu: " ;
            getchar();
}

void opcao3(int &cont, string titulos[], string autores[], string editoras[], string ISBN[], int quantidade[]){
    int isbnPosicao;
    string busca;
    bool valida;
    do{
        cout << "--------- Exclusao de Livros ---------";
        cout << "\nDigite o ISBN do livro que deseja EXCLUIR: "; getline(cin, busca);
        valida = verificaISBN(busca);
    }while(!valida);
        isbnPosicao = verificada(cont, busca, ISBN);
            if(busca == ISBN[isbnPosicao]){
                for(int i = isbnPosicao; i<cont; i++){
                    titulos[i] = titulos[i+1];
                    autores[i] = autores[i+1];
                    editoras[i] = editoras[i+1];
                    ISBN[i] = ISBN[i+1];
                    quantidade[i] = quantidade[i+1];
                }
                titulos[cont] = "";
                autores[cont] = "";
                editoras[cont] = "";
                ISBN[cont] = "";
                quantidade[cont] = 0;
                cont --;
                cout << "Livro EXCLUIDO!" << endl;
            }else{
                cout << "=======================================" << endl;
                cout << "Livro NAO ENCONTRADO!" << endl;
                }
                cout << "=======================================" << endl;
                cout << "Aperte [ENTER] para voltar ao menu: " ;
                getchar();

}

void opcao4(int &cont, string titulos[], string autores[], string editoras[], string ISBN[], int quantidade[]){
   char resp;
   int isbnPosicao, transformaQuant;
   string busca, quant;
   bool valida;
    do{
        cout << "--------- Busca de Exemplares ---------";
        cout << "\nDigite o ISBN do livro: "; getline(cin, busca);
        valida = verificaISBN(busca);
    }while(!valida);
    isbnPosicao = verificada(cont, busca, ISBN);
        if(busca == ISBN[isbnPosicao]){
            cout << "Nome de Livro: " << titulos[isbnPosicao] << endl;
            cout << "Autor e Editora: " << autores[isbnPosicao] << " / " << editoras[isbnPosicao] << endl;
            cout << "Quantidade: " << quantidade[isbnPosicao] << endl;
            cout << "Adquirir mais exemplares [S/N]? "; cin >> resp;
            if(resp == 'S' or resp == 's'){
                cin.ignore();
                do{
                cout << "\nQuantidade de exemplares que deseja adquirir: "; getline(cin, quant);
                valida = verificaNum(quant);
                }while(!valida);
                transformaQuant = atoi(quant.c_str());
                quantidade[isbnPosicao] += transformaQuant;
                cout << "\nExemplares incluidos!" << endl;
                getchar();
                }else{
                    cout << "Voltando ao menu..." << endl;
                    getchar();
                }
            }else{
                cout << "=======================================" << endl;
                cout << "Livro NAO ENCONTRADO!" << endl;
                 cout << "=======================================" << endl;
                cout << "Aperte [ENTER] para voltar ao menu: " ;
                getchar();

            }

            cout << "=======================================" << endl;
            cout << "Aperte [ENTER] para voltar ao menu: " ;
            getchar();
}

void opcao5(int cont, string titulos[], string autores[], string editoras[], string ISBN[], int quantidade[]){
    string ultNome, auxNome;
    char sigla1, sigla2;

    ordenacaoAlfabetica(cont, titulos, autores, editoras, ISBN, quantidade);
    cout << "------------ Relatorio ------------" << endl;
    for(int i=0; i<cont; i++){
        cout << i+1 << "o. Livro: ";
        cout << "\nISBN do Livro: " << ISBN[i];
        cout << "\nTitulo do Livro: " << titulos[i] << endl;
        auxNome = autores[i];
        transformaAutor(auxNome, sigla1, sigla2, ultNome);
        cout << "Autor: " << ultNome << ", " << sigla1 << "." << sigla2;
        cout << "\nEditora do Livro: " << editoras[i];
        cout << "\nQuantidade de exemplares: " << quantidade[i] << endl;
        cout << "=====================================" << endl;
    }
    cout << "\nAperte [ENTER] para voltar ao menu: " ;
    getchar();

}

int main()
{
   int opcao, quantidade[TAM], cont=0;
   string titulo[TAM], autor[TAM], editora[TAM], ISBN[TAM];

   do{
   opcao = menu();
   switch(opcao){
case 1:
    opcao1(cont, titulo, autor, editora, ISBN, quantidade);
    break;
case 2:
    opcao2(cont, titulo, autor, editora, ISBN, quantidade);
    break;
case 3:
    opcao3(cont, titulo, autor, editora, ISBN, quantidade);
    break;
case 4:
    opcao4(cont, titulo, autor, editora, ISBN, quantidade);
    break;
case 5:
    opcao5(cont, titulo, autor, editora, ISBN, quantidade);
    break;
    }
 }while(opcao != 6);

}
