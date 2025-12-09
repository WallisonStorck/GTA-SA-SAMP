// (jetpack, godmode, flymode…)


new bool:UsingJetpack[MAX_PLAYERS];
new JetpackDelay[MAX_PLAYERS];

// =============================================================
// /jet – Jetpack exclusivo do Master
// =============================================================
CMD:jet(playerid, params[])
{
    if (!IsAdmin(playerid, ROLE_MASTER))
        return SendError(playerid, "Comando exclusivo do Master!");

    // Ativa jetpack
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);

    // marca que ele está usando jetpack
    UsingJetpack[playerid] = true;

    // coloca um delay de segurança (20 updates = ~1 segundo)
    JetpackDelay[playerid] = 20;

    CmdAdmin(playerid, "Jetpack ativado!");
    return 1;
}


// =============================================================
// REMOÇÃO AUTOMÁTICA DO JETPACK — versão corrigida
// =============================================================
public OnPlayerUpdate(playerid)
{
    // Se não está usando jetpack, não precisa checar nada
    if (!UsingJetpack[playerid])
        return 1;

    // Se o delay ainda está ativo, só decrementa
    if (JetpackDelay[playerid] > 0)
    {
        JetpackDelay[playerid]--;
        return 1;
    }

    // Se já passou o delay, verificar se largou o jetpack
    if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK)
    {
        UsingJetpack[playerid] = false;

        // remove jetpack
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        // corrige bug visual
        new skin = GetPlayerSkin(playerid);
        SetPlayerSkin(playerid, skin);

        SendInfo(playerid, "Jetpack removido!");
    }

    return 1;
}
