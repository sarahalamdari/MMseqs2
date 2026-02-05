//
// Created by lars on 08.06.15.
//

#ifndef MMSEQS_CLUSTERINGALGORITHMS_H
#define MMSEQS_CLUSTERINGALGORITHMS_H

#include <set>
#include <list>
#include <vector>
#include <unordered_map>

#include "DBReader.h"
#include "Types.h"

class ClusteringAlgorithms {
public:
    ClusteringAlgorithms(DBReader<unsigned int>* seqDbr, DBReader<unsigned int>* alnDbr, int threads,int scoretype, int maxiterations, seqid_t *keyToSet, size_t *sourceOffsets, seqid_t **sourceLookupTable, seqid_t *sourceList, unsigned int sourceLen, bool needSET);
    ~ClusteringAlgorithms();
    std::pair<seqid_t, seqid_t> * execute(int mode);
private:
    DBReader<unsigned int>* seqDbr;

    DBReader<unsigned int>* alnDbr;

    bool needSET;
    int threads;
    int scoretype;
//datastructures
    unsigned int maxClustersize;
    unsigned int dbSize;
    int * clustersizes;
    unsigned int* sorted_clustersizes;
    unsigned int* clusterid_to_arrayposition;
    unsigned int* borders_of_set;
    seqid_t* keyToSet;
    size_t* sourceOffsets;
    seqid_t** sourceLookupTable;
    seqid_t* sourceList;
    unsigned int sourceLen;

//methods

    void initClustersizes();

    void removeClustersize(unsigned int clusterid);

    void decreaseClustersize(unsigned int clusterid);
//for connected component
    int maxiterations;


    void setCover(seqid_t **elementLookup, unsigned short ** elementScoreLookupTable,
                  seqid_t *assignedcluster, short *bestscore, size_t *offsets);

    void greedyIncremental(seqid_t **elementLookupTable, size_t *elementOffsets,
                           size_t n, seqid_t *assignedcluster) ;


    void greedyIncrementalLowMem(seqid_t *assignedcluster) ;


    void readInClusterData(seqid_t **elementLookupTable, seqid_t *&elements,
                           unsigned short **scoreLookupTable, unsigned short *&scores,
                           size_t *elementOffsets, size_t totalElementCount)  ;

};



#endif //MMSEQS_CLUSTERINGALGORITHMS_H
