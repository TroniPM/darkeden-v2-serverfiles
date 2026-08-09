-- =====================================================================
-- patch-compat.sql - Compatibilidade do banco REAL (arquivos FRM/MYD/MYI)
-- ---------------------------------------------------------------------
-- Executado automaticamente pelo entrypoint do MySQL 4.1 (darkeden-mysql)
-- na 1a subida, DEPOIS de copiar os arquivos reais do servidor original
-- (vsserver/sqls/ — tarballs DARKEDEN.tar.gz/USERINFO.tar.gz) para o datadir.
--
-- MOTIVO: os arquivos .FRM/.MYD/.MYI vieram do servidor ORIGINAL e
-- apontam para a infraestrutura dele (IP 192.168.80.2, usuário vsvs,
-- nomes de mapa em caixa que não batem com os arquivos em disco).
-- Sem este patch, nenhum servidor conecta no banco local.
--
-- USO (pode rodar manualmente, é idempotente):
--   mysql --default-character-set=latin1 -uroot < patch-compat.sql
--
-- ⚠️ Se trocar a pasta de dados do servidor (vsserver/data/), rodar de
--    novo a seção de ZoneInfo com os novos nomes exatos em disco.
-- =====================================================================

-- ------------------------------------------------------------------
-- 1) WorldDBInfo: MySQL original (192.168.80.2, user vsvs) -> local
--    (loginserver/sharedserver/gameserver usam esta tabela para
--     conectar nos bancos adicionais de cada WorldID)
-- ------------------------------------------------------------------
UPDATE DARKEDEN.WorldDBInfo SET Host='127.0.0.1', User='elcastle', Password='elca110';

-- ------------------------------------------------------------------
-- 2) GameServerInfo: IP anunciado aos clientes -> local
-- ------------------------------------------------------------------
UPDATE DARKEDEN.GameServerInfo SET IP='127.0.0.1';

-- ------------------------------------------------------------------
-- 3) ZoneInfo: zonas SEM arquivos de mapa (.smp/.ssi não existem em
--    nenhuma pasta de data do projeto) -> fora dos grupos ativos,
--    senão o gameserver morre ao iniciar com FileNotExistException
--    (menegroth 1f-6f, tiffauges castle, hell garden, office)
-- ------------------------------------------------------------------
UPDATE DARKEDEN.ZoneInfo SET ZoneGroupID=0 WHERE ZoneID IN
 (1701,1702,1703,1704,1705,1706,
  1801,1802,1803,1804,
  5000,5010,5020,5030,5040,5050,
  8003,8004);

