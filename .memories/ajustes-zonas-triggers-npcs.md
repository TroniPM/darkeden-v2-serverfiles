# Ajustes de zonas, triggers, waypoints e NPCs (2026-08-08)

Documentação das alterações de banco feitas na sessão que deixou o
servidor estável (zonas adam_* e zona 1105). Todas consolidadas em
`vsserver/sqls/patch-compat.sql` (seções 5-7) — verificado contra o
banco real após o fix.

## Contexto

O banco REAL (FRM/MYD/MYI) veio de um servidor que usava mapas/cliente
diferentes. Três classes de problema derrubavam o gameserver ou ficavam
inconsistentes:

1. **ZoneTriggers fora do mapa** → `Assert` em `Zone.cpp:2396`
   (`loadTriggeredPortal`) derruba o gameserver ao carregar a zona.
2. **Waypoints fora do mapa** → NPCs/movimentação quebrada.
3. **NPCs spawnados fora do mapa** → triggers `SetPosition` com
   coordenadas inválidas.

## ⚠️ LIÇÃO IMPORTANTE: parser do .smp

A primeira tentativa de corrigir os NPCs usou um parser do .smp **errado**:
lia `w*h` bytes fixos como tiles, SEM pular os dados de portal que ficam
**intercalados** entre os tiles. O resultado foi desalinhamento: os tiles
pareciam livres mas na realidade estavam bloqueados (flag 0x02) ou com
portal (flag 0x80). O gameserver crashou com
`EmptyTileNotExistException : too many creature in this zone.. or too
unlucky` ao carregar a zona 1501.

### Formato real do .smp (como o Zone.cpp lê)

```
[header] versionLen(4) + version + zoneID(2) + zoneGroupID(2) +
         zonenameLen(4) + zonename + zoneType(1) + zoneLevel(1) +
         descLen(4) + desc + width(2) + height(2)
[tiles]  para cada tile (y de 0..h-1, x de 0..w-1):
           1 byte flag:
             0x01 = bloqueado burrowing
             0x02 = bloqueado walking
             0x04 = bloqueado flying
             0x80 = TEM PORTAL -> bytes extras a seguir:
               1 byte tipo (0=normal,1=slayer,2=vampire,3=multi,5=guild,6=battle,7=ousters)
               tipo==3: 1 byte size + size*(zoneID(2)+x(1)+y(1))
               tipo 0/1/2/5/6/7: zoneID(2)+x(1)+y(1) = 4 bytes
               tipo 4 (private) ou desconhecido: NADA
```

**Detalhe crítico:** `ZoneID_t` é `WORD` (2 bytes), NÃO 4! O primeiro
parser usava 4 bytes e também errava o alinhamento.

## 1. Zonas adam_* (1501/1504/1505/1506)

- Os mapas `adam_new_c/e/w.smp` são **128x256** (enquanto `adam_c/e/w.smp`
  são 256x256).
- Os `ZoneTriggers` originais usavam `X1=156/X2=160` e `X1=169/X2=174` —
  passando de X=127 → Assert no gameserver.
- **Decisão:** em vez de desativar as zonas (que seria o caminho fácil),
  os triggers foram **corrigidos para dentro do mapa** e as zonas foram
  **mantidas ativas** (`ZoneGroupID=1`).

```sql
-- ZoneTriggers: trazer X para dentro do mapa 128x256
UPDATE DARKEDEN.ZoneTriggers SET X1=123, X2=127 WHERE ZoneID IN (1501,1504,1505,1506) AND X1=156 AND X2=160;
UPDATE DARKEDEN.ZoneTriggers SET X1=122, X2=127 WHERE ZoneID IN (1501,1504,1505,1506) AND X1=169 AND X2=174;

-- Reativação explícita (idempotente)
UPDATE DARKEDEN.ZoneInfo SET ZoneGroupID=1 WHERE ZoneID IN (1500,1501,1504,1505,1506);
```

