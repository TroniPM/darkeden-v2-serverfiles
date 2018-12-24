/////////////////////////////////////////////////////////////////////////////
// filename	: MJob.h
// desc		: ���۽��� �����ؼ� �Ŀ�����Ʈ�� �������� �ϳ��� �۾� ����
/////////////////////////////////////////////////////////////////////////////

#ifndef __MJOB_H__
#define __MJOB_H__

class MJob
{
public:
	MJob( const string& userID, const string& name, const string& cellnum )
		: m_UserID(userID), m_Name(name), m_CellNum(cellnum),
		m_PowerPoint(0), m_ErrorCode(0), m_bEnd(false)
	{
	}

public:
	// ����Ʈ ����
	void addPowerPoint( int point ) { m_PowerPoint += point; }

	// get
	int getPowerPoint() const { return m_PowerPoint; }
	const string& getUserID() const { return m_UserID; }
	const string& getName() const { return m_Name; }
	const string& getCellNum() const { return m_CellNum; }

	// get/set errorcode
	int getErrorCode() const { return m_ErrorCode; }
	void setErrorCode( int errorCode ) { m_ErrorCode = errorCode; }

	// get/set end job
	bool isEnd() const { return m_bEnd; }
	void setEnd( bool bEnd = true ) { m_bEnd = bEnd; }

private:
	// ����� ID 
	string m_UserID;

	// ĳ���� ��
	string m_Name;

	// �ڵ��� ��ȣ
	string m_CellNum;

	// ������ ����Ʈ
	int m_PowerPoint;

	// ���� �ڵ�
	int m_ErrorCode;

	// �۾��� ������?
	bool m_bEnd;
};

#endif

