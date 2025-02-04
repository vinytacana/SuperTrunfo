#include <iostream>
#include <fstream>
using namespace std;

struct Carta
{
    char nome[20];
    unsigned int jogos;
    unsigned int gols;
    unsigned short titulos;
};
const int MaxCartas = 32;

void cadastrarCarta(Carta baralho[], int &totalCartas)
{
    if (totalCartas >= MaxCartas)
    {
        cout << "nao foi possivel inserir, vetor cheio;" << endl;
        return;
    }
    cout << "Insira o nome do jogador: ";
    cin.ignore();
    cin.getline(baralho[totalCartas].nome, 20);

    cout << "Insira a quantidade de jogos que seu jogador teve: ";
    cin >> baralho[totalCartas].jogos;

    cout << "Insira a quantidade de gols do jogador: ";
    cin >> baralho[totalCartas].gols;

    cout << "Insira a quantidade de títulos do jogador: ";
    cin >> baralho[totalCartas].titulos;

    totalCartas++;
    cout << "Carta cadastrada com sucesso!" << endl;
}
void listarCartas(Carta baralho[], int totalCartas)
{
    if (totalCartas == 0)
    {
        cout << "Nenhuma carta cadastrada.\n";
        return;
    }

    cout << "\nCartas no Baralho:\n";
    for (int i = 0; i < totalCartas; i++)
    {
        cout << "#" << i + 1 << " " << baralho[i].nome << " | "
             << baralho[i].jogos << " jogos | "
             << baralho[i].gols << " gols | "
             << baralho[i].titulos << " títulos\n";
    }
}
void import(Carta baralho[], int &totalCartas){
    ifstream fin;
     fin.open("maiscartas.txt");

    for(int i=0;i<totalCartas;i++){
        while(fin>> baralho[i].nome >> baralho[i].jogos>> baralho[i].gols>>baralho[i].titulos){
            
        }
    }
}

int main()
{
    Carta baralho[MaxCartas];
    int totalCartas = 0;
    int opcao;

    do
    {
        cout << "\n--- Gerador de Cartas ---\n";
        cout << "1- Cadastrar Carta\n";
        cout << "2- Listar Cartas\n";
        cout << "0- Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            cadastrarCarta(baralho, totalCartas);
            break;
        case 2:
            listarCartas(baralho, totalCartas);
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }

    } while (opcao != 0);
    return 0;
}