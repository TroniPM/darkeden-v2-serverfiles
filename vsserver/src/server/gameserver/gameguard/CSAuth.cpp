//////////////////////////////////////////////////////////////////////////////
// Filename    : CSAuth.cpp
// Description : Stub implementation of the NProtect GameGuard server SDK
//               (CCSAuth + global auth functions).
//
// ⚠️⚠️⚠️ AVISO IMPORTANTE ⚠️⚠️⚠️
// ----------------------------------------------------------------------------
// O GameGuard original (NProtect/INCA 2004) NÃO funcionará neste servidor.
// Motivos:
//   1. A SDK `libCSAuth.a` era proprietária e NUNCA foi incluída no source.
//   2. As tabelas CSAuth.tab / CSAuth.idx do projeto são PLACEHOLDERS vazios
//      (40 bytes / 1 byte — os dados reais de 2009 se perderam).
//   3. Os servidores centrais da NProtect (que validavam o anti-cheat) estão
//      DESATIVADOS há ~15 anos.
//   4. O driver de kernel do client é fechado e descontinuado.
//
// Este stub PRESERVA a arquitetura de 2005 (EventAuth roda a cada 5 min,
// GCAuthKey é enviado/recebido normalmente), mas SEMPRE autentica o jogador
// (IsAuth()==true, CheckAuthDword()==true) — ou seja, NINGUÉM é kickado.
// Isso é exatamente o que todo servidor privado de DarkEden faz.
//////////////////////////////////////////////////////////////////////////////

// O header CSAuth.h tem o typedef de DWORD comentado (em produção DWORD vem
// de Types.h/SystemTypes.h, incluído antes via GamePlayer.h). Para o stub
// ser compilável de forma autônoma, definimos aqui ANTES do include.
typedef unsigned long DWORD;

#include "CSAuth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===========================================================================
// Funções globais (extern "C" no header)
// ===========================================================================

// Carrega a tabela de autenticação. No original, lia CSAuth.tab e gerava a
// tabela SEED. Aqui: leitura é opcional (placeholder), sempre sucesso.
DWORD __cdecl LoadAuthTable(LPCSTR lpszPath)
{
	// Arquivo é placeholder — ignora conteúdo, valida apenas que abre.
	FILE* fp = fopen(lpszPath, "rb");
	if (fp != NULL)
		fclose(fp);
	return 0; // 0 = sucesso (convenção original)
}

// Carrega o índice. Mesmo tratamento do LoadAuthTable.
DWORD __cdecl LoadAuthIndex(LPCSTR lpszPath)
{
	FILE* fp = fopen(lpszPath, "rb");
	if (fp != NULL)
		fclose(fp);
	return 0;
}

// Define a tabela diretamente em memória. Sem uso real no stub.
DWORD __cdecl SetAuthTable(LPBYTE lpTable, DWORD dwSize)
{
	return 0;
}

// Define o índice. Sem uso real no stub.
DWORD __cdecl SetAuthIndex(DWORD dwIndex)
{
	return 0;
}

// Inicializa proteção de pacote. Sem uso real no stub.
DWORD __cdecl InitPacketProtect(LPCSTR lpszUserKey, DWORD dwUseSeqCheck)
{
	return 0;
}

// ===========================================================================
// Classe CCSAuth
// ===========================================================================

CCSAuth::CCSAuth()
{
	Init();
}

CCSAuth::~CCSAuth()
{
}

// Inicialização: zera estado e semente aleatória.
void CCSAuth::Init()
{
	m_dwSeed        = (DWORD)time(NULL);
	m_dwAuthValue   = 0;
	m_bAuth         = 1;      // 1 = autenticado (stub: sempre OK)
	m_dwCurrIndex   = 0;
	m_dwClientSequenceNumber = 0;
	m_dwServerSequenceNumber = 0;
	m_dwPPLastError = 0;
	m_dwSeq         = 0;
	memset(m_table, 0, sizeof(m_table));
	memset(m_adwLastSeqs, 0, sizeof(m_adwLastSeqs));
}

// Jogador sempre autenticado.
DWORD CCSAuth::IsAuth()
{
	return 1;
}

// Devolve um dword de autenticação qualquer (o client não valida conteúdo).
DWORD CCSAuth::GetAuthDword()
{
	return m_dwAuthValue++;
}

// Valida a resposta do client — sempre aceita.
DWORD CCSAuth::CheckAuthDword(DWORD dwReturnValue)
{
	return 1;
}

// Extrai resultados da autenticação — sem uso real no stub.
DWORD CCSAuth::GetAuthResults(DWORD dwAuthValue, LPDWORD lpdwResult, DWORD dwCount)
{
	return 0;
}

// Criptografia de pacote — sem uso real no stub (não criptografa).
DWORD CCSAuth::EncryptPacket(LPVOID lpData, DWORD dwLength)
{
	return 0;
}

// Descriptografia de pacote — sem uso real no stub (não descriptografa).
DWORD CCSAuth::DecryptPacket(LPVOID lpData, DWORD dwLength)
{
	return 0;
}

// Último erro de proteção de pacote — sempre sem erro.
DWORD CCSAuth::PPGetLastError()
{
	return 0;
}

// Transformação de dword — mantido como no original (transparência).
DWORD CCSAuth::TransAuthDword(DWORD dwAuth, int index)
{
	return (dwAuth << (index % 32)) | (dwAuth >> (32 - (index % 32)));
}

// PRNG — semente simples (qualidade irrelevante no stub).
void CCSAuth::np_srandom(DWORD initial_seed)
{
	m_dwSeed = initial_seed;
}

DWORD CCSAuth::np_random()
{
	// PRNG linear congruential simples (qualidade irrelevante no stub)
	m_dwSeed = m_dwSeed * 1103515245u + 12345u;
	return (m_dwSeed >> 16) & 0x7FFF;
}

// Verifica o último pacote — sempre OK no stub.
DWORD CCSAuth::CheckLastPacket(DWORD dwSeq)
{
	return 1;
}
