// (teleportes, etc)

CMD:go(playerid, params[])
{

    if (!IsAdmin(playerid, ROLE_MASTER))
        return SendError(playerid, "Você não tem permissão!");      

    new Float:x, Float:y, Float:z;

    // Lê 3 números float
    if (sscanf(params, "fff", x, y, z))
        return SendError(playerid, "Use: /go [x] [y] [z]");

    // Teleporta
    SetPlayerPos(playerid, x, y, z);
    SetCameraBehindPlayer(playerid);

    new msg[96];
    format(msg, sizeof msg, "Você se teleportou para: %.2f, %.2f, %.2f", x, y, z);
    SendSuccess(playerid, msg);

    return 1;
}


// =============================================================
// /cls – Limpa o chat para todos os jogadores (Moderador+)
// =============================================================
CMD:cls(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_MODERATOR))
        return SendError(playerid, "Você não tem permissão!"); 

    // Envia 50 linhas em branco para todos os players
    for (new i = 0; i < 50; i++)
    {
        SendClientMessageToAll(-1, " ");
    }

    // Mensagens informativas
    new adminName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, adminName, sizeof adminName);

    new msg[96];
    format(msg, sizeof msg, "O administrador %s limpou o chat.", adminName);
    SendInfoGlobal(msg);

    return 1;
}

// =============================================================
// /ls Teleporte para Los Santos (Admin1+)
// =============================================================
CMD:ls(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN1))
        return SendError(playerid, "Você não tem permissão para usar este comando!");

    SetPlayerPos(playerid, 1133.43, -1696.91, 13.72);
    SetPlayerFacingAngle(playerid, 185.46);

    CmdAdmin(playerid, "Você foi teleportado para Los Santos.");
    return 1;
}

// =============================================================
// /sf Teleporte para San Fierro (Admin1+)
// =============================================================
CMD:sf(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN1))
        return SendError(playerid, "Você não tem permissão para usar este comando!");

    SetPlayerPos(playerid, -2025.62, 143.87, 28.83);
    SetPlayerFacingAngle(playerid, 267.46);

    CmdAdmin(playerid, "Você foi teleportado para San Fierro.");
    return 1;
}

// =============================================================
// /lv Teleporte para Las Venturas (Admin1+)
// =============================================================
CMD:lv(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN1))
        return SendError(playerid, "Você não tem permissão para usar este comando!");

    SetPlayerPos(playerid, 2025.47, 1342.82, 10.82);
    SetPlayerFacingAngle(playerid, 270.11);

    CmdAdmin(playerid, "Você foi teleportado para Las Venturas.");
    return 1;
}

// =============================================================
// /pos Salvar posição do jogador (MASTER)
// Log: scriptfiles/savedpositions/player_positions.log
// =============================================================
stock GetCurrentDateTime(outDate[], dateSize)
{
    new year, month, day;
    new hour, minute, second;

    getdate(year, month, day);
    gettime(hour, minute, second);

    format(outDate, dateSize, "%02d/%02d/%d %02d:%02d:%02d",
        day, month, year, hour, minute, second);
}

CMD:pos(playerid)
{
    if (!IsAdmin(playerid, ROLE_MASTER))
        return SendError(playerid, "Você não tem permissão!");

    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new year, month, day, hour, minute, second;
    getdate(year, month, day);
    gettime(hour, minute, second);

    new File:fp = fopen("savedpositions/player_positions.log", io_append);

    if (!fp)
        return SendError(playerid, "Não foi possível abrir o arquivo de posições!");

    new line[256];
    // format(line, sizeof line,
    //     "[%02d/%02d/%04d %02d:%02d:%02d] X: %.2f | Y: %.2f | Z: %.2f | ANG: %.2f\r\n",
    //     day, month, year, hour, minute, second, x, y, z, a);
    format(line, sizeof line,
        "[%02d/%02d/%04d %02d:%02d:%02d] { %.2f, %.2f, %.2f, %.2f }\r\n",
        day, month, year, hour, minute, second, x, y, z, a);

    fwrite(fp, line);
    fclose(fp);

    new msg[128];
    format(msg, sizeof msg,
        "[AdminCMD] Posição salva! [X: %.2f | Y: %.2f | Z: %.2f | ANG: %.2f]",
        x, y, z, a);

    SendClientMessage(playerid, COLOR_ADMIN, msg);
    return 1;
}

CMD:asf(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN1))
        return SendError(playerid, "Você não tem permissão para usar este comando!");

    SetPlayerPos(playerid, 1456.66, -2593.36, 13.54);
    SetPlayerFacingAngle(playerid, 270.03);

    CmdAdmin(playerid, "Você foi teleportado para aeroporto de Los Santos.");
    return 1;
}

CMD:spawn(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    // Apenas aplicar um spawn novo
    SpawnPlayerRandom(playerid);

    SendInfo(playerid, "Você foi levado para um local aleatório de spawn...");

    return 1;
}


