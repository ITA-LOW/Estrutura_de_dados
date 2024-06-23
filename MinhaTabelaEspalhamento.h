#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente
#include <math.h>
//função pow para converter string em numero

template <typename T, std::size_t capac>

class MinhaTabelaEspalhamento final : public TabelaEspalhamentoAbstrata<T, capac>
{
public:

    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    virtual std::size_t capacidade() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return capac;
    };

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     *
     * @param dado O dado a ser inserido.
     */
    virtual void inserir(T dado) 
    {
        std::size_t casa = funcaoEspalhamento(dado);
        this->tabela.at(casa).inserirNoFim(dado);
    };

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     *
     * @param dado O dado a ser removido.
     */
    virtual void remover(T dado) {
        // escreva o algoritmo esperado
        std::size_t casa = funcaoEspalhamento(dado);
        this->tabela.at(casa).remover(dado);
    };

    /**
     * @brief Verifica se \p dado está contido na tabela.
     *
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        size_t casa; //casa é dado%capac
        casa = funcaoEspalhamento(dado);
        return this->tabela.at(casa).contem(dado);
    };
    

    /**
     * @brief Obtém a quantidade de dados contidos na tabela (tabela nesse caso são as casas dos pombos).
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t quantidade() const
    {
        std::size_t quantidade = 0;
        std::size_t i;

        for(i = 0; i < capac; ++i){
            quantidade += this->tabela[i].tamanho(); //visito cada casa de pombo e conto quantos tem la
        }

        return quantidade;
    };

    /**
     * @brief Obtém a posição de um dado na tabela e o tamanho da lista em que
     * se encontra.
     *
     * @param dado O dado sendo buscado.
     * @return A posição do dado na tabela estando ele ou não na tabela e, caso
     * esteja, a posição na lista.
     */
    /* Posicao posicao(T dado) const
    {
        std::size_t posTabela = funcaoEspalhamento(dado);
        std::size_t tamLista = this->tabela.at(posTabela).tamanho();
        std::optional<std::size_t> (posLista) = this->tabela.at(posTabela).posicao(dado);
        return Posicao{posTabela, tamLista, posLista};
    }; */

protected:
    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    virtual std::size_t funcaoEspalhamento(T dado) const
    {
        return codigoEspalhamento(dado)%capac;
    };

private:
    /**
     * @brief Calcula a representação numérica de um tipo integral.
     *
     * @tparam U O tipo integral.
     * @param integral Um valor integral.
     * @return Um inteiro calculado através de static_cast<std::size_t>(integral)
     */
    template <typename U>
    std::size_t codigoEspalhamento(U integral) const
    {
        // substitua a linha abaixo pelo algoritmo esperado. Dica use std::is_integral_v<U> para garantir que U é um tipo integral
        return static_cast<std::size_t>(integral);
    };

    /**
     * @brief Calcula a representação numérica de um string.
     *
     * @param s um string.
     * @return Um inteiro calculado conforme s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1].
     */
    std::size_t codigoEspalhamento(std::string const &string) const
    {
        std::size_t hash = 0;
        std::size_t n = string.length();

        for (std::size_t i = 0; i < n; ++i) {
            hash += static_cast<std::size_t>(string[i]) * static_cast<std::size_t>(pow(31, n - (i + 1)));
        }

        return hash;
    }
};

#endif