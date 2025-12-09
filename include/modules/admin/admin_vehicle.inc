// (car, poscar, spawncar)

// =============================================================
// /car Criar veículo no local (Admin2+)
// =============================================================
CMD:car(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão para criar veículos!");

    new model, color1, color2;

    if (sscanf(params, "iii", model, color1, color2))
        return SendError(playerid, "USE: /car [modelo] [cor1] [cor2]");

    if (model < 400 || model > 611)
        return SendError(playerid, "ID do veículo inválido! Use IDs entre 400 e 611.");

    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new vehid = CreateVehicle(model, x, y, z, a, color1, color2, -1);

    // Dejesa destruir o veículo ao sair dele?
    TempVehicle[vehid] = false;

    PutPlayerInVehicle(playerid, vehid, 0);

    new msg[128];
    format(msg, sizeof(msg),
        "Veículo criado! (Modelo %d | Cores %d/%d)",
        model, color1, color2);

    CmdAdmin(playerid, msg);
    return 1;
}

// =============================================================
// /poscar Salvar posição do veículo atual (MASTER)
// Log: scriptfiles/savedpositions/vehicle_positions.log
// =============================================================
CMD:poscar(playerid)
{
    if (!IsAdmin(playerid, ROLE_MASTER))
        return SendError(playerid, "Você não tem permissão!");

    if (!IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Você precisa estar dentro de um veículo!");

    new veh = GetPlayerVehicleID(playerid);

    new Float:x, Float:y, Float:z, Float:a;
    GetVehiclePos(veh, x, y, z);
    GetVehicleZAngle(veh, a);

    // Data e hora
    new year, month, day, hour, minute, second;
    getdate(year, month, day);
    gettime(hour, minute, second);

    // Abrir arquivo para adicionar linha
    new File:fp = fopen("savedpositions/vehicle_positions.log", io_append);

    if (!fp)
        return SendError(playerid, "Não foi possível abrir o arquivo de posições!");

    new line[256];
    // format(line, sizeof line,
    //     "[%02d/%02d/%04d %02d:%02d:%02d] X: %.2f | Y: %.2f | Z: %.2f | ANG: %.2f\r\n",
    //     day, month, year, hour, minute, second,
    //     x, y, z, a);
    format(line, sizeof line,
        "[%02d/%02d/%04d %02d:%02d:%02d] { %.2f, %.2f, %.2f, %.2f }\r\n",
        day, month, year, hour, minute, second,
        x, y, z, a);

    fwrite(fp, line);
    fclose(fp);

    // Mensagem no chat
    new msg[144];
    format(msg, sizeof msg,
        "Posição do veículo salva! [ X: %.2f | Y: %.2f | Z: %.2f | ANG: %.2f ]",
        x, y, z, a);

    CmdAdmin(playerid, msg);
    return 1;
}

// =============================================================
// /repair Você Reparar veículo atual (Admin2+)
// =============================================================
CMD:rp(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    if (!IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Você precisa estar dentro de um veículo.");

    new veh = GetPlayerVehicleID(playerid);

    RepairVehicle(veh);

    CmdAdmin(playerid, "Seu veículo foi reparado.");
    return 1;
}

// =============================================================
// /flip Você Reparar veículo atual (Admin2+)
// =============================================================
CMD:fp(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
        return SendError(playerid, "Você não tem permissão!");

    if (!IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Você precisa estar dentro de um veículo.");

    new veh = GetPlayerVehicleID(playerid);

    new Float:x, Float:y, Float:z, Float:a;
    GetVehiclePos(veh, x, y, z);
    GetVehicleZAngle(veh, a);

    // Colocar o veículo de volta no chão e desvirado
    SetVehiclePos(veh, x, y, z + 0.5);   
    SetVehicleZAngle(veh, a);           
    SetVehicleHealth(veh, 1000.0);      

    RepairVehicle(veh);

    CmdAdmin(playerid, "Seu veículo foi desvirado e reparado.");
    return 1;
}

// =============================================================
// /destroy vehicle | Você destruir o veículo atual (Admin2+)
// =============================================================
CMD:dv(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN2))
            return SendError(playerid, "Você não tem permissão.");

    if (!IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Você não está dentro de um veículo.");

    new vehicleid = GetPlayerVehicleID(playerid);

    // Proteção para evitar destruir veículos inexistentes (bug)
    if (!IsValidVehicle(vehicleid))
        return SendError(playerid, "Este veículo não existe ou já foi destruído.");

    // Desanexa o jogador antes de destruir (evita bugs)
    RemovePlayerFromVehicle(playerid);

    DestroyVehicle(vehicleid);

    CmdAdmin(playerid, "Veículo destruído com sucesso.");
    return 1;
}


// =============================================================
// /nitro | Adiciona nitro 10x no veículo atual (Admin1+)
// =============================================================
CMD:nitro(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_ADMIN1))
        return SendError(playerid, "Você não tem permissão.");

    if (!IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Você precisa estar dentro de um veículo.");

    new veh = GetPlayerVehicleID(playerid);

    // ID do Nitro 10x = 1010
    AddVehicleComponent(veh, 1010);

    CmdAdmin(playerid, "Nitro 10x adicionado ao veículo!");

    return 1;
}
