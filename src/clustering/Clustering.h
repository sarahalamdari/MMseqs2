#ifndef CLUSTERING_H
#define CLUSTERING_H

#include <unordered_map>

#include "DBReader.h"
#include "DBWriter.h"
#include "Types.h"

class Clustering {
public:
    Clustering(const std::string &seqDB, const std::string &seqDBIndex,
               const std::string &alnResultsDB, const std::string &alnResultsDBIndex,
               const std::string &outDB, const std::string &outDBIndex,
               const std::string &weightFileName,
               unsigned int maxIteration, int similarityScoreType, int threads, int compressed, bool needSET);

    void run(int mode);


    ~Clustering();

private:

    void writeData(DBWriter *dbw, const std::pair<seqid_t, seqid_t> * ret, size_t dbSize);

    DBReader<unsigned int> *seqDbr;
    DBReader<unsigned int> *alnDbr;

    bool needSET;
    unsigned int seqnum;
    seqid_t *keyToSet;
    size_t *sourceOffsets;
    seqid_t **sourceLookupTable;
    seqid_t *sourceList;

    //values for affinity clustering
    unsigned int maxIteration;
    int similarityScoreType;

    int threads;
    int compressed;
    std::string outDB;
    std::string outDBIndex;
};

#endif
