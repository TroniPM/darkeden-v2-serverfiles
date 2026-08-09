# Voltar a ler ao religar a VM (2026-08-08)

Guia de retomada: como subir tudo e como conectar o cliente. Escrito em
2026-08-08, sessão que deixou o servidor funcionando de ponta a ponta.

## Estado atual (antes de desligar)

- MySQL 4.1 em Docker: container `darkeden-mysql` (imagem `vettadock/mysql-old:4.1`),
  porta 3306, banco REAL do servidor importado (DARKEDEN 411 tabelas, USERINFO 5) + patch
  de compatibilidade aplicado.
- 3 servidores compilados e rodando: loginserver (9999), sharedserver (9977),
  gameserver (9998) — todos com `127.0.0.1` interno.
- Scripts da raiz renomeados para `.sh`: `install.sh`, `build-server.sh`,
  `setup-mysql.sh`, `wipe-all.sh`, `start-servers.sh`, `stop-servers.sh`.

## Passo a passo ao religar a VM

```bash
# 1. MySQL (baixa imagem na 1ª vez; importa tarballs + patch na 1ª subida)
./install.sh mysql          # ou ./setup-mysql.sh

# 2. Subir os 3 servidores
./start-servers.sh          # loginserver -> sharedserver -> gameserver
./setup-mysql.sh status     # conferir bancos

# 3. Parar tudo
./stop-servers.sh
```

## Fluxo do MySQL (não é dump SQL!)

O banco NÃO vem de dumps `.sql` (schema do opendarkeden é diferente). A fonte é:

- `vsserver/sqls/DARKEDEN.tar.gz` + `USERINFO.tar.gz` = dados reais FRM/MYD/MYI.
- O entrypoint (`vsserver/docker/mysql41-entrypoint.sh`) extrai os tarballs
  (mount é `:ro`, extrai em `/tmp/realdb`), copia pro datadir e aplica
  `vsserver/sqls/patch-compat.sql` (IPs locais, 18 zonas desativadas, 155 ativas,
  usuário elcastle/elca110 com OLD_PASSWORD).
- `00-setup.sql` é desnecessário nesse fluxo (entrypoint já faz GRANT + senha antiga).
- Reimportar do zero: `./setup-mysql.sh reset`.

## Bugs corrigidos no start-servers.sh (não repetir)

1. **Extensão dupla de conf**: as chamadas passavam `loginserver.conf` e a função
   `start_one` acrescentava `.conf` de novo → `src/conf/loginserver.conf.conf`
   → servidor morria na hora, log vazio. Agora passa só o nome (ex.: `loginserver`).
2. **Processos órfãos**: runs antigas deixavam servidores segurando as portas
   (BindException: address already in use). O script agora mata instâncias antigas
   com `pkill -f "bin/<nome>"` antes de subir (stop-servers.sh também tem fallback).
3. Logs `.out` podem ficar vazios por um tempo: binário é estático e bufferiza
   stdout — não é sinal de problema.

## IPs: qual colocar onde (importante!)

São 3 papéis diferentes de IP:

| Onde | Para quem é | IP correto |
|---|---|---|
| `WorldDBInfo.Host` (tabela) | Servidores → MySQL (interno) | `127.0.0.1` (não mexer) |
| `DB_HOST`/`UI_DB_HOST`/`DIST_DB_HOST` (confs) | Servidores → MySQL (interno) | `127.0.0.1` (não mexer) |
| `LoginServerIP`/`SharedServerIP` (confs) | Servidor ↔ Servidor (interno) | `127.0.0.1` (não mexer) |
| `GameServerInfo.IP` (tabela) | Cliente → gameserver (loginserver repassa) | 127.0.0.1 se cliente na mesma máquina; senão IP da VM na LAN |
| IP do loginserver configurado NO CLIENTE | Cliente → loginserver (1ª conexão) | idem acima |

Regra: cliente na mesma máquina → `127.0.0.1` em tudo (estado atual, funcionando).
Cliente em outro PC → precisa do IP da VM na LAN + rede da VM em bridge.

Obs.: `BillingServerIP: 111.111.111.111` e `LogServerIP: 111.111.111.111` no
`gameserver.conf` são lixo do servidor original — não atrapalhou, mas se der
timeout estranho no gameserver, trocar para `127.0.0.1`.

## Rede da VM (VirtualBox) — para cliente em outro PC

A VM está com **NAT** (interface `enp0s3` = `10.0.2.15`, só alcançável de dentro
da VM). Para parecer um servidor "de verdade" na rede local:

1. Desligar a VM → VirtualBox (host): Configurações → Rede → Adaptador 1 →
   Conectado a: **Adaptador em ponte (Bridged Adapter)** → Nome: placa física do host.
2. Ligar a VM → `ip -4 addr` → anotar o novo IP (ex.: 192.168.0.x).
3. Atualizar `GameServerInfo.IP` no banco: `UPDATE DARKEDEN.GameServerInfo SET IP='<novo-ip>';`
4. No cliente (outro PC): loginserver = `<novo-ip>:9999`.
5. Liberar portas 9999, 9998, 9977 no firewall do host/router.
6. Se o host usar Wi-Fi e a ponte falhar: plano B = NAT + Encaminhamento de portas
   no VirtualBox (mapear 9999/9998/9977 do host → VM; cliente usa o IP do host).

## O que são bin/update e bin/updateserver

- `updateserver` = servidor TCP (porta 3000) de auto-update do launcher/cliente
  (config `src/conf/updateserver.conf`, aponta para servidores coreanos mortos).
- `update` = ferramenta de geração de patches (escreve index.dat em
  `/home/darkeden/data/patch` — caminho hardcoded).
- **Não rodam no host**: são ELF 32-bit dinâmicos e o host não tem
  `/lib/ld-linux.so.2` (os 3 servidores do jogo são estáticos, por isso rodam).
- **Não são necessários** para o servidor/jogo — só para o auto-update do cliente.
