# Profissão Caminhoneiro – Design Detalhado (Versão Simples e Divertida)

---

## 1. Visão Geral da Profissão

A profissão de Caminhoneiro neste servidor tem como objetivo ser:

- Simples de entender e jogar.
- Divertida e recompensadora.
- Sem burocracia excessiva (sem fome, sono, contas etc.).
- Baseada em **saídas de Los Santos** levando cargas para várias regiões do mapa.
- Expandível no futuro sem precisar reescrever tudo.

O foco é: **pegar caminhão em Los Santos → escolher entrega → dirigir até o destino → ganhar conforme a distância percorrida**, com alguns bônus simples.

---

## 2. Conceitos Centrais

### 2.1. Ponto Inicial (Hub do Caminhoneiro em Los Santos)

- Local: pátio de caminhões em **Los Santos**, com caminhões (Linerunner) e alguns trailers próximos.
- Este será o **hub principal** da profissão, de onde saem todas as rotas.
- Os caminhões deste pátio serão veículos exclusivos da profissão.

### 2.2. Fluxo Básico da Profissão

1. O jogador vai até o pátio de caminhoneiro em Los Santos.
2. Entra em um caminhão da profissão.
3. O servidor detecta que ele está em um caminhão de job.
4. O jogador usa o comando `/carregar` para pegar uma entrega.
5. O sistema escolhe um destino (rota) **sempre saindo de LS**.
6. O servidor cria um checkpoint de entrega no destino.
7. O jogador dirige até o destino.
8. Ao chegar, o sistema calcula **distância percorrida** e **pagamento**, aplica possíveis bônus, paga o jogador e limpa o estado da entrega.

---

## 3. Estrutura de Dados e Variáveis

### 3.1. Rotas de Caminhoneiro

Cada rota representa **um destino** para o qual o jogador vai levar a carga, sempre considerando a saída de Los Santos.

Estrutura sugerida:

```pawn
enum e_route {
    Float:RouteX,
    Float:RouteY,
    Float:RouteZ
}

new Float:TruckerRoutes[][e_route] = {
    // Exemplos (ajustar depois com coords reais)
    { 655.16, -528.22, 16.80 },  // Dillimore
    { 200.52, -110.42, 1.55 },   // Blueberry
    { 1350.22, 260.44, 19.55 },  // Montgomery
    { -2156.22, -2444.88, 30.60 }, // Angel Pine
    { 2035.51, 1342.22, 10.60 },  // Las Venturas Centro
    { 1614.76, 2348.19, 10.82, 184.09 } // Las Venturas Centro 2
    { -1622.22, 707.33, 13.60 }   // San Fierro (doca, aeroporto etc.)
};
```

- Saída sempre a partir de LS (hub de caminhoneiro).
- Destinos podem ser organizados por categoria: cidades pequenas, LV, SF…

### 3.2. Dados por Jogador (estado da entrega)

Por jogador, precisamos de variáveis como:

- `bool:TruckerHasDelivery[playerid]` – se o jogador está em uma entrega ativa.
- `TruckerRouteIndex[playerid]` – índice da rota escolhida.
- `Float:TruckerStartX[playerid], TruckerStartY[playerid], TruckerStartZ[playerid]` – posição de início da entrega.
- `Float:TruckerDestX[playerid], TruckerDestY[playerid], TruckerDestZ[playerid]` – posição de destino.
- `Float:TruckerDistance[playerid]` – distância calculada para pagamento (pode ser a distância direta LS → destino, ou acumulada).
- `TruckerVehicle[playerid]` – ID do caminhão da entrega (para garantir que não troque de veículo).

Observação: para a **versão simples**, a distância pode ser **distância direta entre origem e destino** (posição do caminhão na saída e posição do checkpoint final). Se o jogador fizer um caminho mais longo de propósito, isso não influencia.

---

## 4. Comandos da Profissão

### 4.1. `/carregar`

**Função:** Inicia uma entrega de caminhoneiro para o jogador.

**Regras:**

- Só pode ser usado se o jogador estiver dentro de um **caminhão da profissão**.
- Não pode haver entrega ativa (`TruckerHasDelivery[playerid] == false`).

**Passos internos:**

1. Verifica se o veículo é um caminhão da profissão.
2. Verifica se o jogador já está em uma entrega.
3. Seleciona **uma rota aleatória** da lista `TruckerRoutes`.
4. Define destino do jogador (`TruckerDestX/Y/Z`) com base na rota.
5. Define início da entrega (`TruckerStartX/Y/Z`) baseado na posição atual do caminhão.
6. Registra o ID do veículo (`TruckerVehicle[playerid] = vehicleid`).
7. Marca `TruckerHasDelivery[playerid] = true`.
8. Cria um **checkpoint** no destino.
9. Envia mensagem ao jogador explicando o destino.

