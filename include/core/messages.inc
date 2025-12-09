// =============================================================================
//  messages.inc — Sistema Unificado de Mensagens
// =============================================================================


#define LOCAL_CHAT_DISTANCE 10.0
// =============================================================================
//  MENSAGENS SIMPLES
//  Prefixos automáticos: (INFO), (ERRO), (AVISO), (ADMIN)
// =============================================================================

stock SendInfo(playerId, const message[])
{
    new msg[144];
    format(msg, sizeof msg, "(INFO) %s", message);
    return SendClientMessage(playerId, COLOR_INFO, msg);
}

stock SendInfoGlobal(const message[])
{
    new msg[160];
    format(msg, sizeof msg, "(INFO) %s", message);
    return SendClientMessageToAll(COLOR_INFO, msg);
}


stock SendError(playerId, const message[])
{
    new msg[144];
    format(msg, sizeof msg, "(ERRO) %s", message);
    return SendClientMessage(playerId, COLOR_ERROR, msg);
}

stock SendSuccess(playerId, const message[])
{
    new msg[144];
    format(msg, sizeof msg, "(SUCESSO) %s", message);
    return SendClientMessage(playerId, COLOR_SUCESS, msg);
}

stock SendWarning(playerId, const message[])
{
    new msg[144];
    format(msg, sizeof msg, "(AVISO) %s", message);
    return SendClientMessage(playerId, COLOR_WARNING, msg);
}

stock SendWarningGlobal(const message[])
{
    new msg[160];
    format(msg, sizeof msg, "(AVISO) %s", message);
    return SendClientMessageToAll(COLOR_WARNING, msg);
}


stock SendAdmin(playerId, const message[])
{
    new msg[144];
    format(msg, sizeof msg, "(ADMIN) %s", message);
    return SendClientMessage(playerId, COLOR_ADMIN, msg);
}


// =============================================================================
//  MENSAGENS BASE (sem prefixos)
//  Usadas quando você quer controle total sobre o texto.
// =============================================================================

stock PlayerMessage(playerId, color, const message[])
{
    return SendClientMessage(playerId, color, message);
}

stock GlobalMessage(color, const message[])
{
    return SendClientMessageToAll(color, message);
}

// =============================================================================
//  MENSAGENS PARA COMANDOS
// =============================================================================

stock CmdUsage(playerId, const usageText[])
{
    new msg[256];
    format(msg, sizeof msg, "(USO CORRETO) %s", usageText);
    return SendClientMessage(playerId, CMD_USAGE_COLOR, msg);
}

stock CmdAdmin(playerId, const message[])
{
    new msg[256];
    format(msg, sizeof msg, "[Admin CMD] %s", message);
    return SendClientMessage(playerId, COLOR_ADMIN, msg);
}



// =============================================================================
//  LOCAL CHAT (mensagens para jogadores próximos)
// =============================================================================

stock SendLocalChat(playerId, const message[])
{
    // Não envia mensagens vazias
    if (!strlen(message)) return;

    // Se o player desconectou durante o processamento, aborta
    if (!IsPlayerConnected(playerId)) return;

    // Obtém a posição do jogador que enviou a mensagem
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerId, px, py, pz);

    // Formata a mensagem com prefixo
    new finalMsg[160];
    format(finalMsg, sizeof finalMsg, "[Chat-Próximo] %s", message);

    // Envia ao próprio jogador
    SendClientMessage(playerId, COLOR_LOCAL_CHAT, finalMsg);

    // Envia aos jogadores próximos
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (i == playerId) continue;                    // Ignora quem enviou
        if (!IsPlayerConnected(i)) continue;            // Ignora desconectados
        if (!IsPlayerStreamedIn(playerId, i)) continue; // Ignora quem não está renderizado

        // Calcula distância até o jogador atual
        new Float:dist = GetPlayerDistanceFromPoint(i, px, py, pz);

        // Se está dentro dos 10 metros, envia
        if (dist <= LOCAL_CHAT_DISTANCE)
        {
            SendClientMessage(i, COLOR_LOCAL_CHAT, finalMsg);
        }
    }
}
