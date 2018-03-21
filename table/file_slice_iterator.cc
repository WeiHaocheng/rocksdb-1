#include "file_slice_iterator.h"

namespace rocksdb{

FileSliceIterator::FileSliceIterator(FileSlice& file_slice, InternalIterator* file_iter, 
			const InternalKeyComparator& internal_comparator)
	:	file_slice_(file_slice),
		file_iter_(file_iter),
		internal_comparator_(internal_comparator) {
		SeekToFirst();
}

bool FileSliceIterator::Valid() const{
	if (!file_iter_->Valid()){
		return false;
	}

	Slice& key = file_iter_->key();
	auto scmp = internal_comparator_->Compare(key, file_slice_.smallest_key.Encode());
	if (scmp < 0 || (scmp == 0 && !file_slice_.is_contain_smallest)){
		return false;
	}

	if (internal_comparator_->Compare(key, file_slice_.largest_key.Encode()) > 0){
		return false;
	}

	return true;
}

Slice FileSliceIterator::key() const{
	assert(Valid());
	return file_iter_->key();
}

Slice FileSliceIterator::value() const{
	assert(Valid());
	return file_iter_->value();
}

void FileSliceIterator::Next() {
	if(Valid()) {
		file_iter_->Next();
	}
}

void FileSliceIterator::Prev() {
	if(Valid()) {
		file_iter_->Prev();
	}
}

//TODO WEIHAOCHENG: add error status
Status FileSliceIterator::status() const {
	return Status::OK();
}

void FileSliceIterator::Seek(const Slice& target) {
	file_iter_->Seek(target);
}

void FileSliceIterator::SeekToFirst() {
	file_iter_->Seek(file_slice_.smallest_key.Encode());
	if (!file_slice_.is_contain_smallest) {
		file_iter_->Next();
	}
}

void FileSliceIterator::SeekToLast() {
	file_iter_->Seek(file_slice_.largest_key.Encode());
}

} //namespace rocksdb