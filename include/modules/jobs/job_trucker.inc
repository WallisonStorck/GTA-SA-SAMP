#if defined _JOB_TRUCKER_INC_
    #endinput
#endif
#define _JOB_TRUCKER_INC_


// ===============================================================
//  DEFINES EXCLUSIVOS DA PROFISSÃO
// ===============================================================

#define TRUCK_MODEL            403     // Linerunner
#define TRUCK_COLOR_1          10      // Azul
#define TRUCK_COLOR_2          10      // Azul

#define TRAILER_MODEL          584     // Petrol Trailer
#define TANKER_MODEL           435     // Tanker (spawn geral)

#define TRUCK_RESPAWN          120     // Segundos



// ===============================================================
//  SPAWN GERAL
//  Caminhões + Tankers (435)
// ===============================================================

// Caminhões do spawn geral
new Float:truck_spawns_general[][4] =
{
    { 2164.00, -2301.40, 14.15, 315.50 },
    { 2167.00, -2304.40, 14.15, 315.50 },
    { 2170.00, -2307.40, 14.15, 315.50 },
    { 2173.00, -2310.40, 14.15, 315.50 },
    { 2176.00, -2313.40, 14.15, 315.50 },
    { 2179.00, -2316.40, 14.15, 315.50 }
};

// Trailers do spawn geral — ID 435
new Float:tanker_spawns_general[][4] =
{
    { 2174.55, -2265.69, 14.00, 224.30 },
    { 2167.02, -2272.98, 14.00, 224.30 },
    { 2160.49, -2279.32, 14.00, 224.30 },

    { 2194.22, -2237.04, 14.18, 224.00 },
    { 2201.22, -2230.04, 14.18, 224.00 },
    { 2208.22, -2223.04, 14.18, 224.00 }

};



// ===============================================================
//  SPAWN REFINARIA
//  Caminhões + Trailers (584)
// ===============================================================

// Caminhões na refinaria
new Float:truck_spawns_refinery[][4] =
{
    { 2429.80, -2119.00, 14.15, 270.00 },
    { 2429.80, -2114.00, 14.15, 270.00 },
    { 2429.80, -2109.00, 14.15, 270.00 },
    { 2429.80, -2104.00, 14.15, 270.00 },

    { 2458.75, -2075.66, 14.69, 178.00 },
    { 2468.12, -2075.90, 14.69, 178.00 },

    { 2501.72, -2102.80, 14.15, 359.00 },
    { 2508.72, -2102.80, 14.15, 359.00 },
    { 2515.72, -2102.80, 14.15, 359.00 }
};

// Trailers de combustível — somente na refinaria
new Float:trailer_spawns_refinery[][4] =
{
    { 2454.66, -2112.80, 14.50, 359.00 },
    { 2460.66, -2112.80, 14.50, 359.00 },
    { 2466.66, -2112.80, 14.50, 359.00 },

    { 2477.00, -2112.80, 14.50, 359.00 },
    { 2484.00, -2112.80, 14.50, 359.00 },
    { 2491.00, -2112.80, 14.50, 359.00 },

    { 2501.72, -2112.80, 14.50, 359.00 },
    { 2508.72, -2112.80, 14.50, 359.00 },
    { 2515.72, -2112.80, 14.50, 359.00 }
};



// ===============================================================
//  CRIADOR DE VEÍCULOS DA PROFISSÃO
// ===============================================================

stock Trucker_CreateVehicles()
{
    // ---------------------------
    // Caminhões do spawn geral
    // ---------------------------
    for (new i = 0; i < sizeof(truck_spawns_general); i++)
    {
        CreateVehicle(
            TRUCK_MODEL,
            truck_spawns_general[i][0], truck_spawns_general[i][1],
            truck_spawns_general[i][2], truck_spawns_general[i][3],
            TRUCK_COLOR_1, TRUCK_COLOR_2,
            TRUCK_RESPAWN
        );
    }

    // ---------------------------
    // Tankers (435) — spawn geral
    // ---------------------------
    for (new i = 0; i < sizeof(tanker_spawns_general); i++)
    {
        CreateVehicle(
            TANKER_MODEL,
            tanker_spawns_general[i][0], tanker_spawns_general[i][1],
            tanker_spawns_general[i][2], tanker_spawns_general[i][3],
            1, 1,
            TRUCK_RESPAWN
        );
    }

    // ---------------------------
    // Caminhões na refinaria
    // ---------------------------
    for (new i = 0; i < sizeof(truck_spawns_refinery); i++)
    {
        CreateVehicle(
            TRUCK_MODEL,
            truck_spawns_refinery[i][0], truck_spawns_refinery[i][1],
            truck_spawns_refinery[i][2], truck_spawns_refinery[i][3],
            TRUCK_COLOR_1, TRUCK_COLOR_2,
            TRUCK_RESPAWN
        );
    }

    // ---------------------------
    // Trailers (584) na refinaria
    // ---------------------------
    for (new i = 0; i < sizeof(trailer_spawns_refinery); i++)
    {
        CreateVehicle(
            TRAILER_MODEL,
            trailer_spawns_refinery[i][0], trailer_spawns_refinery[i][1],
            trailer_spawns_refinery[i][2], trailer_spawns_refinery[i][3],
            1, 1,
            TRUCK_RESPAWN
        );
    }

    print("[TRUCKER] Frota da profissão caminhoneiro criada com sucesso.");
    return 1;
}



// ===============================================================
//  FUNÇÃO PRINCIPAL DA PROFISSÃO
//  Chamado automaticamente por jobs.inc
// ===============================================================

stock Trucker_OnGameModeInit()
{
    Trucker_CreateVehicles();

    // Futuro:
    // Trucker_LoadRoutes();
    // Trucker_InitCommands();
    // Trucker_InitPayments();

    return 1;
}
