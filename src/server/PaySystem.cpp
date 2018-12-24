//---------------------------------------------------------------------------
// Filename   : PaySystem.h
// Written by : sigi
// Description : 
//---------------------------------------------------------------------------
// ���� ���� �ȵ� �� :
//   PC�� ��� �ð� �� ��.. ���� ��� �ð��� 60��*UserLimit���� ���� ��쿡
//   �� Ÿ�ֿ̹� ���ӹ濡�� UserLimit���� ��~ �����ϸ�
//   �ִ� 60��*(UserLimit-1��)������ �ð��� �� play�� �� �ְ� �ȴ�.
//   
// �ذ� ��� :
//   ���ӹ��� ���� UserLimit�� ����ؼ�
//   �ð��� 60��*UserLimit���� ������
//   �ð� üũ Ÿ�̹��� 60��/UserLimit�� �ؾߵɱ�? -_-
//   �� �� ȿ�����ΰ� ����?
//   �ϴ��� ���񽺷� ���ܵѱ�?
//
// --> updatePayPlayTime()���� ó���ߴ�.
//---------------------------------------------------------------------------

#include "PaySystem.h"
#include "database/DB.h"
#include "Thread.h"

#include "Properties.h"

//---------------------------------------------------------------------------
// �� �ʸ��� üũ�� ���ΰ�?
//---------------------------------------------------------------------------
const int DELAY_PAY_TIME_UPDATE = 3600;	// 1�ð� = 60��
//const int DELAY_PAY_TIME_UPDATE = 10;	// 10�ʸ��� - �׽�Ʈ��
const int MINUTE_PAY_TIME_DECREASE = DELAY_PAY_TIME_UPDATE/60;
//const int MINUTE_PAY_TIME_DECREASE = 60;

//---------------------------------------------------------------------------
// �������� ���.. '�� �� ����' ��밡���ϴٰ� �� ��.. 
// ����� ���񽺷� �����Ѵ�.
//---------------------------------------------------------------------------
//const int PLUS_DEADLINE_MIN 	= 10;
const int PLUS_DEADLINE_SECOND	= 59;

//---------------------------------------------------------------------------
//
// constructor / destructor
//
//---------------------------------------------------------------------------
PaySystem::PaySystem()
{
	// ���ο������ü�迡 ���� ����..�̶�� �� �� �ִ�. ������ �ٲ�ߵȴ� -_-;
	m_bSetPersonValue = false;

	m_PayPlayType = PAY_PLAY_TYPE_PERSON;        		// ����/�׹�..
	m_PayType = PAY_TYPE_FREE;          		// ����/�ð�/�Ⱓ/��Ÿ..
	m_PayIPType = PAY_IP_TYPE_ALL;        		// ���ӹ��� ����� IP type

	m_PayPlayStartTime.tv_sec = 0;
	m_PayPlayStartTime.tv_usec = 0;

	m_PayPlayAvailableHours = 0;

	m_PayPlayFlag = 0;
	m_PCRoomID = 0;

	m_UserLimit = 0;
	m_UserMax = 0;

	m_bPremiumPlay = false;
	m_bPCRoomPlay = false;

	m_bFamilyPayAvailable = false;
	m_FamilyPayPartyType = FAMILY_PAY_PARTY_TYPE_NONE;
}

PaySystem::~PaySystem()
{
}

