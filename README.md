# Mini Waze
### Final Project: Data Structures and Algorithms

[Assita a apresentação](https://youtu.be/njsW6HlLDzc)

## Descrição

O projeto final trata-se de uma versão simplificada do Waze. Para essa aplicação somente a cidade do Rio de Janeiro é considerada. Os pontos e ruas da cidade são representados por um grafo, cujos nós e arestas foram extraidos da biblioteca osmnx, pelo Python. O programa pode consultar o menor caminho ou o caminho mais rápido através do Dijkstra ou A*. Além disso, para o A* é possível ver os pontos sendo considerados pelo algortimo. 

## Grupo

> Ari Oliveira

> Lívia Meinhardt

> Luiz Luz

## Execução do programa

Para executar o programa localmente é necessária a instalação de um servidor ou acessar a máquina virtual criada. Instruções para qualquer uma dessas opções podem ser encontradas [aqui](auxiliares/servidor.md).

## Interação via Console

Caso deseje executar o programa via console basta executar o programa passando os padrâmetros:


```s
./main.cgi "y1" "x1" "y2" "x2" "algoritmo" "tipo_de_rota"
```
Em que:

* (y1,x1) é a coordenada do ponto de início
* (y2,x2) é a coordenada do ponto final
* algoritmo pode ser o A* [1] ou o Dijsktra [0]
* tipo de rota pode ser a mais rápida [1] ou a mais curta [0]

Exemplo:

```s
./main.cgi -22.905479 -43.168620 -22.894177 -43.679636 1 1
```
O comando executa o menor caminho entre as coordenadas dadas utilizando o A*.

Obs: deve-se estar no diretório do programa para executa-lo. Ou seja, antes execute:

```s
cd /var/www/final*/backend
```
