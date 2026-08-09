# Ponto de continuacao (2026-08-07, ~21:20) — dumps, encoding e fluxo de instalacao

## Contexto
Missao em andamento: substituir o banco binario (FRM/MYD/MYI) por DUMPS
limpos, com o fluxo de instalacao = 00-setup.sql -> DARKEDEN.sql -> USERINFO.sql,
e deixar tudo documentado/automatico para um novato rodar ./setup-mysql.sh.

## O QUE JA FOI FEITO (nesta sessao)

### 1. Banco REAL carregado (antes desta tarefa de dumps)
- MySQL 4.1 (vettadock/mysql-old:4.1) com os arquivos REAIS do servidor
  (FRM/MYD/MYI de vsserver/sqls/ — tarballs) — 411 tabelas MyISAM
- Todos os fixes aplicados NO BANCO VIVO: WorldDBInfo->127.0.0.1/elcastle,
  GameServerInfo->127.0.0.1, ZoneInfo com nomes exatos em disco (caixa mista),
  18 zonas sem mapa excluidas (ZoneGroupID=0), elcastle OLD_PASSWORD
- Os 3 servidores sobem e conversam (loginserver 9999, sharedserver 9977,
  gameserver 9998 + 155 zonas)

### 2. Scripts de instalacao JÁ ATUALIZADOS (feito na tarefa anterior)
- vsserver/sqls/patch-compat.sql (criado): documenta TODOS os updates de
  compatibilidade (WorldDBInfo, GameServerInfo, 18 zonas excluidas, 155 nomes
  de zona, usuario elcastle OLD_PASSWORD + limpeza de anonimos). Idempotente.
- vsserver/docker/mysql41-entrypoint.sh: REESCRITO para copiar os arquivos
  reais (com fallback para tarballs) + aplicar o patch (flags .realdata-deployed
  e .patch-applied)
- docker-compose.yml, mysql.sh e setup-mysql.sh (raiz): comentarios/descricoes
  atualizados para o fluxo "arquivos reais"
- ⚠️ ESSE FLUXO AINDA NAO FOI TESTADO de ponta a ponta (o wipe nao chegou a
  acontecer — interrompido quando o usuario mudou de ideia para dumps)

### 3. Decisao do usuario (NOVO CAMINHO): dumps em vez de arquivos binarios
- Gerar dumps do banco JÁ CORRIGIDO (todos os fixes embutidos) e substituir
  os dumps antigos (DARKEDEN.sql/USERINFO.sql de opendarkeden — schema errado)
- Fluxo final desejado: 00-setup.sql -> DARKEDEN.sql -> USERINFO.sql
- "files" deixa de ser necessario no fluxo (fica como backup)

## 🔬 INVESTIGACAO DE ENCODING (muito importante)

### Fatos verificados
- O texto coreano nos bancos reais esta em **CP949/EUC-KR** (ex.: FullName da
  zona 11 = bytes BFA1BDBDB6F3B4CFBEC6BACFB5BF), guardado em colunas declaradas
  latin1 (latin1 e byte-transparente; o client 3.23 dos servers le bytes crus)
- O MYSQL 4.1 NAO TEM information_schema (checagens usam SHOW TABLE STATUS)
- O cliente mysql do container NAO carrega a tabela de charsets
  (/usr/share/mysql/charsets tem Index.xml do 5.x, nao o Index binario do 4.1)
  → por isso apareciam "[CREDIT_CARD]" em queries sem --default-character-set

### 🐛 O PRIMEIRO DUMP COMPLETO SAIU CORROMPIDO
- `mysqldump --default-character-set=latin1 -uroot DARKEDEN` (1a vez) produziu
  texto coreano vira U+FFFD (EFBFBD) — MONSTERLIST/colunas text corrompidas
- O RE-DUMP (mesmo comando) saiu PERFEITO: zero U+FFFD, bytes CP949 intactos
  (verificado byte a byte: B5A5B5E5B9D9B5F0 preservado). Causa do 1o: nao
  determinada (possivel glitch da 1a execucao) — o re-dump esta salvo em
  /tmp/opencode/DARKEDEN-v2.sql (HOST) e /tmp/darkeden.sql (dentro do container)
- DUMP DE TABELA UNICA com latin1 TAMBEM preserva bytes (testado)
- IMPORT com --default-character-set=utf8 CONVERTE (latin1->utf8, reversivel
  se importar com utf8 tambem) — entao SEMPRE importar com latin1
