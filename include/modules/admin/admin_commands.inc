/*============================================================================
 ARQUIVO: admin_commands.inc
 DESCRIÇÃO:
     Este arquivo funciona como o INDEX central do sistema administrativo.
     Ele NÃO contém comandos diretamente. Sua função é apenas reunir,
     organizar e importar todos os módulos administrativos do servidor.

     A organização modular permite:
       • Código mais limpo e fácil de manter
       • Separação clara entre diferentes grupos de comandos
       • Possibilidade de habilitar/desabilitar módulos rapidamente
       • Melhor legibilidade e escalabilidade do sistema admin

     ESTRUTURA ATUAL DOS MÓDULOS:
       - admin_core.inc        ? Funções essenciais (IsAdmin, cargos, Master)
       - admin_basic.inc       ? Comandos básicos (teleportes, repair, flip)
       - admin_player.inc      ? Comandos que afetam jogadores (vida, skin)
       - admin_vehicle.inc     ? Comandos de veículos (car, poscar, etc.)
       - admin_special.inc     ? Ações especiais (jetpack, futuros modos)

     IMPORTANTE:
       Este arquivo deve ser incluído no main.pwn:
             #include "../include/modules/admin/admin_commands.inc"

       Todo comando administrativo DEVE existir dentro dos módulos acima,
       nunca diretamente neste arquivo.

 AUTOR: Wallison Storck
 SISTEMA: Administração geral do servidor SA-MP
============================================================================*/

#include "../include/modules/admin/admin_core.inc"
#include "../include/modules/admin/admin_basic.inc"
#include "../include/modules/admin/admin_player.inc"
#include "../include/modules/admin/admin_vehicle.inc"
#include "../include/modules/admin/admin_special.inc"

