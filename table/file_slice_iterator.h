#pragma once
#include "internal_iterator.h"

namespace rocksdb {
	class FileSliceIterator : public InternalIterator{
		public:
			FileSliceIterator(FileSlice& file_slice, InternalIterator* file_iter, 
				const InternalKeyComparator& internal_comparator);

			~FileSliceIterator();

			virtual bool Valid() const;

			virtual Slice key() const;

			virtual Slice value() const;

			virtual Status status() const;

			virtual void Next();

			virtual void Prev();

			virtual Seek(const Slice& target);

			virtual void SeekToFirst();

			virtual void SeekToLast();
		private:
			const InternalKeyComparator icmp_;
			InternalIterator* file_iter_;
			FileSlice file_slice_;

	}
}