#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL(){
        this->apagarArvore(this->raiz);
    };

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        if (this->raiz == nullptr){
            return true;
        } else {
            return false;
        }
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const
    {
        return contaElementos(this->raiz);
    };

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        if(busca(chave, this->raiz) != nullptr){ 
            return true;
        }else{
            return false;
        }
    };

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        Nodo<T> * raizSubArvore = busca(chave, this->raiz);
        if(raizSubArvore != nullptr){
            return raizSubArvore->altura;
        }else{
            return std::nullopt;
        }
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave){
        this->raiz = inserirRec(this->raiz, chave);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave){
        this->raiz = removerRec(this->raiz, chave);
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        Nodo<T> *nodo = busca(chave, this->raiz);
        if (nodo != nullptr && nodo->filhoEsquerda != nullptr) {
            return nodo->filhoEsquerda->chave;
        } else {
            return std::nullopt;
        }
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        Nodo<T> *nodo = busca(chave, this->raiz);
        if (nodo != nullptr && nodo->filhoDireita != nullptr) {
            return nodo->filhoDireita->chave;
        } else {
            return std::nullopt;
        }
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        ListaEncadeadaAbstrata<T> * lista = new MinhaListaEncadeada<T>;
        funcaoEmOrdem(this->raiz, lista);
        return lista;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        ListaEncadeadaAbstrata<T> * lista = new MinhaListaEncadeada<T>;
        funcaoPreOrdem(this->raiz, lista);
        return lista;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        ListaEncadeadaAbstrata<T> * lista = new MinhaListaEncadeada<T>;
        funcaoPosOrdem(this->raiz, lista);
        return lista;
    };

    //###########################################################################################################
    //####################### todas as funções auxiliares estão a partir daqui ##################################
    //###########################################################################################################

    // função auxiliar do destrutor
        void apagarArvore(Nodo<T>* nodo){
        if (nodo != nullptr){
            apagarArvore(nodo->filhoDireita);
            apagarArvore(nodo->filhoEsquerda);
            delete nodo;
        }
    };
    
    // função auxiliar para contar quantidade de elementos de uma arvore
    int contaElementos(Nodo<T> *nodo) const
    {
        if (nodo == nullptr) return 0;

        return 1 + contaElementos(nodo->filhoEsquerda) + contaElementos(nodo->filhoDireita);
    };

    // função auxiliar contem
    Nodo<T> * busca(T elemento, Nodo<T> * nodo) const {
        if (nodo == nullptr || nodo->chave == elemento) {
            return nodo;
        } else if (elemento < nodo->chave) {
            return busca(elemento, nodo->filhoEsquerda);
        } else {
            return busca(elemento, nodo->filhoDireita);
        }
    };

    // função auxiliar para calcular a altura
    int auxAltura(Nodo<T>* nodo) const {
        if (nodo == nullptr) {
            return -1;
        } else {
            return nodo->altura;
        }
    };

    //função auxiliar para inserir um novo nó
    Nodo<T> * inserirRec(Nodo<T>* nodo, T elemento) const {
        if(nodo == nullptr){
            return new Nodo<T>{elemento};
        }
        
        if(elemento > nodo->chave){
            nodo->filhoDireita =  inserirRec(nodo->filhoDireita, elemento);
            nodo->altura = std::max(auxAltura(nodo->filhoEsquerda), auxAltura(nodo->filhoDireita)) + 1;
        }else if(elemento < nodo->chave){
            nodo->filhoEsquerda =  inserirRec(nodo->filhoEsquerda, elemento);
            nodo->altura = std::max(auxAltura(nodo->filhoEsquerda), auxAltura(nodo->filhoDireita)) + 1;
        }else {
            return nodo;
        }

        int balance = getBalance(nodo);

        // Rotação simples à direita
        if (balance > 1 && elemento < nodo->filhoEsquerda->chave) {
            return rotacaoDireita(nodo);
        }

        // Rotação simples à esquerda
        if (balance < -1 && elemento > nodo->filhoDireita->chave) {
            return rotacaoEsquerda(nodo);
        }

        // Rotação dupla (esquerda-direita)
        if (balance > 1 && elemento > nodo->filhoEsquerda->chave) {
            nodo->filhoEsquerda = rotacaoEsquerda(nodo->filhoEsquerda);
            return rotacaoDireita(nodo);
        }

        // Rotação dupla (direita-esquerda)
        if (balance < -1 && elemento < nodo->filhoDireita->chave) {
            nodo->filhoDireita = rotacaoDireita(nodo->filhoDireita);
            return rotacaoEsquerda(nodo);
        }

        return nodo;
    };


    void funcaoPreOrdem(Nodo<T> * nodo, ListaEncadeadaAbstrata<T> * lista) const {
        if(nodo != nullptr){
            lista->inserirNoFim(nodo->chave);
            funcaoPreOrdem(nodo->filhoEsquerda, lista);
            funcaoPreOrdem(nodo->filhoDireita, lista);
        }
    };

    void funcaoEmOrdem(Nodo<T> * nodo, ListaEncadeadaAbstrata<T> * lista) const{
        if(nodo != nullptr){
            funcaoEmOrdem(nodo->filhoEsquerda, lista);
            lista->inserirNoFim(nodo->chave);
            funcaoEmOrdem(nodo->filhoDireita, lista);
        }
    };

    void funcaoPosOrdem(Nodo<T> * nodo, ListaEncadeadaAbstrata<T> * lista) const {
        if(nodo != nullptr){
            funcaoPosOrdem(nodo->filhoEsquerda, lista);
            funcaoPosOrdem(nodo->filhoDireita, lista);
            lista->inserirNoFim(nodo->chave);
        }
    };

    // Rotação simples à direita
    Nodo<T> *rotacaoDireita(Nodo<T> *y)const {
        Nodo<T> *x = y->filhoEsquerda;
        Nodo<T> *T2 = x->filhoDireita;
        x->filhoDireita = y;
        y->filhoEsquerda = T2;
        y->altura = std::max(auxAltura(y->filhoEsquerda), auxAltura(y->filhoDireita)) + 1;
        x->altura = std::max(auxAltura(x->filhoEsquerda), auxAltura(x->filhoDireita)) + 1;
        return x;
    };

    // Rotação simples à esquerda
    Nodo<T> *rotacaoEsquerda(Nodo<T> *x) const
    {
        Nodo<T> *y = x->filhoDireita;
        Nodo<T> *T2 = y->filhoEsquerda;
        y->filhoEsquerda = x;
        x->filhoDireita = T2;
        x->altura = std::max(auxAltura(x->filhoEsquerda), auxAltura(x->filhoDireita)) + 1;
        y->altura = std::max(auxAltura(y->filhoEsquerda), auxAltura(y->filhoDireita)) + 1;
        return y;
    };

    // Obter fator de balanceamento
    int getBalance(Nodo<T> *nodo) const
    {
        return nodo == nullptr ? 0 : auxAltura(nodo->filhoEsquerda) - auxAltura(nodo->filhoDireita);
    };

     // Função auxiliar para encontrar o nó com o valor mínimo (importante para fazer a deleção)
    Nodo<T> *minimoNodo(Nodo<T> *nodo) const
    {
        Nodo<T> *atual = nodo;
        while (atual->filhoEsquerda != nullptr)
            atual = atual->filhoEsquerda;
        return atual;
    }

    // Função auxiliar para remover um nó
    Nodo<T> *removerRec(Nodo<T> *nodo, T elemento)
    {
        if (nodo == nullptr) {
            return nodo;
        }

        if (elemento < nodo->chave) {
            nodo->filhoEsquerda = removerRec(nodo->filhoEsquerda, elemento);
        } else if (elemento > nodo->chave) {
            nodo->filhoDireita = removerRec(nodo->filhoDireita, elemento);
        } else {
            if (nodo->filhoEsquerda == nullptr || nodo->filhoDireita == nullptr) {
                Nodo<T> *temp = nodo->filhoEsquerda ? nodo->filhoEsquerda : nodo->filhoDireita;
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    *nodo = *temp;
                }
                delete temp;
            } else {
                Nodo<T> *temp = minimoNodo(nodo->filhoDireita);
                nodo->chave = temp->chave;
                nodo->filhoDireita = removerRec(nodo->filhoDireita, temp->chave);
            }
        }

        if (nodo == nullptr) {
            return nodo;
        }

        nodo->altura = 1 + std::max(auxAltura(nodo->filhoEsquerda), auxAltura(nodo->filhoDireita));

        int balance = getBalance(nodo);

        // Rotação simples à direita
        if (balance > 1 && getBalance(nodo->filhoEsquerda) >= 0) {
            return rotacaoDireita(nodo);
        }

        // Rotação simples à esquerda
        if (balance < -1 && getBalance(nodo->filhoDireita) <= 0) {
            return rotacaoEsquerda(nodo);
        }

        // Rotação dupla (esquerda-direita)
        if (balance > 1 && getBalance(nodo->filhoEsquerda) < 0) {
            nodo->filhoEsquerda = rotacaoEsquerda(nodo->filhoEsquerda);
            return rotacaoDireita(nodo);
        }

        // Rotação dupla (direita-esquerda)
        if (balance < -1 && getBalance(nodo->filhoDireita) > 0) {
            nodo->filhoDireita = rotacaoDireita(nodo->filhoDireita);
            return rotacaoEsquerda(nodo);
        }

        return nodo;
    };
};

#endif