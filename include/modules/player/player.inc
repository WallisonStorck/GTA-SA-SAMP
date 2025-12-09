// ============================================================================
//  Player System (Account / Login / Save)
//  Uses: scriptfiles/accounts/NAME.ini
// ============================================================================

forward Player_OnConnect(playerid);
forward Player_OnDisconnect(playerid, reason);
forward Player_OnSpawn(playerid);


//  INTERNAL: Remove \r\n ao ler linhas
stock StripNewLine(str[])
{
    new len = strlen(str);
    while (len > 0 && (str[len - 1] == '\r' || str[len - 1] == '\n'))
    {
        str[len - 1] = '\0';
        len--;
    }
    return 1;
}


stock Player_OnConnect(playerid)
{
    PlayerData[playerid][IsLogged]   = false;
    PlayerData[playerid][Level]      = 1;
    PlayerData[playerid][Money]      = 500;
    // PlayerData[playerid][AdminLevel] = ROLE_PLAYER;

    Player_LoadAccount(playerid);
    ShowAdminLoginMessage(playerid);
    return 1;
}


stock Player_OnDisconnect(playerid, reason)
{
    #pragma unused reason

    if (PlayerData[playerid][IsLogged])
        Player_SaveAccount(playerid);

    return 1;
}


stock Player_OnSpawn(playerid)
{
    GivePlayerMoney(playerid, PlayerData[playerid][Money]);
    return 1;
}


stock Player_GetAccountPath(playerid, path[], size)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    format(path, size, "accounts/%s.ini", name);
    return 1;
}


stock Player_LoadAccount(playerid)
{
    new path[128];
    Player_GetAccountPath(playerid, path, sizeof(path));

    // Verifica se arquivo existe
    if (!fexist(path))
    {
        SendInfo(playerid, "Conta nao encontrada! Use /registrar <senha>.");
        return 0;
    }

    new File:f = fopen(path, io_read);
    if (!f)
    {
        SendError(playerid, "Não foi possível abrir arquivo da conta!");
        return 0;
    }

    new line[64];

    // Linha 1 ? Senha
    if (fread(f, line))
    {
        StripNewLine(line);
        format(PlayerData[playerid][Password], 32, "%s", line);
    }

    // Linha 2 ? Level
    if (fread(f, line))
    {
        StripNewLine(line);
        PlayerData[playerid][Level] = strval(line);
    }

    // Linha 3 ? Money
    if (fread(f, line))
    {
        StripNewLine(line);
        PlayerData[playerid][Money] = strval(line);
    }

    // Linha 4 ? AdminLevel (Role)
    if (fread(f, line))
    {
        StripNewLine(line);
        PlayerData[playerid][AdminLevel] = strval(line);
    }

    fclose(f);

    SendInfo(playerid, "Conta carregada. Use /login <password>.");
    return 1;
}


stock Player_SaveAccount(playerid)
{
    new path[128];
    Player_GetAccountPath(playerid, path, sizeof(path));

    new File:f = fopen(path, io_write);
    if (!f)
    {
        SendError(playerid, "Erro ao salvar conta!");
        return 0;
    }

    new buffer[64];

    // Linha 1 ? Senha
    format(buffer, sizeof buffer, "%s\r\n", PlayerData[playerid][Password]);
    fwrite(f, buffer);

    // Linha 2 ? Level
    format(buffer, sizeof buffer, "%d\r\n", PlayerData[playerid][Level]);
    fwrite(f, buffer);

    // Linha 3 ? Money
    format(buffer, sizeof buffer, "%d\r\n", PlayerData[playerid][Money]);
    fwrite(f, buffer);

    // Linha 4 ? AdminLevel
    format(buffer, sizeof buffer, "%d\r\n", PlayerData[playerid][AdminLevel]);
    fwrite(f, buffer);

    fclose(f);
    return 1;
}
