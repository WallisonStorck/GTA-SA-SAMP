// (vida, colete, skin, cash)

// =============================================================
// /sethp Define a vida de um jogador (Admin2+)
// Uso: /setHp [id] [vida]
// =============================================================
CMD:sethp(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    new target_id, hp;
    if (sscanf(params, "ii", target_id, hp))
        return SendError(playerid, "Use: /setHp [id] [vida]");

    if (!IsPlayerConnected(target_id))
        return SendError(playerid, "Jogador inválido!");

    if (hp < 0 || hp > 100)
        return SendError(playerid, "A vida deve estar entre 0 e 100.");

    SetPlayerHealth(target_id, float(hp));

    // mensagens
    new pname[MAX_PLAYER_NAME], tname[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pname, sizeof pname);
    GetPlayerName(target_id, tname, sizeof tname);

    new msg_admin[96];
    format(msg_admin, sizeof msg_admin,
        "Vida de %s foi definida para %d.", tname, hp);
    CmdAdmin(playerid, msg_admin);


    new msg_target[128];
    format(msg_target, sizeof msg_target,
        "O administrador %s ajustou sua vida para %d.", pname, hp);
    SendInfo(target_id, msg_target);

    return 1;
}

// =============================================================
// /setar Define o colete de um jogador (Admin2+)
// Uso: /setAr [id] [colete]
// =============================================================
CMD:setar(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    new target_id, armor;
    if (sscanf(params, "ii", target_id, armor))
        return SendError(playerid, "Use: /setAr [id] [colete]");

    if (!IsPlayerConnected(target_id))
        return SendError(playerid, "Jogador inválido!");

    if (armor < 0 || armor > 100)
        return SendError(playerid, "O colete deve estar entre 0 e 100.");

    SetPlayerArmour(target_id, float(armor));

    new pname[MAX_PLAYER_NAME], tname[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pname, sizeof pname);
    GetPlayerName(target_id, tname, sizeof tname);

    new msg_admin[96];
    format(msg_admin, sizeof msg_admin,
        "Colete de %s definido para %d.", tname, armor);
    CmdAdmin(playerid, msg_admin);

    new msg_target[128];
    format(msg_target, sizeof msg_target,
        "O administrador %s ajustou seu colete para %d.", pname, armor);
    SendInfo(target_id, msg_target);

    return 1;
}


// =============================================================
// /setcash Define o dinheiro do jogador (Admin2+)
// Uso: /setcash [id] [quantia]
// =============================================================
CMD:setcash(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    new target_id, amount;
    if (sscanf(params, "ii", target_id, amount))
        return SendError(playerid, "Use: /setCash [id] [valor]");

    if (!IsPlayerConnected(target_id))
        return SendError(playerid, "Jogador inválido!");

    if (amount < 0 || amount > 99999999)
        return SendError(playerid, "Valor fora da faixa permitida!");

    ResetPlayerMoney(target_id);
    GivePlayerMoney(target_id, amount);

    // mensagens
    new pname[MAX_PLAYER_NAME], tname[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pname, sizeof pname);
    GetPlayerName(target_id, tname, sizeof tname);

    new msg_admin[96];
    format(msg_admin, sizeof msg_admin,
        "Dinheiro de %s definido para $%d.", tname, amount);
    CmdAdmin(playerid, msg_admin);

    new msg_target[128];
    format(msg_target, sizeof msg_target,
        "O administrador %s ajustou seu dinheiro para $%d.", pname, amount);
    SendInfo(target_id, msg_target);

    return 1;
}

// =============================================================
// /givegun – Dá qualquer arma ao jogador (Admin2+)
// Uso: /givegun [id] [arma] [munição]
// =============================================================
CMD:givegun(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    new target_id, weapon_id, ammo;

    // Leitura dos parâmetros
    if (sscanf(params, "iii", target_id, weapon_id, ammo))
        return SendError(playerid, "Use: /giveGun [id] [arma] [munição]");

    if (!IsPlayerConnected(target_id))
        return SendError(playerid, "Jogador inválido!");

    // --------------------------------------------
    // VALIDAÇÃO: qualquer arma entre 1 e 46 é ok
    // exceto as armas inexistentes
    // --------------------------------------------
    if (weapon_id < 1 || weapon_id > 46)
        return SendError(playerid, "ID de arma deve estar entre 1 e 46.");


    // IDs que não existem no GTA SA
    if (weapon_id == 19 || weapon_id == 20 || weapon_id == 21 ||
        weapon_id == 44 || weapon_id == 45)
        return SendError(playerid, "Este ID de arma não existe no GTA San Andreas!");

    if (ammo < 1 || ammo > 9999)
        return SendError(playerid, "A munição deve estar entre 1 e 9999.");

    // Entregar arma
    GivePlayerWeapon(target_id, weapon_id, ammo);

    // Mensagens
    new admin_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, admin_name, sizeof admin_name);
    GetPlayerName(target_id, target_name, sizeof target_name);

    new msg_admin[128], msg_target[128];

    format(msg_admin, sizeof msg_admin,
        "Arma %d (%d munições) entregue a %s.",
        weapon_id, ammo, target_name);
    CmdAdmin(playerid, msg_admin);

    format(msg_target, sizeof msg_target,
        "Você recebeu a arma %d com %d munições do administrador %s.",
        weapon_id, ammo, admin_name);
    SendInfo(target_id, msg_target);

    return 1;
}

