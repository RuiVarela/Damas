# Damas

Introdução à Programação  
ISCTE, 2002/2003  
Trabalho Final

Grupo nº: 11  
Nome: Rui Filipe Borges Varela  
Nº: 22175

## Relatório 
De forma muito sucinta posso estruturar o programa em quatro classes que se relacionam entre si de forma hierárquica, no topo temos a classe jogo que tem um membro privado do tipo Tabuleiro, que de forma evidente constitui o tabuleiro de jogo, por seu lado este tabuleiro contém um vector de 8x8 células, e cada célula contém uma peça.  
Desta forma temos no tabuleiro varias peças do tipo sem_peça, que foi a maneira utilizada para representar um célula desocupada.  
Fora do encapsulamento das classes foi incluída um única função (n tendo em conta o main) 
Com o intuito de tornar o código relativamente dinâmico foram utilizados entre outros, enumerações para estados (i.e. EstadoDePosicao, EstadoDeJogo), nesse mesmo sentido tentamos afastar o controlo do fluxo do programa da classe tabuleiro, que funciona como um suporte para o jogo, não realizando só por si o jogo, pensando no futuro é mais fácil reescrever outra classe jogo que, de forma mais inovadora controle a classe Tabuleiro, para que não fiquem a pensar que é texto em vão, uma solução vantajosa seria arranjar um sistema de selecção de posição que utilizasse o rato.

## Extras

### Redimensionar 
O primeiro extra é o facto da janela poder redimensionada, sendo que é actualizada de foma eficiente. Foram estabelecidas medidas base (3x7) como mínimo para o tamanho de uma célula.   
No seguimento desta funcionalidade, foi criada uma variável (aspecto), na classe Tabuleiro, que serve de mediador para calcular as medidas necessárias às funções que exigem desenho do tabuleio 

### Damas Normais 
O segundo extra é o facto das damas se comportarem como damas regulares, isto é podem dar saltos maiores que os peõs. Porém esta funcionalidade exigiu que fosse devidamente implementado o seu suporte no que diz respeito ao cumprimento de um requisito do programa, dado um posição saber se é possível chegar a outra.  
Sendo que é a função Tabuleiro::simulacaoDePercurso(..) é mais complexa do jogo passo a explicar: 
- Esta função funciona em cooperação com Tabuleiro::podePercorrer (), a primeira prepara a execução da outra, 
- É necessária uma atenção especial neste contexto visto que a peça pode executar um salto(onde toma uma peça) e só depois começa a comer em sequência, como tal foi necessário verificar as possibilidades desse salto. 
- A primeira função inicia um especie de simulação que vai percorrendo as diagonais à dama até encontrar uma posição onde possa haver sequência
- Quando encontra passa controlo para a função Tabuleiro::podePercorrer (), esta indica se é possível através de capturas chegar à posição desejada. O termo simulação não é usado em vão, visto que à medida que se vai testanto o percurso as pseudo-peças comidas vão sendo marcadas como sem_peça, e quando é necessário voltam a ser marcadas com o verdadeiro estado.

### IPC++ 
Com este código é possível jogar contra outra máquina (embora dividindo processos), através de ipc++.   
O protocolo é muito simples, de um lado é criado um vector de posições relativas à jogada, esse vector é posteriormente enviado.   
Este protocolo envia apenas a posições por onde a peça “em marcha” efectivamente passou. Do outro lado o vector é recebido construído recebendo (linha/coluna) referentas ás posições recebidas, depois estas posições são tratadas e executadas 
