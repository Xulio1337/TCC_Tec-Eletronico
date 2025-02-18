# TCC_Tec-Eletronico
# Sala Automatizada com Controle via Bluetooth

## Visão Geral do Projeto
Este projeto consiste no desenvolvimento de uma sala automatizada utilizando um **Arduino Mega**, uma **shield CNC**, um **módulo Bluetooth**, dois **motores de passo**, um **sensor ultrassônico** e diversos **LEDs**. A automação permite o controle de diferentes elementos da sala por meio de comandos enviados via um aplicativo de celular ou computador, promovendo maior acessibilidade e eficiência.

## Funcionamento
O sistema conta com dois motores de passo, onde:
- Um motor representa uma **porta automatizada** que, ao identificar a presença de uma pessoa por meio do sensor ultrassônico, se abre automaticamente.
- O outro motor controla uma **janela**, que pode ser aberta ou fechada mediante comandos específicos.

Além dos motores, **LEDs foram integrados** para representar diferentes eletrodomésticos, como **televisão e cafeteira**. O **módulo Bluetooth** possibilita a comunicação sem fio, permitindo que o usuário envie comandos e controle a sala remotamente.

## Estrutura do Código
O código foi desenvolvido de forma a garantir a comunicação eficiente entre os dispositivos, utilizando **duas saídas de comunicação Serial**:
- Uma para o terminal do **computador**.
- Outra para o terminal do **celular, via Bluetooth**.

Os comandos são organizados em diferentes **"cases"** dentro da estrutura condicional `switch-case`:
- De `1` a `8` são responsáveis pelo **controle dos motores**.
- De `a` a `d` **controlam os LEDs**.
- Os comandos `N` e `D` **executam múltiplas atividades simultaneamente**.

## Objetivo do Projeto
A proposta inicial era criar um ambiente **totalmente controlável** por celular ou computador, seguindo a lógica da **Internet das Coisas (IoT)**. No entanto, optou-se pelo uso do **Bluetooth** em vez de uma conexão com a internet, visando a implementação da tecnologia em **áreas remotas**, onde o acesso à rede pode ser limitado. Dessa forma, este projeto busca expandir as possibilidades de automação e telecomunicação para locais com infraestrutura reduzida.

## Contribuição e Desenvolvimento
Durante o desenvolvimento, fui responsável pela **concepção da ideia, execução, montagem, eletrônica, mecânica e programação** do projeto.
