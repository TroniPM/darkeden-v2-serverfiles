//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCAskVariable.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_ASK_VARIABLE_H__
#define __GC_NPC_ASK_VARIABLE_H__

#include <hash_map>
#include "Packet.h"
#include "PacketFactory.h"
#include "ScriptParameter.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskVariable;
// NPC �� ��縦 �ֺ��� PC �鿡�� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////

typedef hash_map<string,ScriptParameter*>		HashMapScriptParameter;
typedef HashMapScriptParameter::iterator		HashMapScriptParameterItor;
typedef HashMapScriptParameter::const_iterator	HashMapScriptParameterConstItor;

class GCNPCAskVariable : public Packet
{
public:
	GCNPCAskVariable() throw();
	virtual ~GCNPCAskVariable() throw();

public:
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID()  { return PACKET_GC_NPC_ASK_VARIABLE; }
	PacketSize_t getPacketSize() ;
	string getPacketName()  { return "GCNPCAskVariable"; }
	string toString() ;

public:
	ObjectID_t getObjectID(void)  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	ScriptID_t getScriptID(void)  { return m_ScriptID; }
	void setScriptID(ScriptID_t id) throw() { m_ScriptID = id; }

	void addScriptParameter( ScriptParameter* pParam ) throw(DuplicatedException);
	void clearScriptParameters() throw();
	HashMapScriptParameter& getScriptParameters() { return m_ScriptParameters; }
	string getValue( const string& name ) const throw(NoSuchElementException);

private:
	ObjectID_t m_ObjectID; // NPC's object id
	ScriptID_t m_ScriptID; // script id
	HashMapScriptParameter m_ScriptParameters; // ��ũ��Ʈ�� ���� �Ķ���͵�
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskVariableFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskVariableFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCNPCAskVariable(); }
	string getPacketName()  { return "GCNPCAskVariable"; }
	PacketID_t getPacketID()  { return Packet::PACKET_GC_NPC_ASK_VARIABLE; }
	PacketSize_t getPacketMaxSize() 
	{
		return szObjectID
			 + szScriptID
			 + szBYTE
			 + ScriptParameter::getMaxSize() * 255;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskVariableHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskVariableHandler 
{
public:
	static void execute(GCNPCAskVariable* pPacket, Player* pPlayer) throw(ProtocolException, Error);
};

#endif
