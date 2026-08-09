//////////////////////////////////////////////////////////////////////////////
// Filename    : libcpsso.cpp
// Description : Reimplementation of the NetMarble SDK cookie parser
//               (libcpsso).  The original library was a proprietary SDK
//               that was never shipped with the server source, so the
//               loginserver could not link (No rule to make target
//               libcpsso.a).  This stub provides the real behaviour of
//               GetCPCookieValue(): it parses a cookie string of the form
//               "var1=value1&var2=value2" (both '&' and ';' separators are
//               accepted) and copies the value of the requested variable.
//////////////////////////////////////////////////////////////////////////////

#include "libcpsso.h"

#include <string.h>

bool GetCPCookieValue(const char* szCpCookie, const char* szVar, char* pstrRtnValue)
{
	if (szCpCookie == NULL || szVar == NULL || pstrRtnValue == NULL)
		return false;

	// reset the output buffer
	pstrRtnValue[0] = '\0';

	const char* p = szCpCookie;

	while (*p != '\0')
	{
		// skip separators and whitespace
		while (*p == '&' || *p == ';' || *p == ' ')
			p++;

		if (*p == '\0')
			break;

		// find the '=' that separates the variable name from its value
		const char* pEq = strchr(p, '=');
		if (pEq == NULL)
			break; // malformed cookie

		size_t nameLen = pEq - p;

		const char* pVal = pEq + 1;
		const char* pEnd = pVal;
		while (*pEnd != '\0' && *pEnd != '&' && *pEnd != ';')
			pEnd++;

		if (nameLen == strlen(szVar) && strncmp(p, szVar, nameLen) == 0)
		{
			size_t valLen = pEnd - pVal;
			if (valLen == 0)
				return false; // empty value is not a valid cookie field

			memcpy(pstrRtnValue, pVal, valLen);
			pstrRtnValue[valLen] = '\0';
			return true;
		}

		// advance to the next variable
		p = pEnd;
	}

	return false;
}