## 2. NPCs das zonas adam (triggers SetPosition)

4 NPCs spawnavam em **(166,40)**, fora do mapa 128x256. Reposicionados
no tile livre mais próximo — **revalidado com o parser correto** (tile
sem flags de bloqueio e sem portal):

| TriggerID | Zona | Antes | Depois |
|---|---|---|---|
| 1583 | 1501 | (166,40) | (127,30) |
| 1619 | 1504 | (166,40) | (126,1) |
| 1631 | 1505 | (166,40) | (126,5) |
| 1643 | 1506 | (166,40) | (126,5) |

> ❌ (127,10)/(127,1) foram as posições escolhidas com o parser errado —
> tile real era 0x07 (bloqueado) ou 0x80 (portal). Correção acima.
> Os UPDATEs no banco partiram do valor já alterado (X : 127), então o
> REPLACE tem que procurar 'Y : 10'/'Y : 1' e não 'X : 166'.

```sql
-- NO PATCH (aplica sobre o valor ORIGINAL 'X : 166'):
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 127'), 'Y : 40', 'Y : 30') WHERE TriggerID=1583;
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 126'), 'Y : 40', 'Y : 1') WHERE TriggerID=1619;
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 126'), 'Y : 40', 'Y : 5') WHERE TriggerID=1631;
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 126'), 'Y : 40', 'Y : 5') WHERE TriggerID=1643;
```

## 3. WayPointInfo da zona 1105 (eslania_dungeon)

Waypoints com `Y=201` e `X=165` fora do mapa → trazidos para dentro
(X/Y máx = 127).

```sql
UPDATE DARKEDEN.WayPointInfo SET Y=127 WHERE ZoneID=1105 AND Y=201;
UPDATE DARKEDEN.WayPointInfo SET X=127 WHERE ZoneID=1105 AND X=165;
```

Estado final da zona 1105: waypoints `(95,127)` e `(127,89)`.

## 4. Zonas desativadas (seção 3 do patch)

18 zonas SEM arquivos de mapa em `vsserver/data/` continuam
desativadas (`ZoneGroupID=0`) — ativá-las derruba o gameserver com
FileNotExistException (o retry em minúsculas do ifstream nunca funciona
com STLport):

```
1701-1706 (menegroth), 1801-1804 (tiffauges castle),
5000-5050 (hell garden), 8003-8004 (office)
```

## Verificação (banco real, container darkeden-mysql)

| Checagem | Resultado |
|---|---|
| Zonas adam 1500/1501/1504/1505/1506 | `ZoneGroupID=1` (ativas) |
| Total de zonas ativas | 155 |
| ZoneTriggers das adam | máx X2 = 127 (dentro do mapa) |
| WayPointInfo 1105 | (95,127) e (127,89) |
| NPC triggers 1583/1619/1631/1643 | (127,30) / (126,1) / (126,5) x2 |
| Todos os NPC SetPosition (parser correto) | 0 problemas |
| Zonas desativadas | exatamente as 18 da lista |
| Gameserver sobe | ✅ 157 zonas SUCCESS, sem crash nas adam |
| Zona 1301 | exception em runs antigos; SUCCESS no run atual |

## Notas

- O patch-compat.sql é **idempotente**: rodar de novo não tem efeito
  (os WHEREs só pegam valores ainda não corrigidos).
- Se trocar `vsserver/data/` por outros mapas, revalidar com o parser
  CORRETO (portais intercalados!) e as dimensões reais dos .smp
  (128x256 vs 256x256).
- Formato do campo `Actions` na tabela `Triggers` usa `\n\t\t` como
  separador e `X : N` / `Y : N` com espaços ao redor do `:`.
- Para validar posição de NPC: o tile tem que ter flag==0 (sem
  bloqueio walking 0x02 E sem portal 0x80) — o gameserver usa
  `findSuitablePosition` com busca em espiral de 300 iterações.
