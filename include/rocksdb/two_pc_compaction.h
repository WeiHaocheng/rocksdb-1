#ifndef STORAGE_ROCKSDB_TwoPC_COMPACTION_OPTIONS_H
#define STORAGE_ROCKSDB_TwoPC_COMPACTION_OPTIONS_H

#include <stdint.h>
#include <climits>
#include <vector>

namespace rocksdb {

class CompactionOptionsTwoPC {
 public:

  unsigned int start_level;
  unsigned int merge_threshold;

  // Default set of parameters
  CompactionOptionsTwoPC()
      : start_level(1),
        merge_threshold(5) {}
};

}  // namespace rocksdb

#endif  // STORAGE_ROCKSDB_TwoPC_COMPACTION_OPTIONS_H