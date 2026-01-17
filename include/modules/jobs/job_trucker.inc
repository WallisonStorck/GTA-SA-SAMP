#if defined _JOB_TRUCKER_INC_
    #endinput
#endif
#define _JOB_TRUCKER_INC_

#define TRUCK_MODEL            403     // Linerunner
#define TRUCK_COLOR_1          10      // Azul
#define TRUCK_COLOR_2          10      // Azul

#define TRAILER_MODEL          584     // Petrol Trailer
#define TANKER_MODEL           435     // Tanker (spawn geral)

#define TRUCK_RESPAWN          120     // Segundos



// ===============================================================
//  Ocean Docks - LS
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
    // { 2160.49, -2279.32, 14.00, 224.30 },

    { 2207.34, -2276.83, 14.18, 45.00 },
    { 2214.64, -2269.53, 14.18, 45.00 },
    { 2221.94, -2262.23, 14.18, 45.00 },
    { 2229.24, -2254.93, 14.18, 45.00 },
    { 2236.54, -2247.63, 14.18, 45.00 },

    { 2184.70, -2226.22, 14.18, 225.50 },
    { 2189.02, -2221.75, 14.18, 225.50 },
    { 2193.33, -2217.29, 14.18, 225.50 },
    { 2197.65, -2212.82, 14.18, 225.50 },
    { 2201.96, -2208.36, 14.18, 225.50 },
    { 2206.28, -2203.89, 14.18, 225.50 }

};

stock Trucker_RemoveMap(playerid)
{
    // Ocean Docks - LS (Spawn Caminhoneiro)
    RemoveBuildingForPlayer(playerid, 3686, 2195.0859, -2216.8438, 15.9063, 0.25);
    RemoveBuildingForPlayer(playerid, 3744, 2193.2578, -2286.2891, 14.8125, 0.25);
    RemoveBuildingForPlayer(playerid, 5305, 2198.8516, -2213.9219, 14.8828, 0.25);

    RemoveBuildingForPlayer(playerid, 3747, 2234.3906, -2244.8281, 14.9375, 0.25);
    RemoveBuildingForPlayer(playerid, 3747, 2226.9688, -2252.1406, 14.9375, 0.25);
    RemoveBuildingForPlayer(playerid, 3747, 2219.4219, -2259.5234, 14.8828, 0.25);
    RemoveBuildingForPlayer(playerid, 3747, 2212.0938, -2267.0703, 14.9375, 0.25);
    RemoveBuildingForPlayer(playerid, 3747, 2204.6328, -2274.4141, 14.9375, 0.25);

    RemoveBuildingForPlayer(playerid, 3578, 2165.0703, -2288.9688, 13.2578, 0.25);
    RemoveBuildingForPlayer(playerid, 3574, 2193.2578, -2286.2891, 14.8125, 0.25);

    RemoveBuildingForPlayer(playerid, 3569, 2204.6328, -2274.4141, 14.9375, 0.25);
    RemoveBuildingForPlayer(playerid, 3569, 2212.0938, -2267.0703, 14.9375, 0.25);
    RemoveBuildingForPlayer(playerid, 3569, 2219.4219, -2259.5234, 14.8828, 0.25);
    RemoveBuildingForPlayer(playerid, 3569, 2226.9688, -2252.1406, 14.9375, 0.25);
    RemoveBuildingForPlayer(playerid, 3569, 2234.3906, -2244.8281, 14.9375, 0.25);

    RemoveBuildingForPlayer(playerid, 3578, 2235.1641, -2231.8516, 13.2578, 0.25);
    RemoveBuildingForPlayer(playerid, 3627, 2195.0859, -2216.8438, 15.9063, 0.25);
    RemoveBuildingForPlayer(playerid, 5244, 2198.8516, -2213.9219, 14.8828, 0.25);

    return 1;
}


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


stock Trucker_OnPlayerConnect(playerid)
{
    Trucker_RemoveMap(playerid);
    return 1;
}