# 📌 Storck SA-MP Server

Bem-vindo ao repositório oficial do **Servidor SA-MP by Storck**. Este projeto tem como objetivo criar um modo de jogo estruturado, organizado, modularizado e altamente expansível para futuros sistemas, incluindo administração, economia, contas, veículos, jogadores e muito mais.

---

## 📂 Estrutura do Projeto

A organização segue uma arquitetura modular para facilitar manutenção e evolução:

```
include/
│
├── core/
│   ├── globals.inc          // Variáveis globais, cores, enums principais
│   ├── functions.inc        // Funções auxiliares essenciais
│   └── ...
│
├── modules/
│   ├── admin/               // Tudo relacionado a comandos e sistemas administrativos
│   │   ├── admin.inc
│   │   ├── admin_core.inc
│   │   ├── admin_basic.inc
│   │   ├── admin_player.inc
│   │   ├── admin_vehicle.inc
│   │   └── admin_special.inc
│   │
│   ├── player/              // Sistema do jogador
│   ├── vehicles/            // Gerenciamento de veículos
│   └── ...
│
├── savedpositions/          // Arquivos gerados por comandos /pos e /poscar
└── ...
```

---

## 🛠️ Sistema de Administração

O servidor utiliza um sistema completo de cargos:

| Cargo         | Código | Descrição                             |
| ------------- | ------ | ------------------------------------- |
| Jogador comum | 0      | Nenhum acesso administrativo          |
| Ajudante      | 1      | Suporte básico                        |
| Moderador     | 2      | Acesso a comandos de moderação        |
| Admin Nível 1 | 3      | Ações administrativas básicas         |
| Admin Nível 2 | 4      | Acesso avançado                       |
| Master        | 5      | Administrador supremo (apenas Storck) |

Todos os comandos usam a função:

```
IsAdmin(playerid, CARGO_X)
```

O Master também possui:

```
IsMaster(playerid)
```

---

## 🧩 Comandos Principais

A lista completa está dividida nos arquivos dentro de `modules/admin/`.
Aqui estão algumas categorias:

### 🚗 Veículos

- `/car` – cria veículo
- `/repair` – repara veículo
- `/flip` – desvira veículo
- `/nitro` – adiciona nitro 10x

### ❤️ Jogador

- `/sethp` – define vida
- `/setar` – define colete
- `/setcash` – define dinheiro
- `/givegun` – dá qualquer arma
- `/setskin` – altera skin
- `/heal` – cura completamente

### 📍 Utilidade

- `/pos` – salva posição do player
- `/poscar` – salva posição do veículo
- `/clearchat` – limpa chat

### 🛩️ Recursos especiais

- `/jet` – jetpack exclusivo do Master

---

## 🔧 Sistema de Salvamento (Arquivo)

As posições são gravadas via `fopen/fwrite/fclose` utilizando um único arquivo por tipo:

`include/savedpositions/player_positions.txt`
`include/savedpositions/vehicle_positions.txt`

Cada linha tem estrutura:

```
[DD/MM/YYYY HH:MM:SS] X:0.00 | Y:0.00 | Z:0.00 | A:0.00
```

---

## Funcionalidades Pendentes

O servidor já possui uma base sólida e modular, mas ainda há vários sistemas planejados para enriquecer a jogabilidade. Abaixo está a lista oficial do que será desenvolvido:

### 🔧 Sistemas Planejados

- **Sistema de XP e Level-UP** — progressão do jogador com recompensas configuráveis.
- **Sistema de Relógio** — horário global sincronizado, com suporte a dia/noite customizado.
- **Sistema de AFK** — detecção de inatividade com notify automático.
- **Sistema de Profissões** — trabalhos legais (ex: caminhoneiro, lenhador, mecânico, taxista) e árvores de evolução.
- **Sistema de Login/Registro** — contas salvas com senha, estatísticas e permissões persistentes.

- Criar painel de administração dentro do jogo
- Implementar sistema de contas com criptografia de senha
- Criar logs estruturados para cada ação administrativa
- Criar sistema de casas, empregos, economia e veículos próprios

---

## 🚀 Como Compilar o Projeto

1. Instale o **SA-MP Server Package**
2. Configure o `pawn.cfg` com caminhos completos dos includes
3. Abra o Pawno pelo diretório do servidor:

```
C:\MyServerStorcks\pawno\pawncc.exe
```

4. Compile o gamemode.

---

## 👤 Sobre o Desenvolvedor

Projeto criado e mantido por **Storck**, professor universitário e desenvolvedor.

Se quiser adicionar seus créditos ou changelog, posso colocar aqui também.

---

## 📬 Contribuição

Por enquanto, o repositório é fechado para contribuições externas.
Em breve serão abertas issues e pull requests.
