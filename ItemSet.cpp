#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ItemSet
{
    private:
        vector<string> listaItens;
        bool itemCadastrado(string s);

    public:
        ItemSet();
        ItemSet(const ItemSet &b);
        ~ItemSet();
        vector<string> getListaItens();
        void setListaItens(vector<string> _listaItens);
        void inserir(string s);
        void excluir(string s);
        int localizarItem(string &item_a_buscar);

        ItemSet operator+(ItemSet c);
        ItemSet &operator=(const ItemSet &b);
        ItemSet operator*(ItemSet c);
        ItemSet operator-(ItemSet C);
        ItemSet operator&(ItemSet C);//vamos utilizar o operador & para sobrecarregar já que o operador <> nao é aceito
        bool operator==(ItemSet C);
};

ItemSet::ItemSet() {}

// Construtor que recebe outro ItemSet como parâmetro
ItemSet::ItemSet(const ItemSet &b)
{
    // Copiar os itens do conjunto 'other' para o novo conjunto
    for (const std::string &item : b.listaItens)
    {
        this->inserir(item);
    }
}

// Sobrecarga do operador de atribuição '='
ItemSet &ItemSet::operator=(const ItemSet &b)
{
    if (this == &b)
    {
        return *this; // Evitar auto-atribuição
    }

    // Limpar os itens do conjunto atual
    this->listaItens.clear();

    // Copiar os itens do conjunto 'other' para o conjunto atual
    for (const std::string &item : b.listaItens)
    {
        this->inserir(item);
    }

    return *this;
}

ItemSet::~ItemSet()
{
}

vector<string> ItemSet::getListaItens()
{
    return listaItens;
}

void ItemSet::setListaItens(vector<string> _listaItens)
{
    listaItens = _listaItens;
}

bool ItemSet::itemCadastrado(string _s)
{
    for (string s : listaItens)
    {
        if (s == _s)
        {
            return true;
        }
    }

    return false;
}

void ItemSet::inserir(string s)
{
    int tam = listaItens.size();

    if (tam == 0 || !itemCadastrado(s))
    {
        listaItens.push_back(s);
    }
}

void ItemSet::excluir(string s)
{
    int tam = listaItens.size();

    if (tam >= 0 && itemCadastrado(s))
    {
        for (int i = 0; i < tam; i++)
        {
            if (listaItens[i] == s)
            {
                listaItens.erase(listaItens.begin() + i);
                break;
            }
        }
    }
}

ItemSet ItemSet::operator+(ItemSet c)
{
    ItemSet a, b;
    bool inserir;
    a.setListaItens(listaItens);

    for (string itemC : c.getListaItens())
    {
        inserir = true;

        for (string itemB : listaItens)
        {
            if (itemC == itemB)
            {
                inserir = false;
                break;
            }
        }

        if (inserir)
        {
            a.inserir(itemC);
        }
    }

    return a;
}

ItemSet ItemSet::operator-(ItemSet C)
{
    ItemSet result;
    for (string &item : listaItens)
    {
        
        if (C.localizarItem(item) == -1) 
        {
            result.inserir(item);
        }
    }
    return result;
}

ItemSet ItemSet::operator&(ItemSet C){
    int indiceEncontrou;
    ItemSet delta;

    for (string &item : listaItens)
    {
        
        if (C.localizarItem(item) == -1) 
        {
            delta.inserir(item);
        }
    }

    
    for (string itemC : C.getListaItens()){
        indiceEncontrou = -1;

        for (int i = 0; i < listaItens.size(); i++)
        {
            if (listaItens[i] == itemC)
            {
                indiceEncontrou = i;
                break;
            }
        }

        if (indiceEncontrou == -1) 
        {
            delta.inserir(itemC);
        }
    }
    
   return delta;
}

ItemSet ItemSet::operator*(ItemSet c)
{
    ItemSet b, interssecao;
    vector<string> itensU;

    b.setListaItens(listaItens);

    for (string itemB : listaItens)
    {
        for (string itemC : c.listaItens)
        {
            if (itemB == itemC)
                itensU.push_back(itemC);
        }
    }

    interssecao.setListaItens(itensU);

    return interssecao;
}

bool ItemSet::operator==(ItemSet C) 
{
    for (string item : listaItens) {
        if (C.localizarItem(item) == -1) {
            return false;
        }
    }

    for (string item : C.getListaItens()) {
        if (localizarItem(item) == -1) {
            return false;
        }
    }

    return true;
}

