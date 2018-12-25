///////////////////////////////////////////////////////////////////
// ���￡ ���� �������� ���� �� ���� ���� �� ����� ó����ƾ.
///////////////////////////////////////////////////////////////////

#ifndef __RACE_WAR_H__
#define __RACE_WAR_H__

#include "War.h"

class Mutex;
class PlayerCreature;

class RaceWar : public War
{
public:
	RaceWar( WarState warState, WarID_t warID=0 );
	virtual ~RaceWar();

	WarType_t		getWarType() const				{ return WAR_RACE; }
	string 			getWarType2DBString() const		{ return "RACE"; }
	string			getWarName() ; 

public:
	//void			sendWarStartMessage() ;
	void			sendWarEndMessage() ;

protected :
	void 			executeStart();
	void 			executeEnd();

	void 			recordRaceWarStart();
	void 			recordRaceWarEnd();

public :
	void    makeWarScheduleInfo( WarScheduleInfo* pWSI ) ;
	void 	makeWarInfo(WarInfo* pWarInfo) ;

	virtual string	toString() ;

private:
};

#endif // __WAR_H__
