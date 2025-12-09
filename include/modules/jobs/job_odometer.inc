// ============================================================================
//  job_odometer.inc — Sistema de Odômetro (contagem de distância percorrida)
//  Exibe textdraw acima do radar (HUD)
// ============================================================================

#if defined _JOB_ODOMETER_
    #endinput
#endif
#define _JOB_ODOMETER_

// #include "../../core/utils.inc"
// #include "../../core/messages.inc"

// ------------------------------
// Variáveis por jogador
// ------------------------------
new bool:OdoActive[MAX_PLAYERS];
new Float:OdoLastX[MAX_PLAYERS];
new Float:OdoLastY[MAX_PLAYERS];
new Float:OdoLastZ[MAX_PLAYERS];
new Float:OdoDistance[MAX_PLAYERS];   // distância total em metros
new OdoTimer[MAX_PLAYERS] = { -1, ... };

// ------------------------------
// Textdraw do odômetro
// ------------------------------
new PlayerText:OdoTD[MAX_PLAYERS];

stock Odometer_UpdateTD(playerid)
{
    if (!OdoActive[playerid]) return;

    new text[64];
    format(text, sizeof text, "~w~Odômetro: ~g~%.2f km", (OdoDistance[playerid] / 1000.0));

    PlayerTextDrawSetString(playerid, OdoTD[playerid], text);
    PlayerTextDrawShow(playerid, OdoTD[playerid]);
}

// ------------------------------
// Timer — atualiza distância percorrida
// ------------------------------
forward Odometer_Tick(playerid);
public Odometer_Tick(playerid)
{
    if (!OdoActive[playerid]) return 0;

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    new Float:dist = GetDistanceBetweenPoints(
        OdoLastX[playerid],
        OdoLastY[playerid],
        OdoLastZ[playerid],
        x, y, z
    );

    // atualiza distância total
    if (dist > 0.1)  // movimento mínimo
        OdoDistance[playerid] += dist;

    // salva posição atual
    OdoLastX[playerid] = x;
    OdoLastY[playerid] = y;
    OdoLastZ[playerid] = z;

    Odometer_UpdateTD(playerid);

    return 1;
}

// ------------------------------
// Criar o textdraw acima do radar
// ------------------------------
stock Odometer_CreateTD(playerid)
{
    OdoTD[playerid] = CreatePlayerTextDraw(playerid, 505.0, 390.0, "Odômetro: 0.00 km");
    PlayerTextDrawFont(playerid, OdoTD[playerid], 1);
    PlayerTextDrawLetterSize(playerid, OdoTD[playerid], 0.28, 1.1);
    PlayerTextDrawColor(playerid, OdoTD[playerid], 0xFFFFFFFF);
    PlayerTextDrawOutline(playerid, OdoTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, OdoTD[playerid], 1);
    PlayerTextDrawSetShadow(playerid, OdoTD[playerid], 0);
}

// ------------------------------
// Comando: iniciar odômetro
// ------------------------------
CMD:odoiniciar(playerid, params[])
{
    if (OdoActive[playerid])
        return SendWarning(playerid, "O odômetro já está ativo.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    // resetar dados
    OdoActive[playerid] = true;
    OdoDistance[playerid] = 0.0;
    OdoLastX[playerid] = x;
    OdoLastY[playerid] = y;
    OdoLastZ[playerid] = z;

    // criar textdraw se necessário
    if (!PlayerTextDrawGetString(playerid, OdoTD[playerid]))
        Odometer_CreateTD(playerid);

    PlayerTextDrawShow(playerid, OdoTD[playerid]);

    // iniciar timer (200 ms)
    OdoTimer[playerid] = SetTimerEx("Odometer_Tick", 200, true, "i", playerid);

    SendSuccess(playerid, "Odômetro iniciado.");
    return 1;
}

// ------------------------------
// Comando: parar odômetro
// ------------------------------
CMD:odoparar(playerid, params[])
{
    if (!OdoActive[playerid])
        return SendError(playerid, "O odômetro não está ativo.");

    OdoActive[playerid] = false;

    // matar timer
    if (OdoTimer[playerid] != -1)
    {
        KillTimer(OdoTimer[playerid]);
        OdoTimer[playerid] = -1;
    }

    PlayerTextDrawHide(playerid, OdoTD[playerid]);

    new msg[96];
    format(msg, sizeof msg, "Distância total percorrida: %.2f km", (OdoDistance[playerid] / 1000.0));
    SendInfo(playerid, msg);

    return 1;
}

// ------------------------------
// Reset ao desconectar
// ------------------------------
public OnPlayerDisconnect(playerid, reason)
{
    if (OdoTimer[playerid] != -1)
        KillTimer(OdoTimer[playerid]);

    OdoActive[playerid] = false;
    return 1;
}