- Regra: dump E import SEMPRE com `--default-character-set=latin1` (e o
  entrypoint ja usa isso no patch)

### ⚠️ ESTADO ATUAL DO BANCO VIVO (precisa de verificacao)
- Tentei importar o dump limpo num banco "rtest" via `mysql rtest < dump`,
  mas o dump tem CREATE DATABASE/USE DARKEDEN embutido → o import foi PARA O
  DARKEDEN VIVO e parou com "Duplicate entry" na linha 3524 (tabela FlagSet
  ou vizinha — contexto: final do bloco FlagSet/FlagWarHistory)
- Impacto provavel: ZERO ou minimo (dump tem DROP TABLE IF EXISTS antes de
  cada tabela → reimportou dados identicos), MAS o banco vivo NAO foi
  verificado depois disso
- DECISAO RECOMENDADA: apagar tudo e fazer o teste de instalacao COMPLETO do
  zero (é o teste definitivo de round-trip do encoding + do fluxo de setup)

## PROXIMOS PASSOS (continuar daqui)

1. VERIFICAR/integrar o dump limpo: substituir vsserver/sqls/DARKEDEN.sql pelo
   /tmp/opencode/DARKEDEN-v2.sql (que está PERFEITO) — NAO usar o DARKEDEN.sql
   que esta em sqls/ agora (pode ser o corrompido de 12247 linhas)
2. Redumpar USERINFO limpo (o atual em sqls/ pode ser do mesmo lote corrompido)
   e substituir
3. Ajustar 00-setup.sql (criar bancos + elcastle com OLD_PASSWORD; manter GRANTs)
4. SIMPLIFICAR o entrypoint para o fluxo de dumps:
   import 00-setup -> DARKEDEN -> USERINFO (ordem alfabetica ja funciona),
   manter: fix de senha OLD_PASSWORD + delete anonimos (sempre), flags
   (ex.: .sqls-imported) e --force para nao crashar container
   NOTA: com dumps o patch-compat.sql vira DOCUMENTACAO (fixes ja embutidos
   nos dumps) — manter arquivo, atualizar cabecalho, decidir se roda ou nao
5. Atualizar comentarios do compose/mysql.sh/setup-mysql (dumps, nao binarios)
6. TESTE FINAL DE PONTA A PONTA (simula novato):
   a. docker compose rm -sf mysql + limpar docker/mysql-data
      (arquivos sao de root: usar docker run --rm --entrypoint bash ... para
      rm -rf como root — sudo do host pede senha interativa e falha)
   b. ./setup-mysql.sh (raiz) OU docker/mysql.sh start
   c. validar: DARKEDEN 411 tabelas, USERINFO 5, elcastle OLD_PASSWORD
      (16 bytes), WorldDBInfo/GameServerInfo 127.0.0.1, ZoneInfo 155 ativas
      + 18 excluidas, e COMPARAR HEX de texto coreano (zona 11 MonsterList
      deve ser 23B5A5B5E5B9D9B5F0...)
   d. subir os 3 servers e confirmar que tudo conecta
7. ATENCAO ao dump: conferir se ha CREATE TABLE duplicado de alguma tabela
   (o erro "Duplicate entry" na linha 3524 sugere investigar; em banco limpo
   nao deve ocorrer, mas conferir a tabela FlagSet/FlagWarHistory)
8. Atualizar .memories/estado-atual.md no final

## DATA DO SERVIDOR (decisao estabelecida)
- USADO: **data-ingles** (vsserver/data/data-ingles/data -> copiado para
  vsserver/data/) — 551 arquivos
- data - coreano tem 628 arquivos (nomes com espaco/outros .bin)
- .smp/.ssi sao IDENTICOS nas duas pastas (142 + 142); diferencas estao nos
  .bin (monstros/NPC) e outros
- Os nomes de arquivo do patch/ZoneInfo foram gerados a partir do data-ingles

## ATALHOS/PISTAS
- Container MySQL: darkeden-mysql (imagem vettadock/mysql-old:4.1)
- Charset nos clientes: SEMPRE --default-character-set=latin1
- mysqldump do container: /usr/local/mysql/bin/mysqldump (versao 4.1.22-max)
- Dump limpo salvo: /tmp/opencode/DARKEDEN-v2.sql (host)
- Bug STLport do retry de lowercase no Zone::load: ja contornado via nomes
  exatos no banco (documentado no estado-atual.md)
