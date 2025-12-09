# 🐞 Bug Tracking — SA-MP Server (Projeto Storck)

Arquivo destinado ao registro de bugs, limitações técnicas e pendências de implementação encontradas durante o desenvolvimento do servidor. Use este documento como referência para futuras correções.

---

## ❗ 1) JETPACK NÃO ATIVA NA ÁGUA

**Descrição:** `SPECIAL_ACTION_USEJETPACK` não funciona quando o jogador está submerso.

**Status atual:** Solução parcial eleva o jogador com `SetPlayerPos()`, mas ainda falha em algumas situações.

**Pendência:**

- Melhorar detecção de água.
- Ajustar altura antes de ativar jetpack.
- Testar diferentes profundidades e animações.

---

## ❗ 2) SISTEMA DE ADMIN AINDA NÃO INTEGRADO AO SISTEMA DE CONTAS

**Descrição:** Por enquanto, Master é validado apenas por nome do jogador.

**Pendência:**

- Implementar autenticação real.
- Salvar/readmin `AdminLevel`.
- Restaurar validação original.
- Remover bypass temporário.

---

## ❗ 3) MENSAGENS COM ACENTOS QUEBRADOS (PROBLEMA DE ENCODING)

**Descrição:** Após habilitar Unicode no VSCode, arquivos `.pwn` foram salvos como UTF-8.
O compilador do SA-MP **não aceita UTF-8**, apenas ANSI.

**Impacto:** Surge texto como:

- “Você” → “VocÃª”
- “Permissão” → “PermissÃ£o”

**Pendência:**

- Configurar VSCode para salvar `.pwn` como ANSI.
- Desativar UTF-8 automático.

---

## ❗ 4) INDENTAÇÃO SUMINDO AO SALVAR NO VSCODE

**Descrição:** Após editar configurações, VSCode passou a remover tabulações/formatar sozinho.

**Causas possíveis:**

- `editor.formatOnSave`
- `files.trimTrailingWhitespace`
- Extensão auto-formatter

**Pendência:**

- Revisar settings.json.
- Desativar formatação automática para Pawn.