-- ------------------------------------------------------------------
-- 4) ZoneInfo: nomes de arquivo EXATOS como estão em vsserver/data/
--    (caixa mista). NECESSÁRIO: o Zone::load tenta abrir com o nome do
--    banco e, se falhar, faz um retry em minúsculas — mas o ifstream
--    (STLport no Linux) não limpa o estado de erro do 1o open, então o
--    retry NUNCA funciona. O nome tem que bater EXATO de primeira.
--    (idempotente: roda de novo sem efeito)
-- ------------------------------------------------------------------
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_ne.smp', SsiFileName='eslania_ne.ssi' WHERE ZoneID=11;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_NW.smp', SsiFileName='eslania_NW.ssi' WHERE ZoneID=12;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_se.smp', SsiFileName='eslania_se.ssi' WHERE ZoneID=13;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_sw.smp', SsiFileName='eslania_sw.ssi' WHERE ZoneID=14;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_ne.smp', SsiFileName='limbo_lair_ne.ssi' WHERE ZoneID=21;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_nw.smp', SsiFileName='limbo_lair_nw.ssi' WHERE ZoneID=22;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_se.smp', SsiFileName='limbo_lair_se.ssi' WHERE ZoneID=23;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_sw.smp', SsiFileName='limbo_lair_sw.ssi' WHERE ZoneID=24;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_ne.smp', SsiFileName='drobeta_ne.ssi' WHERE ZoneID=31;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_nw.smp', SsiFileName='drobeta_nw.ssi' WHERE ZoneID=32;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_se.smp', SsiFileName='drobeta_se.ssi' WHERE ZoneID=33;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_sw.smp', SsiFileName='drobeta_sw.ssi' WHERE ZoneID=34;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_ne.smp', SsiFileName='rodin_ne.ssi' WHERE ZoneID=41;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_nw.smp', SsiFileName='rodin_nw.ssi' WHERE ZoneID=42;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_se.smp', SsiFileName='rodin_se.ssi' WHERE ZoneID=43;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_sw.smp', SsiFileName='rodin_sw.ssi' WHERE ZoneID=44;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_ne.smp', SsiFileName='timore_ne.ssi' WHERE ZoneID=51;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_nw.smp', SsiFileName='timore_nw.ssi' WHERE ZoneID=52;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_se.smp', SsiFileName='timore_se.ssi' WHERE ZoneID=53;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_sw.smp', SsiFileName='timore_sw.ssi' WHERE ZoneID=54;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_ne.smp', SsiFileName='perona_ne.ssi' WHERE ZoneID=61;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_nw.smp', SsiFileName='perona_nw.ssi' WHERE ZoneID=62;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_se.smp', SsiFileName='perona_se.ssi' WHERE ZoneID=63;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_sw.smp', SsiFileName='perona_sw.ssi' WHERE ZoneID=64;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='triste_ne.smp', SsiFileName='triste_ne.ssi' WHERE ZoneID=71;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='triste_nw.smp', SsiFileName='triste_nw.ssi' WHERE ZoneID=72;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='triste_se.smp', SsiFileName='triste_se.ssi' WHERE ZoneID=73;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='triste_sw.smp', SsiFileName='triste_sw.ssi' WHERE ZoneID=74;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_ne.smp', SsiFileName='stray_ne.ssi' WHERE ZoneID=75;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_nw.smp', SsiFileName='stray_nw.ssi' WHERE ZoneID=81;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_se.smp', SsiFileName='stray_se.ssi' WHERE ZoneID=82;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_sw.smp', SsiFileName='stray_sw.ssi' WHERE ZoneID=83;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_nw.smp', SsiFileName='eslania_nw.ssi' WHERE ZoneID=84;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='triste_dungeon.smp', SsiFileName='triste_dungeon.ssi' WHERE ZoneID=91;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='dragon_1f.smp', SsiFileName='dragon_1f.ssi' WHERE ZoneID=92;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='dragon_2f.smp', SsiFileName='dragon_2f.ssi' WHERE ZoneID=93;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_dungeon.smp', SsiFileName='stray_dungeon.ssi' WHERE ZoneID=94;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1005;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1006;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1007;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1008;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1009;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1010;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1011;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1012;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_dungeon.smp', SsiFileName='drobeta_dungeon.ssi' WHERE ZoneID=1013;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_dungeon.smp', SsiFileName='limbo_dungeon.ssi' WHERE ZoneID=1020;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1100;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1101;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1102;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1103;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1104;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1105;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1106;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1111;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1112;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1113;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1114;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1115;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1121;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1122;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1123;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1124;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1125;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1126;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1127;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1128;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1129;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1130;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1131;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1132;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1133;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1134;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1201;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1202;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1203;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1204;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1205;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1206;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1211;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1212;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1221;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1222;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1231;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1232;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1241;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1242;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1251;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1252;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1261;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_dungeon.smp', SsiFileName='rodin_dungeon.ssi' WHERE ZoneID=1262;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1301;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1302;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1303;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1311;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1312;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1313;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1314;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1321;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1322;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1323;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_dungeon.smp', SsiFileName='timore_dungeon.ssi' WHERE ZoneID=1324;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_dungeon.smp', SsiFileName='perona_dungeon.ssi' WHERE ZoneID=1401;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_dungeon.smp', SsiFileName='perona_dungeon.ssi' WHERE ZoneID=1402;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_dungeon.smp', SsiFileName='perona_dungeon.ssi' WHERE ZoneID=1410;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_dungeon.smp', SsiFileName='perona_dungeon.ssi' WHERE ZoneID=1411;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_dungeon.smp', SsiFileName='perona_dungeon.ssi' WHERE ZoneID=1412;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_dungeon.smp', SsiFileName='perona_dungeon.ssi' WHERE ZoneID=1413;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=1500;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_e.smp', SsiFileName='adam_new_e.ssi' WHERE ZoneID=1501;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_n.smp', SsiFileName='adam_new_n.ssi' WHERE ZoneID=1502;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_s.smp', SsiFileName='adam_new_s.ssi' WHERE ZoneID=1503;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_w.smp', SsiFileName='adam_new_w.ssi' WHERE ZoneID=1504;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=1505;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=1506;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_ne.smp', SsiFileName='stray_ne.ssi' WHERE ZoneID=1600;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_nw.smp', SsiFileName='stray_nw.ssi' WHERE ZoneID=1601;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_se.smp', SsiFileName='stray_se.ssi' WHERE ZoneID=1602;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_sw.smp', SsiFileName='stray_sw.ssi' WHERE ZoneID=1603;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_ne.smp', SsiFileName='stray_ne.ssi' WHERE ZoneID=1604;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_nw.smp', SsiFileName='stray_nw.ssi' WHERE ZoneID=1611;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_nw.smp', SsiFileName='stray_nw.ssi' WHERE ZoneID=1612;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='stray_ne.smp', SsiFileName='stray_ne.ssi' WHERE ZoneID=1621;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2000;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2010;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2011;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2012;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2013;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2014;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2020;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2021;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2022;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2023;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2024;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=2101;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=2102;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=3001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=3002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=3003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4005;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='woban_1f.smp', SsiFileName='woban_1f.ssi' WHERE ZoneID=8000;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='woban_2f.smp', SsiFileName='woban_2f.ssi' WHERE ZoneID=8001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='woban_2f.smp', SsiFileName='woban_2f.ssi' WHERE ZoneID=8002;

