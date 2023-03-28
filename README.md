# Trabalho 1 - Estrutura de Dados
![image](https://user-images.githubusercontent.com/92150848/224928731-e176f871-3ba1-4c7e-b087-ad9bb12001aa.png)
---
>O mundo de Pandora vive momentos de tensão entre os povos Ya’nki e Chi’ni. O povo
Chi’ni enviou secretamente balões para espionar o território dos Ya’nki. Estes descobriram objetos
voadores e enviam caças para derrubá-los via bombas de detonação por afastamento. Entretanto, os
balões tiram fotos e enviam-nas para sua base de observação.
As fotos podem retratar desde instalações militares ou logísticas de grande importância até
regiões vazias ou pouco relevantes. Por isso, a base avalia cada foto e atribui a ela um número que
denota seu grau de importância: quanto maior o número, maior a importância.

anotações pra mim mesmo:
- vou ter que dar um jeito de empurrar as fotos geradas usando static provavelmente
- seno e cosseno pra calcular lugar da bomba + sai DEBAIXO (y positivo pq é svg) do texto a bomba
- perguntar o que é a posição relativa do elemento à borda da foto no comando tf
- tem toda a putaria da pontuação ainda
- clones
- testar caminho relativo no ted 


- lendo geo ok
- colocando na lista ok
- lendo qry
- executando comandos qry
    - mv
    - g
    - ff
    - tf
    - df
        - gerando txt e svgs auxiliares das fotos
        - pontuação
    - d
    - b?
    - c?

- gerando svg final ok


---- NO GERAL ----
torpedos
funções que geram coisas no txt pra nao ficar fudido longo cagado
leitura.h
mudar main (colocar as coisas novas e ver a questao dos path relativos/sem path)
e pronto???????????

vai ter um for(fila) dai pra cada elemento (foto/lista) da fila eu acho o maiorX (entre ele e a bordaAtual) da foto anterior (0 se for primeiro)
tendo a clausura com o dx (deslocamento das fotos) eu crio uma lista nova com as coisas deslocadas

TXT VAI SER NO SWITCH CASE DE LEITURA USANDO FUNÇOES DO TXT.H

calcular onde a bomba ta
remover elementos da lista principal
clonar certos elementos

ESTOU FAZENDO ELE PERCORRER AS FILAS DO BALAO ATINGIDO PELO MISSIL PRA CLONAR OS ELEMENTOS DAS FOTOS NAO ENVIADAS