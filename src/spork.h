// Copyright (c) 2017 The STRAKS developers
// Copyright (c) 2017-2018 The Methuselah Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SPORK_H
#define SPORK_H

//#include "bignum.h"
#include "sync.h"
#include "net.h"
#include "key.h"
#include "hash.h"
//#include "core.h"
#include "util.h"
#include "script/script.h"
#include "base58.h"
#include "net_processing.h"

using namespace std;
using namespace boost;

// Used for displaying of sporks.
// TODO: Updated when sporks are added.
#define SPORK_START 10000
#define SPORK_END   10008

// Don't ever reuse these IDs for other sporks
#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT                 10000
#define SPORK_2_INSTANTX                                        10001
#define SPORK_3_INSTANTX_BLOCK_FILTERING                        10002
#define SPORK_4_NOTUSED                                         10003
#define SPORK_5_MAX_VALUE                                       10004
#define SPORK_6_NOTUSED                                         10005
#define SPORK_7_MASTERNODE_SCANNING                             10006
#define SPORK_8_LOCKDOWN                                        10007
#define SPORK_9_ACTIVE_PROTOCOL                                 10008

#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT         1523923283   // [methuse] TODO: update
#define SPORK_2_INSTANTX_DEFAULT                                1523664107   // [methuse] TODO: update
#define SPORK_3_INSTANTX_BLOCK_FILTERING_DEFAULT                1523664107   // [methuse] TODO: update
#define SPORK_5_MAX_VALUE_DEFAULT                               10000        // 10000 SAP
#define SPORK_7_MASTERNODE_SCANNING_DEFAULT                     1523664107   // [methuse] TODO: update
#define SPORK_8_LOCKDOWN_DEFAULT                                4070908800   // [methuse] FIX: lockdown, 01/01/2099
#define SPORK_9_ACTIVE_PROTOCOL_DEFAULT                         4070908800   // [methuse] FIX: active protocol version

class CSporkMessage;
class CSporkManager;
class CProcessSpork;

//#include "bignum.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "protocol.h"
#include "sync.h"
#include "utilstrencodings.h"
//#include "darksend.h"
#include "validation.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

extern std::map<uint256, CSporkMessage> mapSporks;
extern std::map<int, CSporkMessage> mapSporksActive;
extern CSporkManager sporkManager;
extern CProcessSpork spMessage;

//void ProcessSpork(CNode* pfrom, const string& strCommand, CDataStream& vRecv, CConnman& connman);
int GetSporkValue(int nSporkID);
bool IsSporkActive(int nSporkID);
void ExecuteSpork(int nSporkID, int nValue);

void ProcessSpork(CNode* pfrom, const string& strCommand, CDataStream& vRecv, CConnman& connman);

//
// Spork Class
// Keeps track of all of the network spork settings
//
class CSporkMessage
{
public:
    std::vector<unsigned char> vchSig;
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;
    
    uint256 GetHash()
	{ 
		return lyra2re2_hash(BEGIN(nSporkID), END(nTimeSigned));
	}

    ADD_SERIALIZE_METHODS;
    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
	{
    READWRITE(nSporkID);
    READWRITE(nValue);
    READWRITE(nTimeSigned);
    READWRITE(vchSig);
    }
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;

    std::string strMasterPrivKey;
    std::string strTestPubKey;
    std::string strMainPubKey;

public:
    CSporkManager() {
        strMainPubKey = "04352c3399df0d8ec510f66aef12839689e1f7cfb2794c05209d2ed7723bd1be5a4e61540606343d1dffb6b6ae5d567a7ecf3c1d6854cb144fd06f06d170a41fad"; 
        strTestPubKey = "0470ad8caf90ff3f41fb5d1ce91db4b701a20259c9d5723d9a63ebc735f460f2938aebfdcfa2b035ca7edf095c9d3d66df17ed0a840de40bc80402d2e9eafda4f5";  
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg, CConnman& connman);
	void RelayUpdateSpork(CSporkMessage& msg);
};

#endif
