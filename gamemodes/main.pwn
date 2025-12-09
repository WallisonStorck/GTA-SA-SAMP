#include <a_samp>
#include <sscanf2>
#include <zcmd>

// Core
#include "../include/core/globals.inc"
#include "../include/core/messages.inc"
#include "../include/core/spawns.inc"
#include "../include/core/utils.inc"


// Modules
#include "../include/modules/player/player.inc"
#include "../include/modules/player/player_commands.inc"
#include "../include/modules/admin/admin.inc"
#include "../include/modules/admin/admin_commands.inc"
#include "../include/modules/vehicles/vehicles.inc"
#include "../include/modules/jobs/jobs.inc"


main()
{
    print("\n---------------------------------------------------------------");
    print("  Bem-vindo ao meu servidor SAMP by: Storck");
    print("\n---------------------------------------------------------------");
}

public OnGameModeInit()
{
    DisableInteriorEnterExits(); // Remove casas padrão e interior automático

    CreateFixedVehicles(); // Criar veículos fixos do servidor

    Jobs_OnGameModeInit(); // Inicializa sistema de profissões

    return 1;
}

public OnPlayerConnect(playerid)
{
    SendClientMessage(playerid, COLOR_INFO, " ");
    SendClientMessage(playerid, COLOR_INFO, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    SendClientMessage(playerid, COLOR_INFO, "   Bem-vindo ao meu servidor SAMP by: Storck ");
    SendClientMessage(playerid, COLOR_INFO, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"); 
    SendClientMessage(playerid, COLOR_INFO, " "); 

    Player_OnConnect(playerid);
    return 1;
}


public OnPlayerDisconnect(playerid, reason)
{
    Player_OnDisconnect(playerid, reason);
    return 1;
}

public OnPlayerSpawn(playerid)
{

    // SetPlayerPos(playerid, 1133.43, -1696.91, 13.72); // Spawn do jogador
    // SetPlayerFacingAngle(playerid, 185.46);
    SetPlayerPos(playerid, 2146.73, -2289.87, 14.76, 242.67); // Spawn caminhoneiro
    SetPlayerFacingAngle(playerid, 242.67);
    SetCameraBehindPlayer(playerid);

    TogglePlayerControllable(playerid, 1); // só por segurança

    GivePlayerMoney(playerid, PlayerData[playerid][Money]); // Manter o sistema de conta
    
    return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    if (TempVehicle[vehicleid])
    {
        DestroyVehicle(vehicleid);
        TempVehicle[vehicleid] = false;
    }

    return 1;
}

public OnGameModeExit()
{

    return 1;
}

