# Implementação do RayCasting utilizando C++ e SDL

Este projeto é uma implementação do RayCasting em C++ utilizando a biblioteca SDL (Simple DirectMedia Layer). O RayCasting é uma técnica de renderização que serve como uma versão simplificada do RayTracing, comumente utilizado em computação gráfica para modelagem sólida 3D e renderização de imagens.

## Sobre o Ray Casting

Ray casting é a base metodológica para a modelagem sólida 3D e renderização de imagens em CAD/CAM. É essencialmente o mesmo princípio do ray tracing para gráficos computacionais, onde raios de luz virtuais são "lançados" ou "rastreados" desde o ponto focal de uma câmera através de cada pixel do sensor da câmera para determinar o que é visível ao longo do raio na cena 3D.

Para mais informações sobre Ray Casting, você pode consultar a [página da Wikipedia](https://en.wikipedia.org/wiki/Ray_casting).

## Funcionalidades

Neste projeto, é possível criar cenários utilizando o RayCasting como método de renderização e usufruir das seguintes funcionalidades:

- Objetos geométricos básicos: Cilindro, Cone, Esfera, Plano e Malhas.
- Transformações dos objetos no espaço: Translação, Rotação, Escala e Cisalhamento.
- Otimizações de eficiência, como clustering e backface culling (no caso de malhas).
- Adição de vários tipos de fontes luminosas, tais como: Pontual, Ambiente, Spot e Direcional.

## Requisitos

Antes de executar o projeto, é necessário ter instalado em seu sistema:

- C++ compiler
- SDL (Simple DirectMedia Layer) library

## Executando o projeto

Siga os passos abaixo para executar o projeto:

1. Clone o repositório para o seu ambiente local.
2. Certifique-se de ter as bibliotecas necessárias instaladas (C++ compiler e SDL).
3. Compile o projeto utilizando o seu compilador C++ de preferência.
4. Execute o executável gerado após a compilação.

## Como utilizar

Ao executar o projeto, você será apresentado a uma cena vazia. Você pode utilizar o teclado e o mouse para interagir com o cenário:

- Adicione objetos geométricos à cena (cilindro, cone, esfera, plano ou malhas).
- Aplique transformações aos objetos, como movê-los, girá-los, dimensioná-los ou aplicar cisalhamento.
- Experimente diferentes tipos de fontes luminosas e observe o efeito na cena renderizada.

## Contribuições

Contribuições são bem-vindas! Se você deseja adicionar mais funcionalidades, melhorar o código ou corrigir problemas, sinta-se à vontade para fazer um fork deste repositório, implementar as alterações e enviar um pull request.

## Licença

Este projeto é licenciado sob a [MIT License](LICENSE), o que significa que você é livre para utilizá-lo e modificá-lo conforme suas necessidades.

Esperamos que aproveite este projeto e aprenda mais sobre Ray Casting e suas aplicações em computação gráfica! Se tiver alguma dúvida, sinta-se à vontade para entrar em contato. Aproveite!
