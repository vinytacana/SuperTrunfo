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
             << baralho[i].titulos << " titulos\n";
    }
}
void import(Carta baralho[], int &totalCartas)
{
    ifstream fin;
    char path[100];
    cout << "insira o caminho do arquivo: " << endl;
    cin.ignore();
    cin.getline(path, 100);
    fin.open(path);
    if (!fin.is_open())
    {
        cout << "Erro ao abriri o arquivo" << endl;
        cout << path;
        exit(EXIT_FAILURE);
    }

    while ((totalCartas < MaxCartas) && (fin >> baralho[totalCartas].nome >> baralho[totalCartas].jogos >> baralho[totalCartas].gols >> baralho[totalCartas].titulos))
    {
        totalCartas++;
    }
    if (totalCartas >= MaxCartas)
    {
        cout << "Baralho Cheio!!" << endl;
    }

    fin.close();
}

void carregaCartas(Carta baralho[], int &totalCartas)
{
    ifstream fin;
    fin.open("baralhos.dat", ios_base::in | ios_base::binary);
    if (!fin.is_open())
    {
        cout << "Erro ao abrir arquivo. Criando novo baralho..." << endl;
        return;
    }
    char header[8];
    fin.read(header, 7);
    header[7] = '\0';
    if (string(header) != "BARALHO")
    {
        cout << "Arquivo invalido/corrompido" << endl;
        fin.close();
        return;
    }
    unsigned short totalFile;
    fin.read((char *)&totalFile, sizeof(totalFile));
    totalCartas = 0;

    for (int i = 0; i < totalFile && i < MaxCartas; i++)
    {
        fin.read((char *)&baralho[i], sizeof(Carta));
        totalCartas++;
    }
    cout << "Baralho carregado! Cartas: " << totalCartas << endl;
    fin.close();
}

void salvaCartas(Carta baralho[], int &totalCartas)
{
    ofstream fout;
    fout.open("baralhos.dat", ios_base::out | ios_base::binary);
    if (!fout.is_open())
    {
        cout << "Erro ao abrir o arquivo!!" << endl;
        return;
    }
    else
    {
        fout.write("BARALHO", 7);
        unsigned short totalFile = totalCartas;
        fout.write((char *)&totalFile, sizeof(totalFile));
        for (int i = 0; i < totalCartas; i++)
        {
            fout.write((char *)&baralho[i], sizeof(Carta));
        }
    }
    fout.close();
    cout << "Baralho salvo com sucesso!" << endl;
}
void alterar(Carta baralho[], int &totalCartas)
{
    cout << "\n\t-----Atualizar Cartas\n\t-----";
    listarCartas(baralho, totalCartas);
    int numprocurado;
    cout << "Digite o numero da carta: " << endl;
    cin >> numprocurado;
    for (int i = 0; i < totalCartas && i < MaxCartas; i++)
    {
        if (numprocurado == i + 1)
        {
            cout << "Alterando a carta #" << numprocurado << "(" << baralho[i].nome << ")" << endl;
            cin.ignore();
            cin.getline(baralho[i].nome, sizeof(baralho[i].nome));
            cout << "Nova quantidade de jogos: " << endl;
            cin >> baralho[i].jogos;
            cout << "Nova quantidade de gols: " << endl;
            cin >> baralho[i].gols;
            cout << "Nova quantidade de titulos: " << endl;
            cin >> baralho[i].titulos;

            cout << "Carta atualizada com sucesso!!!" << endl;
            break;
        }
        else
        {
            cout << "Carta nao encontrada! numero invalido." << endl;
        }
    }
}
void excluir(Carta baralho[], int &totalCartas)
{

    if (totalCartas == 0)
    {
        cout << "Nenhuma carta cadastrada para excluir.\n";
        return;
    }
    cout << "\n\t-----Excluir Cartas\n\t-----";
    listarCartas(baralho, totalCartas);
    int numprocurado;
    cout << "Digite o numero da carrta: " << endl;
    cin >> numprocurado;
    if ((numprocurado <1) || (numprocurado > totalCartas))
    {
        cout << "Numero invalido" << endl;
        system("pause");
        return;
    }
    for (int i = numprocurado - 1; i < totalCartas; i++)
    {
        baralho[i] = baralho[i + 1];
    }
     totalCartas--;
}

int main()
{

    Carta baralho[MaxCartas];
    int totalCartas = 0;
    int opcao;
    carregaCartas(baralho, totalCartas);

    do
    {
        cout << "\n--- Gerador de Cartas ---\n";
        cout << "1- Cadastrar Carta\n";
        cout << "2- Listar Cartas\n";
        cout << "3- Importar Cartas\n";
        cout << "4- Alterar\n";
        cout << "5- Excluir\n";
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
        case 3:
            import(baralho, totalCartas);
            break;
        case 4:
            alterar(baralho, totalCartas);
            break;
        case 5:
            excluir(baralho, totalCartas);
            break;
        case 0:
            salvaCartas(baralho, totalCartas);
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }

    } while (opcao != 0);
    return 0;
}