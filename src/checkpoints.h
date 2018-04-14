// Copyright (c) 2009-2017 The Bitcoin Core developers 
// Copyright (c) 2017 The Dash developers 
// Copyright (c) 2017 The STRAKS developers
// Copyright (c) 2017-2018 The Methuselah Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef METHUSELAH_CHECKPOINTS_H
#define METHUSELAH_CHECKPOINTS_H

#include "uint256.h"

#include <map>

class CBlockIndex;
struct CCheckpointData;

/**
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints
{

//! Returns last CBlockIndex* in mapBlockIndex that is a checkpoint
CBlockIndex* GetLastCheckpoint(const CCheckpointData& data);

} //namespace Checkpoints

#endif // METHUSELAH_CHECKPOINTS_H
