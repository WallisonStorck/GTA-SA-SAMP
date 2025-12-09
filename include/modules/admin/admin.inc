// =====================================================
// SISTEMA DE roleS ADMINISTRATIVOS
// =====================================================

// Ní­veis de role
#define ROLE_PLAYER      0
#define ROLE_HELPER      1
#define ROLE_MODERATOR   2
#define ROLE_ADMIN1      3
#define ROLE_ADMIN2      4
#define ROLE_MASTER      5



// Nome do Master (dono do servidor)
#define MASTER_NAME "Storck"


// =====================================================
// Admin_GetName
//  - Converte o nÃ­vel numÃ©rico em um texto legÃ­vel
//  - Exemplo: 3 -> "Administrador NÃ­vel 1"
// =====================================================
stock Admin_GetName(level, dest[], size)
{
    switch (level)
    {
        case ROLE_PLAYER:
        {
            format(dest, size, "Jogador");
        }
        case ROLE_HELPER:
        {
            format(dest, size, "Ajudante");
        }
        case ROLE_MODERATOR:
        {
            format(dest, size, "Moderador");
        }
        case ROLE_ADMIN1:
        {
            format(dest, size, "Administrador Nível 1");
        }
        case ROLE_ADMIN2:
        {
            format(dest, size, "Administrador Nível 2");
        }
        case ROLE_MASTER:
        {
            format(dest, size, "Master Admin");
        }
        default:
        {
            format(dest, size, "Desconhecido");
        }
    }
    return 1;
}


// =====================================================
// IsAdmin
//  - Verifica se o player tem pelo menos o nÃ­vel X
//  - Exemplo: IsAdmin(id, ROLE_MODERATOR) -> true se
//    AdminLevel >= 2
// =====================================================
/*
stock IsAdmin(playerid, level)
{
    return (PlayerData[playerid][AdminLevel] >= level);
}
*/

// ======================================================
// MODO TEMPORÃRIO â€” ENQUANTO NÃƒO TEM SISTEMA DE LOGIN
// Se o nome for "Storck", ele sempre passa como MASTER
// ======================================================
stock IsAdmin(playerid, level)
{
    new pname[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pname, sizeof(pname));

    // VocÃª Ã© sempre MASTER durante o desenvolvimento
    if (strcmp(pname, MASTER_NAME, true) == 0)
        return 1;

    // Funcionamento normal para todos os outros
    return (PlayerData[playerid][AdminLevel] >= level);
}


// =====================================================
// ValidateAdminOnLogin
//  - Protege contra ediÃ§Ã£o manual de .ini
//  - Se alguÃ©m tentar se dar role alto (ADMIN2+)
//    sem ser o MASTER_NAME, zera o role.
// =====================================================
/*
stock ValidateAdminOnLogin(playerid)
{
    new pname[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pname, sizeof(pname));

    if (PlayerData[playerid][AdminLevel] > ROLE_MODERATOR &&
        strcmp(pname, MASTER_NAME, true) != 0)
    {
        PlayerData[playerid][AdminLevel] = ROLE_PLAYER;

        new path[128];
        Player_GetAccountPath(playerid, path, sizeof(path));

        // Evitar warning 239 (string literal):
        new key_admin[] = "AdminLevel";
        DOF2_SetInt(path, key_admin, 0);
        DOF2_SaveFile();

        printf("[SECURITY] Conta %s tentou obter admin ilegalmente. role resetado.", pname);
    }
}
*/


// =====================================================
// ShowAdminLoginMessage
//  - Mostra mensagem com o role do jogador ao logar
// =====================================================
stock ShowAdminLoginMessage(playerid)
{
    if (PlayerData[playerid][AdminLevel] > ROLE_PLAYER)
    {
        new role[32];
        Admin_GetName(PlayerData[playerid][AdminLevel], role, sizeof role);

        new msg[96];
        format(msg, sizeof msg,
            "(INFO) Seu role atual: %s.",
            role);

        SendClientMessage(playerid, COLOR_INFO, msg);
    }
}


// =====================================================
// /setCargo â€“ Define o role de um jogador
//  - Uso: /setcargo [id] [cargo 0-5]
//  - Apenas MASTER pode usar
// =====================================================
CMD:setcargo(playerid, params[])
{
    // Apenas Master (ROLE_MASTER) pode mexer em role
    if (!IsAdmin(playerid, ROLE_MASTER))
        return SendError(playerid, "Você não tem permissão para usar este comando.");

    new targetid, role;
    if (sscanf(params, "ii", targetid, role))
        return SendError(playerid, "Use: /setCargo [id] [cargo 0-5]");

    if (!IsPlayerConnected(targetid))
        return SendError(playerid, "Jogador inválido.");

    if (role < ROLE_PLAYER || role > ROLE_MASTER)
        return SendError(playerid, "Cargo inválido. Use valores entre 0 e 5.");

    // Atualiza em memória
    PlayerData[targetid][AdminLevel] = role;

    // Atualiza no arquivo da conta
    new path[128];
    Player_GetAccountPath(targetid, path, sizeof(path));

    // new key_admin[] = "AdminLevel"; // para evitar warning 239
    // DOF2_SetInt(path, key_admin, role);
    // DOF2_SaveFile();

    // Pega nome do alvo
    new tname[MAX_PLAYER_NAME];
    GetPlayerName(targetid, tname, sizeof tname);

    // Pega nome do role em texto
    new role_name[32];
    Admin_GetName(role, role_name, sizeof role_name);

    // Mensagem para você (MASTER)
    new msg[128];
    format(msg, sizeof msg,
        "(SUCESSO) O cargo de %s agora é: %s.",
        tname, role_name);
    CmdAdmin(playerid, msg);

    // Mensagem para o alvo
    format(msg, sizeof msg,
        "Seu novo role: %s.",
        role_name);
    SendInfo(targetid, msg);

    return 1;
}
