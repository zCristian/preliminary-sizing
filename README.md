# Preliminary Sizing

Programa em C++ com interface gráfica em Qt para estimativa preliminar do peso bruto de decolagem de aeronaves de asa fixa a partir de uma missão definida pelo usuário.

O projeto foi desenvolvido como trabalho da disciplina de Programação III, com foco na aplicação de conceitos de programação orientada a objetos, como abstração, encapsulamento, herança, polimorfismo, uso de ponteiros inteligentes e organização modular do código.

## O que o projeto faz

O programa estima o peso inicial de uma aeronave com base em:

* classe da aeronave;
* tipo de propulsão;
* peso da tripulação;
* peso da carga paga;
* segmentos de missão;
* consumo específico;
* razão de planeio;
* eficiência propulsiva;
* frações de peso ao longo da missão.

A aplicação permite montar uma missão simplificada e calcular a fração final de peso, o peso bruto estimado, o peso vazio, o combustível consumido e o resíduo da solução iterativa.

## Por que o projeto é útil

O dimensionamento preliminar é uma etapa inicial importante no projeto de aeronaves. Nessa fase, estimativas rápidas permitem avaliar se uma configuração inicial é coerente antes de análises mais detalhadas.

Este programa organiza esse processo em uma aplicação modular, permitindo que diferentes segmentos de missão sejam tratados de forma independente e reutilizável.

Além disso, o projeto serve como exemplo acadêmico de aplicação prática de programação orientada a objetos em um problema de engenharia aeroespacial.

## Funcionalidades

* Interface gráfica desenvolvida com Qt Widgets.
* Seleção da classe da aeronave.
* Escolha entre propulsão a jato ou a hélice.
* Entrada de parâmetros de missão.
* Cálculo das frações de peso por segmento.
* Estimativa iterativa do peso bruto inicial.
* Exibição do peso vazio estimado.
* Estimativa de combustível consumido.
* Exibição de resumo textual dos resultados.
* Estrutura modular baseada em classes e herança.

## Estrutura do projeto

```text
preliminary-sizing/
├── assets/
│   └── aircraft-icon.png
├── docs/
│   └── uml/
│       └── preliminary_sizing_uml.puml
├── include/
│   └── sizing/
│       ├── gui/
│       ├── segments/
│       ├── AircraftClass.h
│       ├── Mission.h
│       ├── PropulsionType.h
│       └── WeightEstimator.h
├── src/
│   ├── gui/
│   ├── segments/
│   ├── AircraftClass.cpp
│   ├── Mission.cpp
│   └── WeightEstimator.cpp
├── main.cpp
├── resources.qrc
└── CMakeLists.txt
```

## Principais classes

### `AircraftClass`

Representa a classe da aeronave e armazena os coeficientes utilizados para estimar a fração de peso vazio em função do peso bruto inicial.

### `Mission`

Representa a missão da aeronave. Armazena uma sequência de segmentos e calcula a fração de peso final da missão.

### `MissionSegment`

Classe abstrata base para todos os segmentos de missão. Define a interface comum implementada pelas classes derivadas.

### `WeightEstimator`

Classe responsável por estimar o peso bruto inicial da aeronave a partir da missão, da classe da aeronave, da tripulação e da carga paga.

### `MainWindow`

Classe responsável pela interface gráfica, entrada de dados e exibição dos resultados.

## Conceitos de Programação III utilizados

O projeto aplica os seguintes conceitos:

* **Abstração:** a classe `MissionSegment` define uma interface comum para diferentes segmentos de missão.
* **Encapsulamento:** os atributos das classes são protegidos por modificadores de acesso.
* **Herança:** segmentos específicos herdam de classes base.
* **Polimorfismo dinâmico:** a missão armazena segmentos por meio de ponteiros para a classe base `MissionSegment`.
* **Ponteiros inteligentes:** uso de `std::unique_ptr` para gerenciar segmentos de missão.
* **Organização modular:** separação entre interface gráfica, modelo de cálculo e segmentos de missão.

## Hierarquia simplificada dos segmentos

```text
MissionSegment
├── TaxiTakeoffSegment
├── ClimbSegment
├── DescentSegment
├── LandingSegment
├── CruiseRangeSegment
│   ├── JetCruiseRangeSegment
│   └── PropellerCruiseRangeSegment
└── ReserveCruiseSegment
    ├── JetReserveCruiseSegment
    └── PropellerReserveCruiseSegment
```

## Requisitos

Para compilar o projeto, é necessário ter instalado:

* C++17 ou superior;
* CMake;
* Qt 6;
* Qt Widgets;
* Make ou Ninja.

No Ubuntu, os principais pacotes podem ser instalados com:

```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev
```

## Como compilar

Na pasta raiz do projeto, execute:

```bash
cmake -S . -B build
cmake --build build
```

## Como executar

Após a compilação, execute:

```bash
./build/PreliminarySizing
```

## Como usar

Na interface gráfica:

1. selecione a classe da aeronave;
2. escolha o tipo de propulsão;
3. insira os pesos de tripulação e carga paga;
4. preencha os parâmetros da missão;
5. clique no botão de cálculo;
6. analise os resultados exibidos na janela.

## Diagrama UML

O diagrama UML foi desenvolvido em PlantUML e está disponível em:

```text
docs/uml/preliminary_sizing_uml.puml
```

Para visualizar no VS Code, pode-se utilizar a extensão PlantUML.

Para exportar o diagrama pela extensão, use:

```text
PlantUML: Export Current Diagram
```

Também é possível exportar pelo terminal:

```bash
plantuml -tsvg docs/uml/preliminary_sizing_uml.puml
```

## Observações

Este programa possui finalidade acadêmica e foi desenvolvido para estudos de dimensionamento preliminar. Os resultados devem ser interpretados como estimativas iniciais e não substituem análises detalhadas de desempenho, estabilidade, estrutura, certificação ou viabilidade operacional.

## Autor

Cristian Martins

Projeto desenvolvido para a disciplina de Programação III.
