#include "ItemHeroOptionManager.h"
#include "DB.h"
#include "Assert.h"

void ItemHeroOptionManager::load() 
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT Grade, Ratio, GambleRatio, BeadRatio, GroupID FROM ItemHeroRatioInfo" );

		//Assert( pResult->getRowCount() == 620 );
		//m_HeroOptionGambleRatios.reserve(620);
		//m_HeroOptionBeadRatios.reserve(620);
		//m_HeroOptionRatios.reserve(620);

		while ( pResult->next() )
		{
			int Grade = pResult->getInt(1);
			int Ratio = pResult->getInt(2);
			int GambleRatio = pResult->getInt(3);
			int BeadRatio = pResult->getInt(4);
			int Group = pResult->getInt(5);
			//m_HeroOptionRatios[Grade-1][Group] = {{0,},{0,}};
			m_HeroOptionRatios[Grade-1][Group] = Ratio;
			m_HeroOptionGambleRatios[Grade-1][Group] = GambleRatio;
			m_HeroOptionBeadRatios[Grade-1][Group] = BeadRatio;

			cout << Grade << "�� : " << Ratio << ", " << GambleRatio << ", " << BeadRatio << endl;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

int ItemHeroOptionManager::getRandomHeroOptionAttr(int Group) const
{
	int i=0;
	int value = rand()%100000;
	int size1 = sizeof(m_HeroOptionRatios) / sizeof(m_HeroOptionRatios[0]) ;            //�� ���� = (�迭�� �� ũ�� * �� ũ��) 
	int size2 = sizeof(m_HeroOptionRatios[0]) / sizeof(m_HeroOptionRatios[0][0]);    //�� ���� = (�� ũ�� * �� ũ��=�ڷ��� ũ��)
	
	cout << size1 << "/" << size2 << endl;
	if(Group == 7 || Group == 8 || Group == 23){size1 = 25;}
	if(Group >= 32){size1 = 10;}
	for ( ; i<size1; ++i )
	{
		if(m_HeroOptionRatios[i][Group] != 0){
		value -= m_HeroOptionRatios[i][Group];
		cout << " Ȯ�� : " << value <<" / " << m_HeroOptionRatios[i][Group] << " ���� ũ�� " << endl;
		if ( value < 0 ) return i+1;
		}
		if(m_HeroOptionRatios[i][Group] == 0){
		return 1;
		}
	}

	return i;
}

int ItemHeroOptionManager::getRandomHeroOption() const
{
	int value = Random(0,19);

	if(value == 5){value = 20;} // 5�� ���� ũ��Ƽ�÷� ��ü
	if(value == 6){value = 23;} // 5�� ���� ��ɷ� ��ü
	if(value == 13){value = 32;} // 5�� ���� ��ɷ� ��ü
	if(value == 14){value = 33;} // 5�� ���� ��ɷ� ��ü
	if(value == 15){value = 36;} // 5�� ���� ��ɷ� ��ü
	if(value == 16){value = 37;} // 5�� ���� ��ɷ� ��ü
	if(value == 17){value = Random(0,4);} // 5�� ���� ��ɷ� ��ü
	if(value == 18){value = Random(0,4);} // 5�� ���� ��ɷ� ��ü

	return value;
}

int ItemHeroOptionManager::getRandomBeadHeroOption(int Group) const
{
	int value = rand()%100000;
	int i=0;

	for ( ; i<10; ++i )
	{
		value -= m_HeroOptionBeadRatios[i][Group];
		if ( value < 0 ) return i+1;
	}

	return i;
}

int ItemHeroOptionManager::getClassHeroOptionSize(int Group) const
{
	Statement* pStmt = NULL;
	int Grade;
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT Count(*)  FROM ItemHeroRatioInfo where GroupID = %d", Group );

		pResult->next();
		Grade = pResult->getInt(1);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return Grade;

}

ItemHeroOptionManager& ItemHeroOptionManager::Instance()
{
	static ItemHeroOptionManager theInstance;
	return theInstance;
}