//---------------------------------------------------------------------------
// set Pay PlayAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setPayPlayAvailableDateTime(const string& pat) 
	throw (Error)
{
	__BEGIN_TRY

	
	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if (pat.size()==19)
	{
		int year  = atoi( pat.substr(0,4).c_str() );
		int month = atoi( pat.substr(5,2).c_str() );
		int day   = atoi( pat.substr(8,2).c_str() );
		int hour  = atoi( pat.substr(11,2).c_str() );
		int min   = atoi( pat.substr(14,2).c_str() );
		//int sec   = atoi( pat.substr(10,2).c_str() );

		// play������ �Ѱ� �ð��� �����صд�.
		m_PayPlayAvailableDateTime.setDate( VSDate(year, month, day) );
		m_PayPlayAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// ���� �Ұ� ���·� ����
		m_PayPlayAvailableDateTime.setDate( VSDate(2002, 1, 1) );
		m_PayPlayAvailableDateTime.setTime( VSTime(12, 10, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// set Family Pay PlayAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setFamilyPayPlayAvailableDateTime(const string& pat) 
	throw (Error)
{
	__BEGIN_TRY

	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if (pat.size()==19)
	{
		int year  = atoi( pat.substr(0,4).c_str() );
		int month = atoi( pat.substr(5,2).c_str() );
		int day   = atoi( pat.substr(8,2).c_str() );
		int hour  = atoi( pat.substr(11,2).c_str() );
		int min   = atoi( pat.substr(14,2).c_str() );
		//int sec   = atoi( pat.substr(10,2).c_str() );

		// play������ �Ѱ� �ð��� �����صд�.
		m_FamilyPayPlayAvailableDateTime.setDate( VSDate(year, month, day) );
		m_FamilyPayPlayAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// ���� �Ұ� ���·� ����
		m_FamilyPayPlayAvailableDateTime.setDate( VSDate(2002, 1, 1) );
		m_FamilyPayPlayAvailableDateTime.setTime( VSTime(12, 10, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// set Pay StartAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setPayStartAvailableDateTime(const string& pat) 
	throw (Error)
{
	__BEGIN_TRY

	
	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if (pat.size()==19)
	{
		int year  = atoi( pat.substr(0,4).c_str() );
		int month = atoi( pat.substr(5,2).c_str() );
		int day   = atoi( pat.substr(8,2).c_str() );
		int hour  = atoi( pat.substr(11,2).c_str() );
		int min   = atoi( pat.substr(14,2).c_str() );
		//int sec   = atoi( pat.substr(10,2).c_str() );

		// play������ �Ѱ� �ð��� �����صд�.
		m_PayStartAvailableDateTime.setDate( VSDate(year, month, day) );
		m_PayStartAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// ���� �Ұ� ���·� ����
		m_PayStartAvailableDateTime.setDate( VSDate(2099, 1, 1) );
		m_PayStartAvailableDateTime.setTime( VSTime(0, 0, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// is Pay PlayAvailable
//---------------------------------------------------------------------------
bool PaySystem::checkPayPlayAvailable()
{
	if (m_PayType!=PAY_TYPE_FREE && m_PayType!=PAY_TYPE_POST)
	{
		VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

		// �йи� ����� ��밡������ üũ�Ѵ�.
		if ( m_PayPlayAvailableDateTime != m_FamilyPayPlayAvailableDateTime
			&& currentDateTime <= m_FamilyPayPlayAvailableDateTime )
		{
			m_PayPlayAvailableDateTime = m_FamilyPayPlayAvailableDateTime;
			m_bFamilyPayAvailable = true;
		}

		// PC���� ��츸 StartDate�� üũ�Ѵ�.
		bool bAvailable = (m_PayPlayType!=PAY_PLAY_TYPE_PCROOM || currentDateTime >= m_PayStartAvailableDateTime)
							&& currentDateTime <= m_PayPlayAvailableDateTime;

		//cout << "checkPayPlay: " << currentDateTime.toString() << " <= " << m_PayPlayAvailableDateTime.toString() << endl;

		// ������ ���
		if (bAvailable)
		{
			m_PayType = PAY_TYPE_PERIOD;
		}
		else
		{ 
			bAvailable = m_PayPlayAvailableHours > 0;

			// ������ ���
			if (bAvailable)
			{
				m_PayType = PAY_TYPE_TIME;
			}
		}

		return bAvailable;
	}
	else if (m_PayType == PAY_TYPE_POST)
	{
		VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

		if (currentDateTime <= m_PayPlayAvailableDateTime)
			return true;
		else
			return false;
	}

	/*
	switch (m_PayType)
	{
		case PAY_TYPE_PERIOD :
		{
			VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());
			return currentDateTime <= m_PayPlayAvailableDateTime;
		}

		case PAY_TYPE_TIME :
		{
			return m_PayPlayAvailableHours > 0;
		}

		default : break;
	}
	*/

	return true;
}

//---------------------------------------------------------------------------
// set PayPlayValue
//---------------------------------------------------------------------------
void PaySystem::setPayPlayValue(PayType payType,
								const string& payPlayDate, int payPlayHours, uint payPlayFlag, const string& familyPayPlayDate)
{
	setPayType( payType );
	setPayPlayAvailableDateTime( payPlayDate );
	setPayPlayAvailableHours( payPlayHours );
	setPayPlayFlag( payPlayFlag );
	setFamilyPayPlayAvailableDateTime( familyPayPlayDate );

	m_bSetPersonValue = true;
}


//---------------------------------------------------------------------------
// update Pay PlayTime
//---------------------------------------------------------------------------
bool PaySystem::updatePayPlayTime(const string& playerID, const VSDateTime& currentDateTime, const Timeval& currentTime)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	switch (m_PayType)
	{
		//-----------------------------------------
		// �Ⱓ�� ������� ���
		//-----------------------------------------
		case PAY_TYPE_PERIOD :
		{
			// �� �ð� ������ �� ���� üũ�Ѵ�.
			// �Ⱓ�� ������� ���� 1�ð� ���� ���񽺵Ǿ ���� ���ٰ� ����
			if (currentTime.tv_sec >= m_PayPlayStartTime.tv_sec + DELAY_PAY_TIME_UPDATE)
			{
				m_PayPlayStartTime.tv_sec = currentTime.tv_sec;

				//cout << "[PAY_TYPE_PERIOD] " << endl;
				//cout << "CurrentDateTime = " << currentDateTime.toString().c_str() << endl;
				//cout << "PayPlayAvaiable = " << m_PayPlayAvailableDateTime.toString().c_str() << endl << endl;

				// �ð��� ��������.. ¥����.
				if (currentDateTime > m_PayPlayAvailableDateTime)
				{
					//throw ProtocolException("���ð��� �ٵƴ�.");
					m_PayPlayStartTime.tv_sec = 0;
					m_bPremiumPlay = false;
					return false;
				}
			}
		}
		break;

		//-----------------------------------------
		// �ð��� ������� ���
		//-----------------------------------------
		case PAY_TYPE_TIME :
		{
			int elapsedSec = currentTime.tv_sec - m_PayPlayStartTime.tv_sec;
			int remainSec = m_PayPlayAvailableHours*60;
			int UserMax = m_UserMax;


			// ����� ���̴� ���..
			if (m_PayPlayStartTime.tv_sec != 0
					// [1] 1�ð����� DB�� update ��Ų��.
				&& (currentTime.tv_sec >= m_PayPlayStartTime.tv_sec + DELAY_PAY_TIME_UPDATE
					// [2] ���ð��� 1�ð��� �� ���Ҵٸ�.. �ٷ� üũ..
					|| m_PayPlayAvailableHours < MINUTE_PAY_TIME_DECREASE
						&& elapsedSec > remainSec
					// [3] PC�� ����̰� 
					//      ���� �ð��� 1�ð�*UserMax ���� ����, 
					// 		���ð�*UserMax�� ���� �ð����� ũ��.. (UserMax�� 1~12�� ����:�ʹ� ���� üũ���� �ʰ��ϱ� ���ؼ�)
					//        �Ǵ�, ���� minute�� ����ڼ����� ������(1�о��� �� ���ٸ�), 1�и��� üũ�Ѵ�.
					|| m_PayPlayType==PAY_PLAY_TYPE_PCROOM 
						//&& elapsedSec <= DELAY_PAY_TIME_UPDATE
						&& m_PayPlayAvailableHours < MINUTE_PAY_TIME_DECREASE*UserMax
						&& (elapsedSec * (min(12, max(1, (int)m_UserMax))) > remainSec
							|| elapsedSec>=60 && m_PayPlayAvailableHours <= UserMax)
					)
				)
			{
				// �д����� �ٲ۴�.
				int decreaseMin = (currentTime.tv_sec - m_PayPlayStartTime.tv_sec)/60;

				// �ٽ� 1�ð��� ��ٷ���.
				if (decreaseMin > 0)
				{
					m_PayPlayStartTime.tv_sec = currentTime.tv_sec;
			
					switch (m_PayPlayType)
					{
						case PAY_PLAY_TYPE_PERSON :
							// DB���� ����� �ð��� 1�ð� ���ش�.
							//m_PayPlayAvailableHours -= 60;

							// DB�� �����ؾ��Ѵ�.
							decreasePayPlayTime(playerID, decreaseMin);//MINUTE_PAY_TIME_DECREASE);
						break;

						case PAY_PLAY_TYPE_PCROOM :
							// DB���� ���ӹ� �ð��� 1�ð� ���ش�.
							//m_PayPlayAvailableHours -= 60;

							// �������̼� �� �� �����Ƿ�.. 
							// �ٽ� DB���� ���� �ð��� �о�´�.
							decreasePayPlayTimePCRoom(decreaseMin);//MINUTE_PAY_TIME_DECREASE);
						break;

						default : break;
					}
				}

				if (m_PayPlayAvailableHours <= 0)
				{
					//throw ProtocolException("���ð��� �ٵƴ�.");
					m_PayPlayStartTime.tv_sec = 0;
					m_bPremiumPlay = false;
					return false;
				}
			}
		}
		break;

		default : break;
	}

	return true;

	__END_CATCH
}

//---------------------------------------------------------------------------
// login Pay PlayPCRoom IP
//---------------------------------------------------------------------------
// ip�� PCRoomIPInfo�� �ִٸ� �� ID�� ���� PCRoom�� PCRoomInfo���� ã�Ƽ�
// �� ������ �о���δ�.
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlayPCRoom(const string& ip, const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	//Statement* pStmt = NULL;
	//cout << "[loginPayPlayPCRoom] from = " << ip.c_str() << ", " << playerID.c_str() << endl;

	BEGIN_DB
	{
		try {
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		try {
			pResult = pStmt->executeQuery( 
				"SELECT r.ID, r.PayType, r.PayStartDate, r.PayPlayDate, r.PayPlayHours, r.PayPlayFlag, r.UserLimit, r.UserMax FROM PCRoomInfo r, PCRoomIPInfo p WHERE p.IP='%s' AND p.ID=r.ID",
					ip.c_str());
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		if (pResult!=NULL && pResult->next())
		{
			uint i = 0;

			setPCRoomID( pResult->getInt(++i) );
			setPayType( (PayType)pResult->getInt(++i) );
			setPayStartAvailableDateTime( pResult->getString(++i) );
			setPayPlayAvailableDateTime( pResult->getString(++i) );
			setPayPlayAvailableHours( pResult->getInt(++i) );
			setPayPlayFlag( pResult->getInt(++i) );
			m_UserLimit 	= pResult->getInt(++i);
			m_UserMax 		= pResult->getInt(++i);

			// �̻��� ������ ���� �ڵ�
			if ( m_PayType == PAY_TYPE_POST )
			{
				VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

				// ���ѵ� ��¥ ���ĸ� ���� �ȵǾ� �ϹǷ�
				if ( currentDateTime <= m_PayPlayAvailableDateTime )
				{
					setPayPlayType( PAY_PLAY_TYPE_PCROOM );
					m_bPCRoomPlay = true;
					return true;
				}

				return false;
			}

			//m_UserMax = max((unsigned int)5, m_UserMax);
			//m_UserMax = min((unsigned int)12, m_UserMax);
			m_UserMax = 15;	// �� �׹� �ִ� 15��

			pResult = pStmt->executeQuery(
				"SELECT count(*) from PCRoomUserInfo WHERE ID=%d", m_PCRoomID );

			if (pResult->next())
			{
				uint users = pResult->getInt(1);

				setPayPlayType( PAY_PLAY_TYPE_PCROOM );
				bool bAvailable = checkPayPlayAvailable();

				//
				// [PC�� ����ڼ� ����]
				//
				// ������ : UserLimit �Ѿ�� �ȵȴ�.
				// ������ : UserMax �Ѿ�� �ȵȴ� <-- ��� ū �ǹ̴� ����. 
				//
				if (m_PayType==PAY_TYPE_PERIOD && users >= m_UserLimit
					|| m_PayType==PAY_TYPE_TIME && users >= m_UserMax)
				{
					//cout << "[PayPCRoom] User Limit Exceed!" << endl;
					SAFE_DELETE(pStmt);

					return false;
				}

				// ��밡���ϴٸ�..
				if (bAvailable)
				{
					// �ϴ� ����ڸ� �߰��غ��µ�..
					try {
						pStmt->executeQuery(
							"INSERT IGNORE INTO PCRoomUserInfo(ID, PlayerID) VALUES(%d, '%s')",
							m_PCRoomID, playerID.c_str());
					} catch (SQLQueryException& se) {
						filelog("paySystem.txt", "%s", se.toString().c_str());
						// �׳� �Ѿ��
					}

					// �߰��� ���� ����� ���ڸ� Ȯ���غ���..
					pResult = pStmt->executeQuery(
						"SELECT count(*) from PCRoomUserInfo WHERE ID=%d", m_PCRoomID );
					
					if (pResult->next())
					{
						users = pResult->getInt(1);

						// PC�� ����ڼ� ������ �Ѿ��...
						if (m_PayType==PAY_TYPE_PERIOD && users >= m_UserLimit
							|| m_PayType==PAY_TYPE_TIME && users >= m_UserMax)
						{
							// �߰��ߴ��� �ٽ� �����..
							pStmt->executeQuery(
								"DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
									playerID.c_str());

							//cout << "[PayPCRoom] User Limit Exceed2!" << endl;

							// ��� �Ұ�..
							SAFE_DELETE(pStmt);

							return false;
						}
						else
						{
							// �������� ���
							SAFE_DELETE(pStmt);

							m_bPCRoomPlay = true;

							return true;
						}
					}
				}
			}
		}

		SAFE_DELETE(pStmt);

	} catch(SQLQueryException& sqe) { 
		SAFE_DELETE(pStmt);

		filelog("paySystem.txt", "%s", sqe.toString().c_str());
		throw;
	}

	return false;

	__END_CATCH
}

//---------------------------------------------------------------------------
// logout Pay PlayPCRoomIP
//---------------------------------------------------------------------------
void PaySystem::logoutPayPlayPCRoom(const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	if (m_PayPlayType==PAY_PLAY_TYPE_PCROOM)
	{
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

			// �߰��ߴ��� �ٽ� �����..
			pStmt->executeQuery( "DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
											playerID.c_str());

			SAFE_DELETE(pStmt);
		//} END_DB(pStmt);
		} catch(SQLQueryException& sqe) { 
			SAFE_DELETE(pStmt);
			filelog("paySystem.txt", "%s", sqe.toString().c_str());
			throw;
		}

	
	}

	__END_CATCH
}


//---------------------------------------------------------------------------
// login PayPlay
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlay(PayType payType, 
							const string& payPlayDate, int payPlayHours, uint payPlayFlag,
							const string& ip, const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	// ���� logout�� �� ���°� �ƴϸ�..
	if (m_PayPlayStartTime.tv_sec != 0)
	{
		return true;
	}

	m_PayPlayStartTime.tv_sec = 0;

	/*
	cout << "[PaySystem::loginPayPlay] "
		<< "PlayerID = " << playerID.c_str() << ", "
		<< "PayType = " << (int)payType << endl
		<< "payPlayDate = " << payPlayDate.c_str() << endl
		<< "payPlayHours = " << (int)payPlayHours << endl
		<< "payPlayFlag = " << (int)payPlayFlag << endl;
	*/

//	if ( g_pConfig->getPropertyInt( "IsNetMarble" ) )
//	{
//		payType = PAY_TYPE_FREE;
//	}

	// ���� by sigi. 2002.5.31
	// FREE, PERIOD, TIME, PART
	setPayType(payType);

	//--------------------------------------------------
	// ���� ����� ���ü�迡 ���� üũ
	//--------------------------------------------------
	if (payType!=PAY_TYPE_FREE)
	{
		setPayPlayType( PAY_PLAY_TYPE_PERSON );

		setPayPlayAvailableDateTime( payPlayDate );
		setPayPlayAvailableHours( payPlayHours );
		setPayPlayFlag( payPlayFlag );

		if ( !checkPayPlayAvailable() || m_PayType == PAY_TYPE_TIME )
		{
			// ���ӹ� ���� üũ
			if ( !loginPayPlayPCRoom(ip, playerID) )
			{
				// loginPayPlayPCRoom���� ���� �ٲ�Ƿ�.. -_-;
				// ���� ����� ���� ����
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayType( payType );
				setPayPlayAvailableDateTime( payPlayDate );
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );

				// ���� ����� üũ
				if (!checkPayPlayAvailable())
				{
					return false;
				}
			}
			else
			{
				// ������ ���ο������ü�� ������ �о�� �ϹǷ�..
				m_bSetPersonValue = false;
			}
		}
		// ���� ���� ����ڵ� PC �� ���ʽ��� ��������ֱ� ���ؼ�
		else if ( m_PayType == PAY_TYPE_PERIOD )
		{
			// PC �� �α��غ��� �Ǹ� -_-;;
			if ( loginPayPlayPCRoom(ip, playerID) )
			{
				// PC �� �α� �ƿ� �ϰ�
				logoutPayPlayPCRoom( playerID );
				// �� �ٽ� ������� �����ֱ�
				setPayType(payType);
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayPlayAvailableDateTime( payPlayDate );
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );
			}
		}
	}

	__END_CATCH

	getCurrentTime(m_PayPlayStartTime);

	// PayType�� �����Ѵ�.
	checkPayPlayAvailable();
	m_bPremiumPlay = true;

	return true;
}

//---------------------------------------------------------------------------
// login PayPlay
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlay(const string& ip, const string& playerID)
	throw (Error)
{

	Statement* pStmt = NULL;

	__BEGIN_TRY

	// ���� logout�� �� ���°� �ƴϸ�..
	if (m_PayPlayStartTime.tv_sec != 0)
	{
		return true;
	}

	m_PayPlayStartTime.tv_sec = 0;


	if (!m_bSetPersonValue)
	{

		BEGIN_DB
		{
			//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

			Result* pResult = pStmt->executeQuery( "SELECT PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID='%s'", playerID.c_str());

			if (pResult->getRowCount() == 0)
			{
				SAFE_DELETE(pStmt);

				//cout << "No PlayerID" << endl;
				return false;
			}

			pResult->next();

			setPayType( (PayType)pResult->getInt(1) );

			setPayPlayAvailableDateTime( pResult->getString(2) );
			setPayPlayAvailableHours( pResult->getInt(3) );
			setPayPlayFlag( pResult->getInt(4) );

			setFamilyPayPlayAvailableDateTime( pResult->getString(5) );

			SAFE_DELETE(pStmt);

		//} END_DB(pStmt)
		} catch(SQLQueryException& sqe) { 

			SAFE_DELETE(pStmt);

			filelog("paySystem.txt", "%s", sqe.toString().c_str());
			throw;
		}


	}

	/*
	cout << "[PaySystem::loginPayPlay] "
		<< "PlayerID = " << playerID.c_str() << ", "
		<< "PayType = " << (int)m_PayType << endl
		<< "payPlayDate = " << m_PayPlayAvailableDateTime.toString() << endl
		<< "payPlayHours = " << (int)m_PayPlayAvailableHours << endl
		<< "payPlayFlag = " << (int)m_PayPlayFlag << endl;
	*/

//	if ( g_pConfig->getPropertyInt( "IsNetMarble" ) )
//	{
//		setPayType( PAY_TYPE_FREE );
//	}

	// ���� by sigi. 2002.5.31
	// FREE, PERIOD, TIME, PART

	//--------------------------------------------------
	// ���� ����� ���ü�迡 ���� üũ
	//--------------------------------------------------
	if (m_PayType!=PAY_TYPE_FREE)
	{
		// ���� ������ ��������� ���� üũ�Ѵ�.
		setPayPlayType( PAY_PLAY_TYPE_PERSON );
		if (!checkPayPlayAvailable() || m_PayType != PAY_TYPE_PERIOD)
		{
			// loginPayPlayPCRoom���� ���� �ٲ�Ƿ�.. -_-;
			PayType 	payType 	= m_PayType;
			VSDateTime 	payPlayDate = m_PayPlayAvailableDateTime;
			int 		payPlayHours = m_PayPlayAvailableHours;
			uint 		payPlayFlag = m_PayPlayFlag;

			// ���ӹ� ���� üũ
			if (!loginPayPlayPCRoom(ip, playerID))
			{
				// ���� ����� ���� ����
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayType( payType );
				m_PayPlayAvailableDateTime = payPlayDate;
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );

				// ���� ����� üũ
				if (!checkPayPlayAvailable())
				{
					//cout << "No PayPlay" << endl;

					return false;
				}
			}
			else
			{
				// ������ ���ο������ü�� ������ �о�� �ϹǷ�..
				m_bSetPersonValue = false;
			}
		}
		// ���� ���� ����ڵ� PC �� ���ʽ��� ��������ֱ� ���ؼ�
		else if ( m_PayType == PAY_TYPE_PERIOD )
		{
			m_bPCRoomPlay = isPlayInPayPCRoom( ip, playerID );
		}
	}

	__END_CATCH

	getCurrentTime(m_PayPlayStartTime);

	// PayType�� �����Ѵ�.
	checkPayPlayAvailable();

	m_bPremiumPlay = true;

	//cout << "PayPlay Available : " << m_PayPlayAvailableDateTime.toString() << ", " << (int)m_PayPlayAvailableHours << endl;

	return true;
}


//---------------------------------------------------------------------------
// logout PayPlay
//---------------------------------------------------------------------------
void PaySystem::logoutPayPlay(const string& playerID, bool bClear, bool bDecreaseTime)
	throw (Error)
{
	__BEGIN_TRY

	// �ð��� �� �ż� ©���� ����� ó���� �� ��
	// m_PayPlayStartTime.tv_sec = 0 ���� �����س��� �����̴�.

	//if (m_PayPlayStartTime.tv_sec == 0)
	//	return;

	if (m_PayPlayType==PAY_PLAY_TYPE_PCROOM)
	{
		logoutPayPlayPCRoom(playerID);

		Timeval currentTime;
		getCurrentTime(currentTime);

		if (bDecreaseTime && m_PayType==PAY_TYPE_TIME)
		{

			int usedMin = (currentTime.tv_sec-m_PayPlayStartTime.tv_sec)/60;
			//usedMin = max(1, usedMin);

			if (usedMin > 0)
			{
				decreasePayPlayTimePCRoom(usedMin);
			}
		}
		else if (bDecreaseTime && m_PayType==PAY_TYPE_POST)
		{
			int usedMin = (currentTime.tv_sec-m_PayPlayStartTime.tv_sec)/60;

			if (usedMin > 0)
			{
				increasePayPlayTimePCRoom(usedMin);
			}
		}
	}
	else if (m_PayPlayType==PAY_PLAY_TYPE_PERSON)
	{
		if (bClear)
		{
			// ��� Pay������ �����ϰ� �������ڷ� �ٲ۴�. by sigi. 2002.11.18
			clearPayPlayDateTime(playerID);
		}
		else if (bDecreaseTime 
				&& m_PayType==PAY_TYPE_TIME
				&& m_PayPlayStartTime.tv_sec!=0)
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			int usedMin = (currentTime.tv_sec-m_PayPlayStartTime.tv_sec)/60;
			//usedMin = max(1, usedMin);

			if (usedMin > 0)
			{
				decreasePayPlayTime(playerID, usedMin);
			}
		}
	}

	m_PayPlayStartTime.tv_sec = 0;
	m_bPremiumPlay = false;

	__END_CATCH
}

//---------------------------------------------------------------------------
// clear PayPlayTime 
//---------------------------------------------------------------------------
// DB���� ���ð��� �����Ѵ�.
void PaySystem::clearPayPlayDateTime(const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours = 0;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pStmt->executeQuery( 
				"UPDATE Player SET PayPlayHours=0, PayPlayDate='2002-11-18 00:00:00' WHERE PlayerID='%s'",
							playerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		
	__END_CATCH
}

//---------------------------------------------------------------------------
// decrease PayPlayTime 
//---------------------------------------------------------------------------
// DB���� ���ð��� ���ش�. 
void PaySystem::decreasePayPlayTime(const string& playerID, uint mm)
	throw (Error)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours -= mm;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pStmt->executeQuery( 
				"UPDATE Player SET PayPlayHours=PayPlayHours-%d WHERE PlayerID='%s'",
							mm, playerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		
	__END_CATCH
}

//---------------------------------------------------------------------------
// decrease PayPlayTime PCRoom
//---------------------------------------------------------------------------
void PaySystem::decreasePayPlayTimePCRoom(uint mm)
	throw (Error)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours -= mm;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pStmt->executeQuery( 
			"UPDATE PCRoomInfo SET PayPlayHours=PayPlayHours-%d WHERE ID=%d",
							mm, m_PCRoomID);

		Result* pResult = pStmt->executeQuery(
			"SELECT PayPlayHours FROM PCRoomInfo WHERE ID=%d", m_PCRoomID);
							
		if (pResult->next())
		{
			m_PayPlayAvailableHours = pResult->getInt(1);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		

	__END_CATCH
}

//---------------------------------------------------------------------------
// increase PayPlayTime PCRoom
//---------------------------------------------------------------------------
void PaySystem::increasePayPlayTimePCRoom(uint mm)
	throw (Error)
{
	__BEGIN_TRY

	VSDate vsDate = VSDate::currentDate();

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pResult = pStmt->executeQuery( 
			"SELECT PayPlayMinute FROM PCRoomPayList WHERE PCRoomID=%d AND Year=%d AND Month=%d" ,
							m_PCRoomID, vsDate.year(), vsDate.month() );
		
		if ( pResult->next() )
		{
			pStmt->executeQuery( 
				"UPDATE PCRoomPayList SET PayPlayMinute=PayPlayMinute+%d WHERE PCRoomID=%d AND Year=%d AND Month=%d" ,
								mm, m_PCRoomID, vsDate.year(), vsDate.month() );
		}
		else
		{
			pStmt->executeQuery( 
				"INSERT INTO PCRoomPayList (PCRoomID, Year, Month, PayPlayMinute) VALUES (%d, %d, %d, %d)",
								m_PCRoomID, vsDate.year(), vsDate.month(), mm );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		

	__END_CATCH
}

bool PaySystem::isPayPlayingPeriodPersonal(const string& PlayerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	bool isPayPlay = false;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		Result* pResult = pStmt->executeQuery( "
			SELECT PayType=0 or PayPlayDate > now() FROM Player WHERE PlayerID='%s'",
			PlayerID.c_str());

		if (pResult->next())
		{
			isPayPlay = pResult->getInt(1)==1;
		}

		SAFE_DELETE(pStmt);

	//} END_DB(pStmt)
	} catch(SQLQueryException& sqe) { 

		SAFE_DELETE(pStmt);

		filelog("paySystem.txt", "%s", sqe.toString().c_str());
		throw;
	}

	return isPayPlay;

	__END_CATCH
}

//---------------------------------------------------------------------------
// ip�� PCRoomIPInfo�� �ִٸ� �� ID�� ���� PCRoom�� PCRoomInfo���� ã�Ƽ�
// �� ������ �о���δ�.
// ���� ������� �Ǿ��濡�� �÷��� �ϰ� �ִ��� Ȯ���ϴ� �Լ�
// ���� �������� ��� loginPayPlayPCRoom() �� ȣ������ �ʱ� ������ ���� Ȯ���� �Ѵ�.
//---------------------------------------------------------------------------
bool PaySystem::isPlayInPayPCRoom(const string& ip, const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		try {
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		try {
			pResult = pStmt->executeQuery( 
				"SELECT r.ID, r.PayType, r.PayStartDate, r.PayPlayDate, r.PayPlayHours FROM PCRoomInfo r, PCRoomIPInfo p WHERE p.IP='%s' AND p.ID=r.ID",
					ip.c_str());
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		if (pResult!=NULL && pResult->next())
		{
			uint i = 0;

			ObjectID_t	pcRoomID = (ObjectID_t)pResult->getInt(++i);
			PayType		payType = (PayType)pResult->getInt(++i);
			VSDateTime	payStartAvailableDateTime( pResult->getString(++i) );
			VSDateTime	payPlayAvailableDateTime( pResult->getString(++i) );
			int			payPlayAvailableHours = pResult->getInt(++i);

			VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

			// �̻��� ������ ���� �ڵ�
			if ( payType == PAY_TYPE_POST )
			{
				VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

				// ���ѵ� ��¥ ���ĸ� ���� �ȵǾ� �ϹǷ�
				if ( currentDateTime <= payPlayAvailableDateTime )
					return true;

				return false;
			}

			// ���� ��� ������ PC ������ Ȯ���Ѵ�.
			bool bAvailable = ( payType == PAY_TYPE_FREE )
								|| ( ( currentDateTime >= payStartAvailableDateTime ) 
									&& ( currentDateTime <= payPlayAvailableDateTime ) )
								|| ( payPlayAvailableHours > 0 );

			// ���� ��� ������ PC ���ϰ�� PC �� ID �� �����Ѵ�.
			if ( bAvailable )
				m_PCRoomID = pcRoomID;

			return bAvailable;
		}

		SAFE_DELETE(pStmt);

	} catch(SQLQueryException& sqe) { 
		SAFE_DELETE(pStmt);

		filelog("paySystem.txt", "%s", sqe.toString().c_str());
		throw;
	}

	return false;

	__END_CATCH
}