-- ------------------------------------------------------------------
-- 5) Usuário do server — NÃO existe nos arquivos reais (o banco mysql/
--    é recriado pelo mysql_install_db). O GRANT cria o usuário, e a
--    senha é convertida para o formato ANTIGO (16 bytes), único que o
--    cliente libmysqlclient 3.23 dos servidores entende.
--    Remove também usuários anônimos (senão 'elcastle' via localhost
--    cai no anônimo e leva Access denied).
-- ------------------------------------------------------------------
GRANT ALL PRIVILEGES ON DARKEDEN.* TO 'elcastle'@'%' IDENTIFIED BY 'elca110';
GRANT ALL PRIVILEGES ON USERINFO.* TO 'elcastle'@'%' IDENTIFIED BY 'elca110';
UPDATE mysql.user SET Password=OLD_PASSWORD('elca110') WHERE User='elcastle' AND Host='%';
DELETE FROM mysql.user WHERE User='';
FLUSH PRIVILEGES;

-- FIM do patch
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_ne.smp', SsiFileName='eslania_ne.ssi' WHERE ZoneID=11;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_NW.smp', SsiFileName='eslania_NW.ssi' WHERE ZoneID=12;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_se.smp', SsiFileName='eslania_se.ssi' WHERE ZoneID=13;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_sw.smp', SsiFileName='eslania_sw.ssi' WHERE ZoneID=14;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_ne.smp', SsiFileName='limbo_lair_ne.ssi' WHERE ZoneID=21;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_nw.smp', SsiFileName='limbo_lair_nw.ssi' WHERE ZoneID=22;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_se.smp', SsiFileName='limbo_lair_se.ssi' WHERE ZoneID=23;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_lair_sw.smp', SsiFileName='limbo_lair_sw.ssi' WHERE ZoneID=24;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_ne.smp', SsiFileName='drobeta_ne.ssi' WHERE ZoneID=31;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_nw.smp', SsiFileName='drobeta_nw.ssi' WHERE ZoneID=32;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_se.smp', SsiFileName='drobeta_se.ssi' WHERE ZoneID=33;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_sw.smp', SsiFileName='drobeta_sw.ssi' WHERE ZoneID=34;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_ne.smp', SsiFileName='rodin_ne.ssi' WHERE ZoneID=41;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_nw.smp', SsiFileName='rodin_nw.ssi' WHERE ZoneID=42;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_se.smp', SsiFileName='rodin_se.ssi' WHERE ZoneID=43;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rodin_sw.smp', SsiFileName='rodin_sw.ssi' WHERE ZoneID=44;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_ne.smp', SsiFileName='timore_ne.ssi' WHERE ZoneID=51;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_nw.smp', SsiFileName='timore_nw.ssi' WHERE ZoneID=52;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_se.smp', SsiFileName='timore_se.ssi' WHERE ZoneID=53;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='timore_sw.smp', SsiFileName='timore_sw.ssi' WHERE ZoneID=54;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_ne.smp', SsiFileName='perona_ne.ssi' WHERE ZoneID=61;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_nw.smp', SsiFileName='perona_nw.ssi' WHERE ZoneID=62;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_se.smp', SsiFileName='perona_se.ssi' WHERE ZoneID=63;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='perona_sw.smp', SsiFileName='perona_sw.ssi' WHERE ZoneID=64;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_e.smp', SsiFileName='adam_new_e.ssi' WHERE ZoneID=71;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=72;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_w.smp', SsiFileName='adam_new_w.ssi' WHERE ZoneID=73;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c_n.smp', SsiFileName='adam_new_c_n.ssi' WHERE ZoneID=74;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c_s.smp', SsiFileName='adam_new_c_s.ssi' WHERE ZoneID=75;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castalo_ne.smp', SsiFileName='castalo_ne.ssi' WHERE ZoneID=81;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='vranco_ne.smp', SsiFileName='vranco_ne.ssi' WHERE ZoneID=91;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='vranco_nw.smp', SsiFileName='vranco_nw.ssi' WHERE ZoneID=92;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='vranco_se.smp', SsiFileName='vranco_se.ssi' WHERE ZoneID=93;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='vranco_sw.smp', SsiFileName='vranco_sw.ssi' WHERE ZoneID=94;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='slayers_training.smp', SsiFileName='slayers_training.ssi' WHERE ZoneID=1001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='vampire_village.smp', SsiFileName='vampire_village.ssi' WHERE ZoneID=1003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_dungeon.smp', SsiFileName='limbo_dungeon.ssi' WHERE ZoneID=1004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_ox.smp', SsiFileName='drobeta_ox.ssi' WHERE ZoneID=1005;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='drobeta_stadium.smp', SsiFileName='drobeta_stadium.ssi' WHERE ZoneID=1006;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rasen_yard.smp', SsiFileName='rasen_yard.ssi' WHERE ZoneID=1007;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='kali_cave.smp', SsiFileName='kali_cave.ssi' WHERE ZoneID=1008;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='rasen_training.smp', SsiFileName='rasen_training.ssi' WHERE ZoneID=1009;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='tunnel_peiac.smp', SsiFileName='tunnel_peiac.ssi' WHERE ZoneID=1010;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='losttaiyan_b1f.smp', SsiFileName='losttaiyan_b1f.ssi' WHERE ZoneID=1011;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='losttaiyan_b2f.smp', SsiFileName='losttaiyan_b2f.ssi' WHERE ZoneID=1012;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=1013;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='limbo_dungeon.smp', SsiFileName='limbo_dungeon.ssi' WHERE ZoneID=1020;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1100;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1101;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1102;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1103;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1104;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1105;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1106;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1111;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1112;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1113;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1114;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1115;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1121;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1122;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1123;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1124;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1125;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1126;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1127;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1128;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1129;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1130;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1131;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1132;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1133;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='eslania_dungeon.smp', SsiFileName='eslania_dungeon.ssi' WHERE ZoneID=1134;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castle_octavus.smp', SsiFileName='castle_octavus.ssi' WHERE ZoneID=1201;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castle_tertius.smp', SsiFileName='castle_tertius.ssi' WHERE ZoneID=1202;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castle_septimus.smp', SsiFileName='castle_septimus.ssi' WHERE ZoneID=1203;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castle_quartus.smp', SsiFileName='castle_quartus.ssi' WHERE ZoneID=1204;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castle_pentanus.smp', SsiFileName='castle_pentanus.ssi' WHERE ZoneID=1205;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castle_hexserius.smp', SsiFileName='castle_hexserius.ssi' WHERE ZoneID=1206;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='octavus_dungeon1f.smp', SsiFileName='octavus_dungeon1f.ssi' WHERE ZoneID=1211;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='octavus_dungeon2f.smp', SsiFileName='octavus_dungeon2f.ssi' WHERE ZoneID=1212;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='tertius_dungeon1f.smp', SsiFileName='tertius_dungeon1f.ssi' WHERE ZoneID=1221;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='tertius_dungeon2f.smp', SsiFileName='tertius_dungeon2f.ssi' WHERE ZoneID=1222;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='septimus_dungeon1f.smp', SsiFileName='septimus_dungeon1f.ssi' WHERE ZoneID=1231;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='septimus_dungeon2f.smp', SsiFileName='septimus_dungeon2f.ssi' WHERE ZoneID=1232;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='quartus_dungeon1f.smp', SsiFileName='quartus_dungeon1f.ssi' WHERE ZoneID=1241;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='quartus_dungeon2f.smp', SsiFileName='quartus_dungeon2f.ssi' WHERE ZoneID=1242;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='pentanus_dungeon1f.smp', SsiFileName='pentanus_dungeon1f.ssi' WHERE ZoneID=1251;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='pentanus_dungeon2f.smp', SsiFileName='pentanus_dungeon2f.ssi' WHERE ZoneID=1252;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='hexserius_dungeon1f.smp', SsiFileName='hexserius_dungeon1f.ssi' WHERE ZoneID=1261;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='hexserius_dungeon2f.smp', SsiFileName='hexserius_dungeon2f.ssi' WHERE ZoneID=1262;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='slayerpk.smp', SsiFileName='slayerpk.ssi' WHERE ZoneID=1301;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='vampirepk.smp', SsiFileName='vampirepk.ssi' WHERE ZoneID=1302;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='freepk.smp', SsiFileName='freepk.ssi' WHERE ZoneID=1303;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ousters_village.smp', SsiFileName='ousters_village.ssi' WHERE ZoneID=1311;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ousters_dungeon01.smp', SsiFileName='ousters_dungeon01.ssi' WHERE ZoneID=1321;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ousters_dungeon02.smp', SsiFileName='ousters_dungeon02.ssi' WHERE ZoneID=1322;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ousters_dungeon03.smp', SsiFileName='ousters_dungeon03.ssi' WHERE ZoneID=1323;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ousters_dungeon04.smp', SsiFileName='ousters_dungeon04.ssi' WHERE ZoneID=1324;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='lusttower_1f.smp', SsiFileName='lusttower_1f.ssi' WHERE ZoneID=1401;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='lusttower_2f.smp', SsiFileName='lusttower_2f.ssi' WHERE ZoneID=1402;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gdr_illusion_01.smp', SsiFileName='gdr_illusion_01.ssi' WHERE ZoneID=1410;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gdr_illusion_02.smp', SsiFileName='gdr_illusion_02.ssi' WHERE ZoneID=1411;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gdr_lair_01.smp', SsiFileName='gdr_lair_01.ssi' WHERE ZoneID=1412;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gdr_lair_hard.smp', SsiFileName='gdr_lair_hard.ssi' WHERE ZoneID=1413;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=1500;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_e.smp', SsiFileName='adam_new_e.ssi' WHERE ZoneID=1501;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='siege_warfare.smp', SsiFileName='siege_warfare.ssi' WHERE ZoneID=1502;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='siege_warfare.smp', SsiFileName='siege_warfare.ssi' WHERE ZoneID=1503;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_w.smp', SsiFileName='adam_new_w.ssi' WHERE ZoneID=1504;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=1505;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='adam_new_c.smp', SsiFileName='adam_new_c.ssi' WHERE ZoneID=1506;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='path_to_fears.smp', SsiFileName='path_to_fears.ssi' WHERE ZoneID=1600;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ik_offic.smp', SsiFileName='ik_offic.ssi' WHERE ZoneID=1601;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ik_lab.smp', SsiFileName='ik_lab.ssi' WHERE ZoneID=1602;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ik_lab_b1f.smp', SsiFileName='ik_lab_b1f.ssi' WHERE ZoneID=1603;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='ik_lab_b2f.smp', SsiFileName='ik_lab_b2f.ssi' WHERE ZoneID=1604;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='under_pass_1f.smp', SsiFileName='under_pass_1f.ssi' WHERE ZoneID=1611;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='under_pass_2f.smp', SsiFileName='under_pass_2f.ssi' WHERE ZoneID=1612;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='castellum.smp', SsiFileName='castellum.ssi' WHERE ZoneID=1621;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2000;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2010;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2011;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2012;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2013;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2014;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2020;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2021;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2022;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2023;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='alter_of_blood.smp', SsiFileName='alter_of_blood.ssi' WHERE ZoneID=2024;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=2101;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=2102;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=3001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=3002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=3003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4002;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='asylion_dungeon.smp', SsiFileName='asylion_dungeon.ssi' WHERE ZoneID=4005;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='devt.smp', SsiFileName='devt.ssi' WHERE ZoneID=8000;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='survival.smp', SsiFileName='survival.ssi' WHERE ZoneID=8001;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gate_of_alter.smp', SsiFileName='gate_of_alter.ssi' WHERE ZoneID=8005;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='clan_hdqrs.smp', SsiFileName='clan_hdqrs.ssi' WHERE ZoneID=9003;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='clan_hdqrs.smp', SsiFileName='clan_hdqrs.ssi' WHERE ZoneID=9004;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='clan_hdqrs.smp', SsiFileName='clan_hdqrs.ssi' WHERE ZoneID=9005;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gate_of_alter.smp', SsiFileName='gate_of_alter.ssi' WHERE ZoneID=9006;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gate_of_alter.smp', SsiFileName='gate_of_alter.ssi' WHERE ZoneID=9009;
UPDATE DARKEDEN.ZoneInfo SET SmpFileName='gate_of_alter.smp', SsiFileName='gate_of_alter.ssi' WHERE ZoneID=9010;

