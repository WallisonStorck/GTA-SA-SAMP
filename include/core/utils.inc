// ============================================================================
// FUNÇÕES UTILITÁRIAS PARA O SERVIDOR
// ============================================================================

// Verifica se um veículo é válido
stock IsValidVehicle(vehicleid)
{
    return (vehicleid >= 1 && vehicleid < MAX_VEHICLES);
}

// Retorna o jogador que está dirigindo o veículo (ou -1 se ninguém)
stock GetVehicleDriver(vehicleid)
{
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && IsPlayerInVehicle(i, vehicleid))
            return i;
    }
    return -1; // ninguém está dirigindo
}

// Distância entre dois pontos 3D
stock Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
    new Float:dx = x1 - x2;
    new Float:dy = y1 - y2;
    new Float:dz = z1 - z2;
    return floatsqroot(dx*dx + dy*dy + dz*dz);
}
