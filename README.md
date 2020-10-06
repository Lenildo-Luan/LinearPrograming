# Linear Programing (LP)

A Programação Linear se trata de uma importante área da Pesquisa Operacional (PO). Ela estuda formas de resolver problemas de otimização que podem ser descritos matematicamente a partir de funções lineares (Ex: `y <= 3`). E sua grande importância se dá pelo fato de que uma grande gama de problemas de otimização podem ser descritos a partir de funções lineares ou usam técnicas de LP para resolver sub-problemas.

## Optmization

Para saber do que se trata um problema de otimização, qual sua natureza e como podem ser descritos (isto engloba os problemas de LP) estou idealizando um repositório com tal conteúdo. Até lá, uma rápida pesquisa no google pode lhe dar esta resposta ;)

## LP problems

Neste repositório busco expor algumas implementações que realizo, com fins de estudo, para a comunidade. Para organizar, categorizei os problemas de LP em: 
  
  - Problemas de mistura
  - Problemas de transporte e designação
  - Problemas de planejamento de produção
  - Problemas de programação de projetos
  - Problemas de gestão financeira

Os problemas implementados são retirados de materiais didático fornecidos por pesquisadores e em livros sobre o assunto. Para que você possa entender o problema abordado por cada implementação, deixarei a referência necessária.

## Executando os códigos

Os problemas foram implementados na linguagem `C++` utilizando o `OR-Tools` e seu _solver_ padrão, `Glop`, ambos _open-source_ e desenvolvidos pela Google. Para instalar o `OR-Tools` e conseguir rodar as implementações, basta seguir o [tutorial da própria Google](https://developers.google.com/optimization/install).