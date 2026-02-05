//
// Created by lars on 10.06.15.
//

#ifndef MMSEQS_ALIGNMENTSYMMETRY_H
#define MMSEQS_ALIGNMENTSYMMETRY_H
#include <set>
#include <list>
#include <Debug.h>
#include <Util.h>

#include "DBReader.h"
#include "Types.h"

class AlignmentSymmetry {
public:
    static void readInData(DBReader<unsigned int>*pReader, DBReader<unsigned int>*pDBReader, seqid_t **pInt,unsigned short**elementScoreTable, int scoretype, size_t *offsets);
    static void readInDataSet(DBReader<unsigned int>*alnDbr, DBReader<unsigned int>*seqDbr, seqid_t **elementLookupTable, unsigned short **elementScoreTable, int scoretype, size_t *offsets, size_t *sourceOffsets, seqid_t **sourceLookupTable, seqid_t *keyToSet, bool isfirst);
    template<typename T>
    static void computeOffsetFromCounts(T* elementSizes, size_t dbSize)  {
        size_t prevElementLength = elementSizes[0];
        elementSizes[0] = 0;
        for(size_t i = 0; i < dbSize; i++) {
            const size_t currElementLength = elementSizes[i + 1];
            elementSizes[i + 1] = elementSizes[i] + prevElementLength;
            prevElementLength = currElementLength;
        }
    }
    static size_t findMissingLinks(seqid_t **elementLookupTable, size_t *offsetTable, size_t dbSize, int threads);
    static void addMissingLinks(seqid_t **elementLookupTable, size_t *offsetTable, size_t * newOffset, size_t dbSize,unsigned short**elementScoreTable);
    static void sortElements(seqid_t **elementLookupTable, size_t *offsets, size_t dbSize);

    template <typename T>
    static void setupPointers(T *elements, T **elementLookupTable, size_t *elementOffset,
                                 unsigned int dbSize, size_t totalElementCount) {
        for(size_t i = 0; i < dbSize; i++) {
            if(totalElementCount < elementOffset[i]){
                Debug(Debug::ERROR) << "Error in setupPointers. totalElementCount "
                                    << "(" << totalElementCount << ") < elementOffset["<<i<<"] (" << elementOffset[i] << ")\n";
                EXIT(EXIT_FAILURE);
            }
            elementLookupTable[i] = elements + elementOffset[i];
        }
    }
};
#endif //MMSEQS_ALIGNMENTSYMMETRY_H
