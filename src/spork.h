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

// Don't ever reuse these IDs for other sporks
#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT               10000
#define SPORK_2_INSTANTX                                      10001
#define SPORK_3_INSTANTX_BLOCK_FILTERING                      10002
#define SPORK_4_NOTUSED                                       10003
#define SPORK_5_MAX_VALUE                                     10004
#define SPORK_6_NOTUSED                                       10005
#define SPORK_7_MASTERNODE_SCANNING                           10006

#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT       1523923283   // [methuse] TODO: update
#define SPORK_2_INSTANTX_DEFAULT                              1523664107   // [methuse] TODO: update
#define SPORK_3_INSTANTX_BLOCK_FILTERING_DEFAULT              1523664107   // [methuse] TODO: update
#define SPORK_5_MAX_VALUE_DEFAULT                             10000        // 10000 SAP
#define SPORK_7_MASTERNODE_SCANNING_DEFAULT                   1523664107   // [methuse] TODO: update

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
        strMainPubKey = "04e6af2d104e5a082806154edf96310de550766b32150c8c25fff172fe4d17db3ceb72f2b055d42298c9a8c1fe2497fb7af7bf1ff10e68cbf7bf571e225dd8b83d"; 
        strTestPubKey = "04180725b0bd97fbb42355cfa4585b549077ec30712961c1efc0d3595bb4a4bf80153dbf451079f93f0e4c5139bcac144cd99b967e340a6b10ccdc1045639fb62a";  
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
