//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowGuildDialog.h
// Written By  : 
// Description :
// Creature�� �־��� ��縦 ���Ѵ�. �� ���� ũ��ó�� �Ӹ� ���� ��ǳ������
// ��µȴ�.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_GUILD_DIALOG_H__
#define __ACTION_SHOW_GUILD_DIALOG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

typedef BYTE GuildDialog_t;
const int szGuildDialog = sizeof(GuildDialog_t);


//////////////////////////////////////////////////////////////////////////////
// class ActionShowGuildDialog;
//////////////////////////////////////////////////////////////////////////////

class ActionShowGuildDialog : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SHOW_GUILD_DIALOG; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

	enum GUILDDIALOG
	{
		GUILD_DIALOG_REGIST = 0,		// ��� ��� â
		GUILD_DIALOG_WAIT_LIST,			// ��� ��� ��� ����Ʈ
		GUILD_DIALOG_LIST,				// ��� ����Ʈ
		GUILD_DIALOG_QUIT,				// ��� Ż�� â

		GUILD_DIALOG_MAX
	};

private:
	GuildDialog_t m_Type;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionShowGuildDialogFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowGuildDialogFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_SHOW_GUILD_DIALOG; }
	virtual string getActionName() const throw() { return "ShowGuildDialog"; }
    virtual Action* createAction() const throw() { return new ActionShowGuildDialog(); }
};

#endif
