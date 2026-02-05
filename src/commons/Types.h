#ifndef MMSEQS_TYPES_H
#define MMSEQS_TYPES_H

#include <cstdint>
#include <limits>

// Sequence ID type - configurable at compile time
// Use -DUSE_64BIT_IDS=ON to enable 64-bit sequence IDs for databases with >4 billion sequences
// Default is 32-bit for memory efficiency

#ifdef USE_64BIT_IDS
    // 64-bit mode: supports up to 2^64 sequences
    typedef uint64_t seqid_t;
    #define SEQID_MAX UINT64_MAX
    #define PRIseqid PRIu64
    #define SEQID_BITS 64
#else
    // 32-bit mode (default): supports up to ~4.3 billion sequences
    typedef uint32_t seqid_t;
    #define SEQID_MAX UINT32_MAX
    #define PRIseqid PRIu32
    #define SEQID_BITS 32
#endif

// Sentinel value for invalid/uninitialized sequence IDs
static constexpr seqid_t INVALID_ID = std::numeric_limits<seqid_t>::max();

// Helper to check if a sequence ID is valid
inline bool isValidSeqId(seqid_t id) {
    return id != INVALID_ID;
}

// Database key type - same as sequence ID type
typedef seqid_t dbkey_t;
#define DBKEY_MAX SEQID_MAX
#define PRIdbkey PRIseqid

#endif // MMSEQS_TYPES_H
