# Patch ZoneInfo corrigido: mapas genéricos trocados pelos mapas REAIS (2026-08-09)

## 🚨 O ERRO (resolvido)

O gameserver crashava ao iniciar com:
```
EmptyTileNotExistException : too many creature in this zone.. or too unlucky
 void Zone::addCreature(Creature *, short unsigned int, short unsigned int, unsigned char)
```
na zona **2001** (guild shop). O usuário achava que tinha sido resolvido — e tinha sido,
porém o `patch-compat.sql` que ficou versionado estava com uma versão corrompida.

## CAUSA RAIZ

O `vsserver/sqls/patch-compat.sql` antigo tinha **DUAS listas de UPDATEs de ZoneInfo**
conflitantes (linhas 52-206 e 223-377). A segunda lista roda por último e sobrescrevia
os mapas CORRETOS do banco real por **mapas genéricos errados**:

| Zonas | Mapas errados (patch velho) | Mapas corretos (banco real/tarball) |
|---|---|---|
| 2000-2024 (guild army/cleric/knight shops) | `alter_of_blood.smp` | `guild_army_*.smp` / `guild_cleric_*.smp` / `guild_knight_*.smp` |
| 2101/2102 (tutorial) | `asylion_dungeon.smp` | `tutorial_n.smp` / `tutorial_s.smp` |
| 3001-3003 | `asylion_dungeon.smp` | `maze.smp`, `trapzone01.smp`, `trapzone02.smp` |
| 4001-4005 | `asylion_dungeon.smp` | `gate_of_alter.smp`, `alter_of_blood.smp`, ... |
| 1100-1134 (dungeons bathory/rasen/caligo etc) | `eslania_dungeon.smp` | `bathory_dungeon_b1f.smp`, `tunnel_ghorgova.smp`, `castle_rasen_*`, `caligo_dungeon.smp`... |
| 1020 | `limbo_dungeon.smp` | `drobeta_stadium.smp` |
| 1500/1501/1504/1505/1506 | `alter_of_blood.smp`? não — `siege_warfare.smp` no real | `adam_new_*` (fix documentado nas memórias) |

### Como descobri que o patch estava errado
- O arquivo `.smp` tem o ZoneID no header (2 bytes após versionLen/version).
  `alter_of_blood.smp` tem zoneID interno **4002** → é o mapa da zona 4002, NÃO das guild shops.
  `guild_army_1f.smp` tem zoneID interno **2001** → é o mapa correto da zona 2001.
- Validando os NPCs (`Triggers` com `ActionType : SetPosition` → tabela `NPC`) contra os mapas:
  - Com `alter_of_blood.smp` (128x128): NPCs das guild shops caíam em tile bloqueado (flag 0x07)
    e o `findSuitablePosition` (espiral de 300 iterações, raio ~8) não achava tile livre → crash.
  - Com `guild_army_*.smp` / `guild_cleric_*.smp` / `guild_knight_*.smp`: **todos** os NPCs OK (raio 0-1).
- Também conferi contra o `ZoneInfo.MYD` ORIGINAL do tarball
  (`tar xzf DARKEDEN.tar.gz DARKEDEN/ZoneInfo.*` + carregar no MySQL 4.1):
  os nomes originais eram `guild_army_1F.smp` (caixa mista) — confirma que o mapa correto
  é o de guild, não o alter_of_blood.

## O QUE FOI FEITO

1. Regenerado o patch com o mapeamento CORRETO para as 155 zonas ativas:
   - Nome = arquivo real do banco (tarball), com a caixa EXATA do arquivo em `vsserver/data/`
     (importante por causa do bug STLport: retry em minúsculas nunca funciona).
   - Zonas adam 1500/1501/1504/1505/1506 mantêm `adam_new_*` (fix das memórias anteriores).
   - Removida a duplicação (a lista antiga de 2x155 UPDATEs virou 1x155).
   - Seções de ZoneTriggers adam (X>127 → Assert), waypoints da 1105 e NPCs adam preservadas.
2. `patch-compat.sql` reescrito (250 linhas, idempotente).
3. Aplicado no banco vivo e validado com o parser do SMP:
   - NPCs (SetPosition): **0 falhas**
   - Portais (ZoneTriggers): **0 fora do mapa**
   - WayPoints: **0 fora do mapa**
4. Gameserver subiu: **155 ZONE INITIALIZATION SUCCESS**, "ALL INITIALIZATIONS ARE COMPLETED
   SUCCESSFULLY", zero EmptyTileNotExistException.

## LIÇÕES

- ⚠️ `alter_of_blood.smp` tem zoneID interno 4002 → é o mapa da zona 4002. NUNCA usar como
  placeholder genérico para outras zonas.
- Para conferir se o mapa do banco está certo para uma zona: ler o zoneID interno do `.smp`
  (offset: versionLen(4)+version+2 bytes) e comparar com o ZoneID da zona.
- O parser do SMP usado nas memórias anteriores continua o mesmo (tiles intercalados com
  portal 0x80; flag 0x02 = bloqueado walking; findSuitablePosition = espiral raio ~8).
- Sempre validar NPCs+portais+waypoints contra o mapa ANTES de dar o patch como pronto.

## PENDENTE (fora do escopo)
- O `patch-compat.sql` novo também corrige as zonas 1100-1134, 2101/2102, 3001-3003 e
  4001-4005 de volta aos mapas reais — o gameserver subiu com todas elas SUCCESS.