// =============================================================
// /weaponpack | Pack de armas pesado (Admin)
// =============================================================
CMD:wpk(playerid, params[])
{
    // Verificação de permissão
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão para usar este comando!");

    // Vida e colete
    SetPlayerHealth(playerid, 100.0);
    SetPlayerArmour(playerid, 100.0);

    // Limpa armas antigas (opcional, mas recomendado)
    ResetPlayerWeapons(playerid);

    // Pack de armas
    GivePlayerWeapon(playerid, 24, 999);   // Desert Eagle
    GivePlayerWeapon(playerid, 31, 999);   // M4
    GivePlayerWeapon(playerid, 34, 99);    // Sniper Rifle
    GivePlayerWeapon(playerid, 35, 99);    // Bazuca (RPG)
    GivePlayerWeapon(playerid, 38, 9999);  // Minigun

    // Feedback
    CmdAdmin(playerid, "Pack de armas pesado concedido!");

    return 1;
}

// =============================================================
// /disarm [id] | Remove todas as armas de um jogador (Admin2+)
// =============================================================
CMD:disarm(playerid, params[])
{
    new targetid;

    // Verificação de permissão
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão para usar este comando!");

    // Leitura do ID do jogador
    if (sscanf(params, "i", targetid))
        return SendError(playerid, "Uso correto: /disarm [id]");

    // Verifica se o jogador existe
    if (!IsPlayerConnected(targetid))
        return SendError(playerid, "Jogador não conectado.");

    // Remove todas as armas do jogador
    ResetPlayerWeapons(targetid);

    // Mensagem para o admin
    new msg[128];
    format(msg, sizeof(msg), "Você desarmou o jogador ID %d.", targetid);
    CmdAdmin(playerid, msg);

    // Mensagem para o jogador desarmado
    SendWarning(targetid, "Um administrador removeu todas as suas armas!");

    return 1;
}


// =============================================================
// /setskin Define a skin do jogador (Admin2+)
// Uso: /setskin [id] [skin]
// =============================================================
CMD:setskin(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    new target_id, skin_id;
    if (sscanf(params, "ii", target_id, skin_id))
        return SendError(playerid, "Use: /setSkin [id] [skin]");

    if (!IsPlayerConnected(target_id))
        return SendError(playerid, "Jogador inválido!");

    if (skin_id < 0 || skin_id > 299)
        return SendError(playerid, "ID de skin deve estar entre 0 e 299.");

    // Apply skin
    SetPlayerSkin(target_id, skin_id);

    // Names
    new admin_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, admin_name, sizeof admin_name);
    GetPlayerName(target_id, target_name, sizeof target_name);

    // Message for admin
    new msg_admin[128];
    format(msg_admin, sizeof msg_admin,
        "Skin de %s definida para %d.", target_name, skin_id);
    CmdAdmin(playerid, msg_admin);

    // Message for target
    new msg_target[128];
    format(msg_target, sizeof msg_target,
        "O administrador %s alterou sua skin para %d.", admin_name, skin_id);
    SendInfo(target_id, msg_target);

    return 1;
}

// =============================================================
// /heal – Cura completamente o jogador (Admin2+)
// Uso: /heal [id]
// =============================================================
CMD:heal(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    new target_id;
    if (sscanf(params, "i", target_id))
        return SendError(playerid, "Use: /heal [id]");

    if (!IsPlayerConnected(target_id))
        return SendError(playerid, "Jogador inválido!");

    // Apply heal
    SetPlayerHealth(target_id, 100.0);
    SetPlayerArmour(target_id, 100.0);

    // Names
    new admin_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, admin_name, sizeof admin_name);
    GetPlayerName(target_id, target_name, sizeof target_name);

    // Message for admin
    new msg_admin[96];
    format(msg_admin, sizeof msg_admin,
        "Jogador %s foi curado completamente.", target_name);
    CmdAdmin(playerid, msg_admin);

    // Message for target
    new msg_target[128];
    format(msg_target, sizeof msg_target,
        "Você foi completamente curado pelo administrador %s.", admin_name);
    SendInfo(target_id, msg_target);

    return 1;
}

