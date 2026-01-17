// =============================================================
//  JOB: SCRAP (Carcaças de Veículos)
//  Responsável por transformar veículos destruídos em carcaças
//  Base para futura profissão de sucateiro / lixeiro
// =============================================================

#if defined _JOB_SCRAP_INC_
    #endinput
#endif
#define _JOB_SCRAP_INC_


// =============================================================
//  CONFIGURAÇÕES GERAIS
// =============================================================

// ID do objeto de carcaça
#define SCRAP_WRECK_OBJECT_ID   3594

// Tempo (em milissegundos) para criar a carcaça após explosão
// 10 segundos = 10000
#define SCRAP_WRECK_DELAY_MS   10000


// =============================================================
//  VARIÁVEIS INTERNAS DO SISTEMA
// =============================================================

// Timer por veículo (evita duplicação)
new Scrap_WreckTimer[MAX_VEHICLES];

// Última posição conhecida do veículo destruído
new Float:Scrap_LastX[MAX_VEHICLES];
new Float:Scrap_LastY[MAX_VEHICLES];
new Float:Scrap_LastZ[MAX_VEHICLES];
new Float:Scrap_LastA[MAX_VEHICLES];


// =============================================================
//  CALLBACK: VEÍCULO DESTRUÍDO
//  Chamado automaticamente quando um veículo explode
// =============================================================
public OnVehicleDeath(vehicleid, killerid)
{
    // Salva a posição final do veículo
    GetVehiclePos(
        vehicleid,
        Scrap_LastX[vehicleid],
        Scrap_LastY[vehicleid],
        Scrap_LastZ[vehicleid]
    );

    GetVehicleZAngle(vehicleid, Scrap_LastA[vehicleid]);

    // Evita múltiplos timers no mesmo veículo
    if (Scrap_WreckTimer[vehicleid] != 0)
    {
        KillTimer(Scrap_WreckTimer[vehicleid]);
        Scrap_WreckTimer[vehicleid] = 0;
    }

    // Agenda a criação da carcaça após o delay configurado
    Scrap_WreckTimer[vehicleid] = SetTimerEx(
        "Scrap_CreateWreck",
        SCRAP_WRECK_DELAY_MS,
        false,
        "i",
        vehicleid
    );

    return 1;
}


// =============================================================
//  FUNÇÃO: CRIA A CARCAÇA APÓS O DELAY
// =============================================================
forward Scrap_CreateWreck(vehicleid);
public Scrap_CreateWreck(vehicleid)
{
    // Limpa o timer
    Scrap_WreckTimer[vehicleid] = 0;

    // Pequeno ajuste no Z para evitar carcaça enterrada
    new Float:z = Scrap_LastZ[vehicleid] - 0.5;

    // Cria a carcaça no local da explosão
    CreateObject(
        SCRAP_WRECK_OBJECT_ID,
        Scrap_LastX[vehicleid],
        Scrap_LastY[vehicleid],
        z,
        0.0,
        0.0,
        Scrap_LastA[vehicleid]
    );

    return 1;
}


// =============================================================
//  PONTO DE ENTRADA DO MÓDULO
//  (Chamado pelo jobs.inc no OnGameModeInit)
// =============================================================
stock Scrap_OnGameModeInit()
{
    print("[SCRAP] Sistema de carcaças carregado.");
    return 1;
}


// ===============================================================
//  FUTURAS EXTENSÕES (DOCUMENTAÇÃO)
// ===============================================================
/*
    Ideias para evolução do job_scrap:

    - /recolher:
        * Player vai até a carcaça
        * Remove objeto
        * Dá dinheiro ou material reciclável

    - Integração com Towtruck:
        * Engatar carcaça
        * Levar até ferro-velho
        * Pagamento maior

    - Sistema de profissão:
        * Apenas jogadores com job SCRAP podem interagir
        * Níveis de sucateiro

    - Limpeza automática:
        * Carcaça some após X minutos
*/