Exemplo de mensagem ao usar `/carregar`:

> (INFO) Você aceitou uma entrega de Los Santos para Dillimore. Siga o marcador no mapa!

### 4.2. `/cancelar` (opcional)

**Função:** Cancela a entrega atual do caminhoneiro.

**Regras:**

- Só pode ser usado se o jogador estiver em entrega (`TruckerHasDelivery[playerid] == true`).

**Efeitos:**

- Remove checkpoints.
- Limpa estado da entrega (`TruckerHasDelivery = false`, zera variáveis).
- Opcional: cobrar taxa de cancelamento ou apenas avisar.

Mensagem de exemplo:

> (AVISO) Entrega cancelada. Você poderá iniciar outra com /carregar.

---

## 5. Lógica de Pagamento por Distância

### 5.1. Momento do cálculo

O cálculo é feito quando o jogador **entra no checkpoint de destino**.

Hook usado: `OnPlayerEnterCheckpoint(playerid)` ou sistema equivalente de callbacks.

### 5.2. Cálculo da distância

Para a versão simples, podemos usar a distância direta entre o ponto de início e o ponto do destino:

```pawn
Float:dist = GetDistanceBetweenPoints(
    TruckerStartX[playerid], TruckerStartY[playerid], TruckerStartZ[playerid],
    TruckerDestX[playerid], TruckerDestY[playerid], TruckerDestZ[playerid]
);
```

Depois, convertemos essa distância para “quilômetros” aproximados (opcional), ou podemos usar a unidade do próprio SA-MP e aplicar uma constante.

Por exemplo:

```pawn
Float:km = dist / 1000.0; // Exemplo de conversão aproximada
```

### 5.3. Fórmula de pagamento

Fórmula simples sugerida:

```pawn
Float:basePay = km * 250.0; // 250 por km
```

Ou, se preferir não converter para km e usar a distância bruta:

```pawn
Float:basePay = dist * 0.25; // ajustando até ficar razoável nos testes
```

### 5.4. Bônus simples (opcionais)

Para manter o sistema leve, mas recompensando boa direção:

1. **Bônus de direção segura:**

   - Se a vida do veículo na entrega for maior que um certo limite (ex.: `GetVehicleHealth(vehicleid) > 900.0`), aplica +10%.

2. **Bônus noturno (opcional):**

   - Se o horário do servidor (`GetHour`) estiver entre 20h e 06h, aplica +5%.

Exemplo de cálculo final:

```pawn
Float:totalPay = basePay;

if (vehicleHealth > 900.0) {
    totalPay *= 1.10; // +10%
}

if (isNightTime) {
    totalPay *= 1.05; // +5%
}
```

No final:

- Arredondar o valor para inteiro.
- Pagar com `GivePlayerMoney(playerid, pagoFinal)`.

### 5.5. Mensagens de feedback ao jogador

Ao completar a entrega:

Exemplo de mensagem:

```text
(SUCESSO) Entrega concluída!
(INFO) Distância percorrida: 4.82 km
(INFO) Pagamento base: $1205
(INFO) Bônus de direção segura: +$120
(SUCESSO) Total recebido: $1325
```

Isso dá sensação de progresso e recompensa.

---

## 6. Tratamento de Casos Especiais

### 6.1. Jogador sai do veículo no meio da entrega

Opções:

- Mais simples: permitir sair, mas se **entrar em outro veículo**, a entrega é cancelada.
- Podemos checar em `OnPlayerStateChange`:

  - Se o player mudou para outro veículo que não seja o da entrega: cancela a entrega.

### 6.2. Caminhão explode ou é destruído

- Cancela a entrega automaticamente.
- Opcional: mandar mensagem de aviso.

Exemplo:

> (ERRO) Seu caminhão foi destruído e a entrega foi cancelada.

### 6.3. Jogador tenta usar `/carregar` sem estar em caminhão do job

- Apenas mostrar mensagem de erro:

> (ERRO) Você precisa estar em um caminhão da profissão para iniciar uma entrega.

---

## 7. Organização de Arquivos

Sugestão de organização dentro do projeto atual:

- Arquivo da profissão caminhoneiro: `include/modules/jobs/job_trucker.inc`

Dentro dele:

1. **Defines e constantes:**

   - IDs de veículos (TRUCK_MODEL, TRAILER_MODEL, etc.).
   - Coordenadas do hub de caminhoneiro em Los Santos.
   - Lista de rotas (`TruckerRoutes`).

2. **Variáveis globais da profissão:**

   - Arrays de estado por jogador (entrega ativa, veículo, início, destino etc.).