int ItemSet::localizarItem(string &item_a_buscar)
{
    for (int i = 0; i < listaItens.size(); i++)
    {
        if (listaItens[i] == item_a_buscar)
        {
            return i;
        }
    }

    return -1;
}

void testeOperadorAdicao(ItemSet itemB, ItemSet itemC);
void testeOperadorAtribuicao(ItemSet itemB);
void testeOperadorMultiplicacao(ItemSet itemB, ItemSet itemC);
void testeOperadorDiferenca(ItemSet &itemB, ItemSet &itemC);
void testeOperadorDelta(ItemSet itemB, ItemSet itemC);
void testeOperadorIgualdade(ItemSet itemB, ItemSet itemC);

int main(void)
{
    ItemSet itemB, itemC, itemD;

    vector<string> listaItensB = {"1", "2", "3", "4", "5"};
    vector<string> listaItensC = {"8", "7", "6", "5", "4", "3"};
    vector<string> listaItensD = {"1", "2", "3", "4", "5"};

    itemB.setListaItens(listaItensB);
    itemC.setListaItens(listaItensC);
    itemD.setListaItens(listaItensD);

    testeOperadorAdicao(itemB, itemC);
    testeOperadorAtribuicao(itemB);
    testeOperadorMultiplicacao(itemB, itemC);
    testeOperadorDiferenca(itemB, itemC); // Novo teste para o operador de diferença
    testeOperadorDelta(itemB, itemC);
    testeOperadorIgualdade(itemB, itemC);
    testeOperadorIgualdade(itemB, itemD);

    cout << endl << endl;
    return 0;
}

void testeOperadorDelta(ItemSet itemB, ItemSet itemC)
{
    ItemSet itemA;
    cout << endl << endl;
    cout << "B =    ";

    for (string s : itemB.getListaItens())
    {
        cout << s << "\t";
    }

    cout << endl << endl;

    cout << "C =    ";
    for (string s : itemC.getListaItens())
    {
        cout << s << "\t";
    }

    cout << endl << endl;

    //'A' recebe a união entre os itens que estão em 'B' mas não em 'C',  além dos elementos que estão em 'C' mas não em 'B'
    itemA = itemB & itemC;
    cout << "A = B <> C =>  ";
    for (string s : itemA.getListaItens())
    {
        cout << s << "\t";
    }
}

void testeOperadorDiferenca(ItemSet &itemB, ItemSet &itemC)
{
    ItemSet itemA;

    cout << "\nB =\t";
    for (string s : itemB.getListaItens())
    {
        cout << s << "\t";
    }

    cout << "\n\nC =\t";
    for (string s : itemC.getListaItens())
    {
        cout << s << "\t";
    }

    //'A' recebe os itens de 'B' que não estão em 'C'.
    itemA = itemB - itemC;
    cout << "\n\nA = B - C =>\t";
    for (string s : itemA.getListaItens())
    {
        cout << s << "\t";
    }
}

void testeOperadorAdicao(ItemSet itemB, ItemSet itemC)
{
    ItemSet itemA;

    cout << "\nB =\t";
    for (string s : itemB.getListaItens())
    {
        cout << s << "\t";
    }

    cout << "\n\nC =\t";
    for (string s : itemC.getListaItens())
    {
        cout << s << "\t";
    }

    //'A' recebe todos os itens de 'B' e os itens de 'C' que não se repetem em 'B'.
    itemA = itemB + itemC;
    cout << "\n\nA = B + c =>\t";
    for (string s : itemA.getListaItens())
    {
        cout << s << "\t";
    }
}

void testeOperadorAtribuicao(ItemSet itemB)
{
    ItemSet itemA;

    itemA = itemB;
    cout << "\n\nA = B =>\t";
    for (string s : itemA.getListaItens())
    {
        cout << s << "\t";
    }
}

void testeOperadorMultiplicacao(ItemSet itemB, ItemSet itemC)
{
    ItemSet itemA;

    // A recebe os itens de B que ocorrem também em C.
    itemA = itemB * itemC;
    cout << "\n\nA = B * C =>\t";
    for (string s : itemA.getListaItens())
    {
        cout << s << "\t";
    }
}

void testeOperadorIgualdade(ItemSet itemB, ItemSet itemC)
{
    // Testa se ambos os valores são iguais.
    bool is_igual = itemB == itemC;
    
    cout << "\n\nA == B => " << (is_igual ? "True" : "False") << "\t";
}