-- ------------------------------------------------------------------
-- 5) Zonas adam_* (1500-1506): mapa do cliente é 128x256 e os
--    ZoneTriggers originais passam de X=156/169 -> Assert em
--    Zone.cpp:2396 (loadTriggeredPortal) derruba o gameserver.
--    Em vez de desativar, CORRIGIR os triggers para dentro do mapa
--    e manter as zonas ATIVAS (ZoneGroupID=1).
-- ------------------------------------------------------------------
UPDATE DARKEDEN.ZoneTriggers SET X1=123, X2=127 WHERE ZoneID IN (1501,1504,1505,1506) AND X1=156 AND X2=160;
UPDATE DARKEDEN.ZoneTriggers SET X1=122, X2=127 WHERE ZoneID IN (1501,1504,1505,1506) AND X1=169 AND X2=174;
UPDATE DARKEDEN.ZoneInfo SET ZoneGroupID=1 WHERE ZoneID IN (1500,1501,1504,1505,1506);

-- ------------------------------------------------------------------
-- 6) WayPointInfo da zona 1105 (eslania_dungeon): waypoints com
--    X=165 e Y=201 fora do mapa -> trazidos para dentro.
-- ------------------------------------------------------------------
UPDATE DARKEDEN.WayPointInfo SET Y=127 WHERE ZoneID=1105 AND Y=201;
UPDATE DARKEDEN.WayPointInfo SET X=127 WHERE ZoneID=1105 AND X=165;

-- ------------------------------------------------------------------
-- 7) NPCs das zonas adam_* (1501/1504/1505/1506) spawnavam em
--    (166,40) — fora do mapa 128x256 -> reposicionados no tile
--    livre mais próximo (via trigger SetPosition). Posições
--    revalidadas com o parser do SMP (flag 0x02=bloqueado, 0x80=portal).
-- ------------------------------------------------------------------
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 127'), 'Y : 40', 'Y : 30') WHERE TriggerID=1583;
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 126'), 'Y : 40', 'Y : 1') WHERE TriggerID=1619;
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 126'), 'Y : 40', 'Y : 5') WHERE TriggerID=1631;
UPDATE DARKEDEN.Triggers SET Actions = REPLACE(REPLACE(Actions, 'X : 166', 'X : 126'), 'Y : 40', 'Y : 5') WHERE TriggerID=1643;

-- FIM do patch