3. **Funções internas:**

   - `Trucker_CreateVehicles()` → cria caminhões/trailers do job.
   - `Trucker_StartDelivery(playerid)` → inicia entrega (usado por `/carregar`).
   - `Trucker_FinishDelivery(playerid)` → finaliza, calcula pagamento.
   - `Trucker_CancelDelivery(playerid)` → trata cancelamento.

4. **Callbacks / integração com o modo de jogo:**

   - `Trucker_OnGameModeInit()` → chamado pelo `jobs.inc`.
   - `Trucker_OnPlayerEnterVehicle(playerid, vehicleid)`.
   - `Trucker_OnPlayerEnterCheckpoint(playerid)`.

5. **Comandos:**

   - `CMD:carregar(playerid, params[])`.
   - `CMD:cancelar(playerid, params[])` (opcional).

---

## 8. Como Integrar com o Sistema de Jobs Geral

No arquivo `include/modules/jobs/jobs.inc` (geral):

- Ter uma função de inicialização global:

```pawn
stock Jobs_OnGameModeInit()
{
    Trucker_OnGameModeInit();
    // Futuro: outras profissões
    return 1;
}
```

No `main.pwn`:

- Dentro de `OnGameModeInit()` chamar:

```pawn
Jobs_OnGameModeInit();
```

- E nos callbacks relevantes encaminhar eventos para o job, por exemplo:

```pawn
public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
    Trucker_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
    return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
    Trucker_OnPlayerEnterCheckpoint(playerid);
    return 1;
}
```

---

## 9. Possíveis Extensões Futuras (sem quebrar o sistema atual)

As ideias abaixo podem ser adicionadas **depois**, sem mudar a base do sistema:

1. **Categorias de rotas** (curtas, médias, longas) com valores de pagamento diferentes.
2. **Sistema de XP/Nível de caminhoneiro**:

   - XP baseado no valor da entrega.
   - Liberação de rotas mais longas conforme o nível.

3. **Cargas diferentes** (comum, combustível, industrial), alterando pequenos detalhes no pagamento.
4. **Ranking de caminhoneiros**:

   - Total entregue.
   - Distância total.
   - Maiores pagamentos.

5. **Eventos especiais de entrega**:

   - Missões raras com pagamento alto.
   - Comboios com vários caminhoneiros.

---

## 9.3. Restrições de uso dos caminhões da profissão

Para impedir que jogadores de fora da profissão utilizem os caminhões:

- Cada caminhão do spawn será marcado internamente com um identificador da profissão.
- Ao jogador entrar no veículo, será verificado se ele pertence ao job Caminhoneiro.
- Caso não pertença, é removido do veículo e recebe uma mensagem padronizada.

### Como isso será implementado no código:

```pawn
// Array que marca se um veículo pertence à profissão caminhoneiro
new bool:IsTruckerVehicle[MAX_VEHICLES];
```

Ao criar os veículos do job:

```pawn
IsTruckerVehicle[vehicleid] = true;
```

Ao entrar em qualquer veículo:

```pawn
if (IsTruckerVehicle[vehicleid] && PlayerJob[playerid] != JOB_TRUCKER)
{
    RemovePlayerFromVehicle(playerid);
    SendError(playerid, "Este veículo é exclusivo da profissão Caminhoneiro.");
    return 1;
}
```

---

## 9.4. Comandos /carregar e /descarregar

### `/carregar`

Inicia o processo de pegar uma carga após o jogador entrar em um caminhão da profissão.

Fluxo:

1. Jogador está dentro de um caminhão do job.
2. `/carregar` seleciona um destino.
3. Cria o checkpoint.
4. Registra as coordenadas de início.
5. Começa a entrega.

Mensagem de retorno:

> (INFO) Carga iniciada! Siga o ponto no mapa para realizar a entrega.

---

### `/descarregar`

Finaliza a entrega quando o jogador já está no checkpoint.

Fluxo:

1. Jogador entra no checkpoint.
2. `/descarregar` calcula distância.
3. Aplica pagamentos e bônus.
4. Finaliza o estado da entrega.
5. Permite iniciar uma nova com `/carregar`.

Mensagem de retorno:

> (SUCESSO) Entrega finalizada! Você recebeu $X.

---

## 9.5. Sistema de pagamento com teto

Para evitar que jogadores tentem rodar indefinidamente para aumentar o pagamento, o sistema terá:

- **Distância base:** calculada diretamente entre ponto de saída e de destino.
- **Teto de pagamento:** valor máximo permitido para entrega.

### Exemplo:

```pawn
Float:dist = GetDistanceBetweenPoints(startX, startY, startZ, destX, destY, destZ);
Float:pay = dist * 0.25;
if (pay > 6000.0) pay = 6000.0; // teto de pagamento
```

