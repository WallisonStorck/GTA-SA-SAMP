// ====================================================
//  SISTEMA DE VEÍCULOS FIXOS DO SERVIDOR
//  Este arquivo NÃO contém veículos de profissões.
// ====================================================

// ---------------------------------------------
//  DEFINES GERAIS DE VEÍCULOS FIXOS
// ---------------------------------------------
#define FIXED_VEHICLE_MODEL    560  // Sultan
#define FIXED_VEHICLE_COLOR_1  1    // Branco
#define FIXED_VEHICLE_COLOR_2  1    // Branco
#define FIXED_VEHICLE_RESPAWN  120  // 2 Min

// ---------------------------------------------
//  VEÍCULOS FIXOS DO SERVIDOR
// ---------------------------------------------
new Float:veh_fix[][4] =
{
    // ----- Los Santos -----
    {1099.07, -1775.58, 13.07, 90.0},
    {1099.07, -1760.85, 13.07, 90.0},
    {1062.00, -1766.70, 13.10, 270.0},
    {1062.00, -1743.19, 13.10, 270.0},

    // ----- Las Venturas -----
    {2040.09, 1363.82, 10.39, 180.0},
    {2040.11, 1316.34, 10.39, 180.0},
    {2119.79, 1998.26, 10.53, 180.0},
    {2107.13, 1408.70, 10.53, 359.62},
    {2103.66, 2079.17, 10.54, 90.0},
    {2103.66, 2046.37, 10.54, 90.0},
    {1113.48, 1736.71, 10.54, 90.0},
    {2074.66, 1156.18, 10.39, 0.0},

    // ----- San Fierro -----
    {-1990.19, 271.28, 34.88, 264.62},
    {-1988.01, 128.82, 27.26, 0.63},
    {-2420.98, 741.60, 34.74, 179.94},
    {-2495.22, 741.60, 34.74, 179.94}
};


// ---------------------------------------------
//  FUNÇÃO: CRIA OS VEÍCULOS FIXOS DO SERVIDOR
// ---------------------------------------------
stock CreateFixedVehicles()
{
    for (new i = 0; i < sizeof(veh_fix); i++)
    {
        CreateVehicle(
            FIXED_VEHICLE_MODEL,
            veh_fix[i][0], veh_fix[i][1], veh_fix[i][2],
            veh_fix[i][3],
            FIXED_VEHICLE_COLOR_1,
            FIXED_VEHICLE_COLOR_2,
            FIXED_VEHICLE_RESPAWN
        );
    }

    // Helicóptero da mansão
    CreateVehicle(487, 1291.38, -788.22, 96.63, 176.80, 1, 0, 120);

    print("[VEHICLE SYSTEM] Veículos gerais carregados.");
}