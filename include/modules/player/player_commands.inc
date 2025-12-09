// #pragma once


// #include "../../core/gl_messages.inc"

CMD:registrar(playerid, params[])
{
    new senha[64];
    if (sscanf(params, "s[64]", senha))
        return SendError(playerid, "USE: /registrar <senha>");

    new path[128];
    Player_GetAccountPath(playerid, path, sizeof(path));

    // if (DOF2_FileExists(path))
    //     return SendError(playerid, "(INFO) Esta conta jÃ¡ existe! Use /logar.");

    format(PlayerData[playerid][Password], 64, "%s", senha);
    PlayerData[playerid][IsLogged] = true;

    Player_SaveAccount(playerid);
    SendInfo(playerid, "Conta registrada e logada!");
    return 1;
}

CMD:logar(playerid, params[])
{
    new senha[64];
    if (sscanf(params, "s[64]", senha))
        return SendError(playerid, "USE: /logar <senha>");

    if (PlayerData[playerid][IsLogged])
        return SendError(playerid, "Você já está logado!");

    if (!strcmp(senha, PlayerData[playerid][Password], false))
    {
        PlayerData[playerid][IsLogged] = true;
        SendInfo(playerid, "Login realizado com sucesso!");
        return 1;
    }

    return SendError(playerid, "Senha incorreta!");
}

CMD:stats(playerid)
{
    new msg[200];
    format(msg, sizeof(msg), "Level: %d | Dinheiro: %d",
        PlayerData[playerid][Level],
        PlayerData[playerid][Money]
    );

    SendInfo(playerid, msg);
    return 1;
}

CMD:p(playerId, params[])
{
    if (isnull(params))
        return SendError(playerId, "Use: /p [mensagem]");

    SendLocalChat(playerId, params);
    return 1;
}










