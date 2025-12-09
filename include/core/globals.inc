// =======================================
// CORES PADRÃO
// =======================================
#define COLOR_INFO        0x00C0FFFF
#define COLOR_ERROR       0xFF4040FF
#define COLOR_LOCAL_CHAT  0x40FF40FF
#define COLOR_ADMIN       0xFF1493FF
#define COLOR_WARNING     0xFFFF00FF
#define COLOR_SUCESS      0x40FF40FF

#define CMD_USAGE_COLOR   0xBFC0C2FF

// =======================================
// VARIAVEIS GLOBAIS DO SERVIDOR
// =======================================
new TempVehicle[MAX_VEHICLES];

// =======================================
// SISTEMA DE DADOS DO PLAYER
// =======================================
enum E_PLAYER_DATA
{
    bool:IsLogged,
    Level,
    Money,
    AdminLevel,
    Password[64]
};

new PlayerData[MAX_PLAYERS][E_PLAYER_DATA];
