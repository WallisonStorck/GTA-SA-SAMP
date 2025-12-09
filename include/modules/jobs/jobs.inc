// ==========================================================
//  SISTEMA DE PROFISSÕES — ARQUIVO MASTER
//  Este arquivo APENAS inclui os jobs e expõe um ponto de inicialização.
// ==========================================================

#if defined _JOBS_INC_
    #endinput
#endif
#define _JOBS_INC_


// ---------------------------------------------
//  INCLUDES DE TODAS AS PROFISSÕES
// ---------------------------------------------
#include "../include/modules/jobs/job_trucker.inc"
// futuramente:
// #include "job_police.inc"
// #include "job_miner.inc"
// #include "job_farmer.inc"
// etc.


// ==========================================================
//  FUNÇÃO CHAMADA PELO main.pwn PARA INICIALIZAR OS JOBS
//  (Aqui não tem lógica de profissão, só encaminha para cada job.)
// ==========================================================
stock Jobs_OnGameModeInit()
{
    Trucker_OnGameModeInit();   
    // Futuro:
    // Police_OnGameModeInit();
    // Miner_OnGameModeInit();
    // ...

    print("[JOBS] Todas as profissões foram inicializadas.");
    return 1;
}
