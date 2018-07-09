// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2017 The Dash developers
// Copyright (c) 2017 The STRAKS developers
// Copyright (c) 2017-2018 The Methuselah Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include "arith_uint256.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 1522368000 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Bloomberg 2018-04-12: Venezuela Says Government Bodies Must Soon Accept Cryptocurrency";
    const CScript genesisOutputScript = CScript() << ParseHex("04467062e8e67181af11bdd0619193a35e9630818def50e4e9edba21ccf06994c3d749d8a5249af13dd0175a781d7560bef819895db49809e37c481195fdf187a6");
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("00000de5cd174557ab559bb00ec27e1d0a323ea11fa1afd9d76d5e6f552cffb9");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.BIP102HeightDelta = 0;

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 30 * 60; // 30 minutes
        consensus.nPowTargetSpacing = (2 * 60) + 15; // 2.25 minutes

        consensus.fPowD601SwitchHeight = 20; // consensus.DifficultyAdjustmentInterval();

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 1280; // 2 days
        consensus.nMinerConfirmationWindow = 1920; // 3 days

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1496275200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1496275200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        // 3 days from launch, fair chance to buy/accumulate. 1921 blocks
        consensus.MasternodePaymentStartHeight = 1921;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xab;
        pchMessageStart[2] = 0xac;
        pchMessageStart[3] = 0xad;
        nDefaultPort = 7555;
        nPruneAfterHeight = 100000;

        // Time, Nonce,nBits, version, reward
        genesis = CreateGenesisBlock(1523664107, 348809, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("00000de5cd174557ab559bb00ec27e1d0a323ea11fa1afd9d76d5e6f552cffb9"));
        assert(genesis.hashMerkleRoot == uint256S("da1654e2b09b4057fa5504dc2d8f6b5599467601b16e8e2d70d53b7e341f7cb3"));

        vSeeds.push_back(CDNSSeedData("methuselahcoin.io", "seed1.methuselahcoin.io"));
        vSeeds.push_back(CDNSSeedData("methuselahcoin.io", "seed2.methuselahcoin.io"));
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,51); // M
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,66); // T
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,63); // S
        // 4  M   T   S   = EXT_PUBLIC_KEY (ascii)
        // 4  51  66  63  = EXT_PUBLIC_KEY (base58 decimal)
        // 04 33  42  3F  = EXT_PUBLIC_KEY (hex)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x33)(0x42)(0x3F).convert_to_container<std::vector<unsigned char> >();
        // 4  m   t   s   = EXT_PUBLIC_KEY (ascii)
        // 4  110 128 125 = EXT_PUBLIC_KEY (base58 decimal)
        // 04 6E  80  7D  = EXT_PUBLIC_KEY (hex)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x6E)(0x80)(0x7D).convert_to_container<std::vector<unsigned char> >();

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("00000de5cd174557ab559bb00ec27e1d0a323ea11fa1afd9d76d5e6f552cffb9")},
                { 50900, uint256S("0000000000764b9d957d88a6307e7d87f083d102e23f3bd80458c53523631926")}
            }
        };

        // treasury payment adresses 
        vTreasuryRewardAddress = {
            "NONE"
        };

        /**
         * What makes a good checkpoint block?
         * + Is surrounded by blocks with reasonable timestamps
         *   (no blocks before with a timestamp after, none after with
         *    timestamp before)
         * + Contains no strange transactions
         */
        // [1] UNIX timestamp of last known number of transactions
        // [2] total number of transactions between genesis and that timestamp
        //     (the tx=... number in the SetBestChain debug.log lines)
        // [3] estimated number of transactions per second after that timestamp
        chainTxData = ChainTxData{
            1531078381,
            57241,
            1
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";

        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("00000f1e613da300b980001a74d1bdb8f81d69eff992b3522fae1bc76de7fb93");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.BIP102HeightDelta = 0;

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 5; // 5 seconds
        consensus.nPowTargetSpacing = 5; // 5 seconds 

        consensus.fPowD601SwitchHeight = 30;

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 12; // 2 minutes
        consensus.nMinerConfirmationWindow = 18; // 3 minutes

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1496275200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1496275200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        consensus.MasternodePaymentStartHeight = 250;

        pchMessageStart[0] = 0xba;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0xbc;
        pchMessageStart[3] = 0xbd;
        nDefaultPort = 7444;
        nPruneAfterHeight = 1000;

        // Time, Nonce,nBits, version, reward
        genesis = CreateGenesisBlock(1523664117, 1758867, 0x1e0ffff0, 1, 0 * COIN); 
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("00000f1e613da300b980001a74d1bdb8f81d69eff992b3522fae1bc76de7fb93"));
        assert(genesis.hashMerkleRoot == uint256S("da1654e2b09b4057fa5504dc2d8f6b5599467601b16e8e2d70d53b7e341f7cb3"));

        // vSeeds.push_back(CDNSSeedData("methuselahcoin.io", "test-seed1.methuselahcoin.io"));
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
        vFixedSeeds.clear(); // [methuse] TODO: remove
        vSeeds.clear(); // [methuse] TODO: remove

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,110); // m
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,128); // t
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,125); // s
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xA2)(0xAE)(0xC9)(0xA6).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x46)(0x00)(0x2A)(0x10).convert_to_container<std::vector<unsigned char> >();

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("00000f1e613da300b980001a74d1bdb8f81d69eff992b3522fae1bc76de7fb93")}
            }
        };

        vTreasuryRewardAddress = {
            "NONE"
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("00000d79139aa722b495c750c179bc73cce8c375885be19aecd0335b91508b8e");
        consensus.BIP65Height = 0; 
        consensus.BIP66Height = 0; 
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.BIP102HeightDelta = 0;

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 10; // 10 seconds
        consensus.nPowTargetSpacing = 1; // 1 second

        consensus.fPowD601SwitchHeight = 30;

        consensus.fDigishieldDifficultyCalculation = false;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;

        consensus.nRuleChangeActivationThreshold = 5400; 
        consensus.nMinerConfirmationWindow = 7200; 

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1462060800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1496275200;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1496275200; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        consensus.MasternodePaymentStartHeight = 100;

        pchMessageStart[0] = 0xca;
        pchMessageStart[1] = 0xcb;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0xcd;
        nDefaultPort = 7333;
        nPruneAfterHeight = 1000;

        // Time, Nonce,nBits, version, reward
        genesis = CreateGenesisBlock(1523664127, 1617130, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("00000d79139aa722b495c750c179bc73cce8c375885be19aecd0335b91508b8e"));
        assert(genesis.hashMerkleRoot == uint256S("da1654e2b09b4057fa5504dc2d8f6b5599467601b16e8e2d70d53b7e341f7cb3"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("00000d79139aa722b495c750c179bc73cce8c375885be19aecd0335b91508b8e") )
        };

        vTreasuryRewardAddress = {
            "NONE"
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,138); // x
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,138); // x
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,138); // x
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xA2)(0xAE)(0xC9)(0xA6).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x46)(0x00)(0x2A)(0x10).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}


std::string CChainParams::GetTreasuryRewardAddressAtHeight(int nHeight) const {
    size_t i = nHeight % vTreasuryRewardAddress.size();
    return vTreasuryRewardAddress[i];
}

CScript CChainParams::GetTreasuryRewardScriptAtHeight(int nHeight) const {
    CMethuselahAddress address(GetTreasuryRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = boost::get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script; 
}

std::string CChainParams::GetTreasuryRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vTreasuryRewardAddress.size());
    return vTreasuryRewardAddress[i];
}