Isso mantém o sistema justo e simples.

---

## 10. Resumo Final

A profissão de caminhoneiro foi desenhada para:

- Ser **simples de implementar agora**.
- Ser **divertida para o jogador**, com foco em dirigir pela San Andreas.
- Recompensar pela **distância percorrida**, sem incentivar correria.
- Começar sempre a partir de um **hub em Los Santos**, indo para diversos destinos (cidades pequenas, LV, SF, fazendas etc.).
- Ter uma base limpa que permite crescimento futuro (XP, cargas especiais, ranking, etc.) sem necessidade de reescrever o core do sistema.

Quando você estiver pronto para implementar, basta transformar cada seção deste documento em código dentro de `job_trucker.inc`, conectando com o sistema de jobs e os callbacks principais do gamemode.

---

# Profissão Caminhoneiro – Design Detalhado (Versão Simples e Divertida)

## 1. Visão Geral da Profissão

A profissão de Caminhoneiro neste servidor será:

- Simples de entender e jogar.
- Divertida e recompensadora.
- Baseada em saídas de Los Santos.
- Pagamento por distância percorrida.
- Expandível no futuro.

Fluxo básico:

1. Jogador pega caminhão no pátio em Los Santos.
2. Usa `/carregar`.
3. Dirige até o destino.
4. Recebe pagamento.

## 2. Conceitos Centrais

### 2.1. Hub em Los Santos

- Local fixo com caminhões exclusivos da profissão.
- Todas as rotas começam aqui.

### 2.2. Fluxo da Entrega

1. Entra no caminhão do job.
2. `/carregar` inicia a entrega.
3. Checkpoint aparece no mapa.
4. Jogador dirige até o destino.
5. Sistema calcula pagamento por distância.
6. Limpa a entrega.

## 3. Estrutura de Dados

### 3.1. Rotas

```pawn
enum e_route {
    Float:RouteX,
    Float:RouteY,
    Float:RouteZ
}

new Float:TruckerRoutes[][e_route] = {
    { 655.16, -528.22, 16.80 },
    { 200.52, -110.42, 1.55 },
    { 1350.22, 260.44, 19.55 },
    { -2156.22, -2444.88, 30.60 },
    { 2035.51, 1342.22, 10.60 },
    { -1622.22, 707.33, 13.60 }
};
```

### 3.2. Variáveis por Jogador

- `TruckerHasDelivery[playerid]`
- `TruckerRouteIndex[playerid]`
- `TruckerStartX/Y/Z[playerid]`
- `TruckerDestX/Y/Z[playerid]`
- `TruckerVehicle[playerid]`

## 4. Comandos

### 4.1. `/carregar`

Inicia a entrega:

1. Verifica se está em caminhão do job.
2. Escolhe rota aleatória.
3. Registra início e destino.
4. Cria checkpoint.
5. Marca entrega como ativa.

Mensagem de exemplo:

```
(INFO) Você aceitou uma entrega. Siga o marcador no mapa!
```

### 4.2. `/cancelar`

Cancela a entrega e limpa variáveis.
Mensagem:

```
(AVISO) Entrega cancelada.
```

## 5. Pagamento por Distância

### 5.1. Distância

```pawn
Float:dist = GetDistanceBetweenPoints(
    TruckerStartX[playerid], TruckerStartY[playerid], TruckerStartZ[playerid],
    TruckerDestX[playerid], TruckerDestY[playerid], TruckerDestZ[playerid]
);
```

### 5.2. Fórmula

```pawn
Float:basePay = dist * 0.25; // ajustar nos testes
```

### 5.3. Bônus Simples

- +10% se veículo > 900 HP
- +5% bônus noturno

Mensagem de finalização:

```
(SUCESSO) Entrega concluída!
(INFO) Total recebido: $1325
```

## 6. Casos Especiais

- Se entrar em outro veículo → cancela.
- Se caminhão explode → cancela.
- Se usar `/carregar` errado → erro.

## 7. Organização dos Arquivos

### `job_trucker.inc`

Contém:

- Defines
- Rotas
- Variáveis por jogador
- Funções: criar veículos, iniciar entrega, finalizar entrega
- Callbacks da profissão
- Comandos

### `jobs.inc`

Chama:

```pawn
Jobs_OnGameModeInit();
```

E encaminha callbacks para o job.

## 8. Extensões Futuras

- Rotas por nível
- XP de caminhoneiro
- Ranking
- Comboios
- Cargas especiais

## 9. Resumo

A profissão será:

- Simples
- Divertida
- Recompensadora
- Baseada em distância
- Começa sempre em Los Santos

Fluxo final:

```
Pega caminhão → /carregar → dirige → entrega → recebe.
```
