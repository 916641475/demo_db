//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) num_pages_(num_pages){}

LRUReplacer::~LRUReplacer() = default;

auto LRUReplacer::Victim(frame_id_t *frame_id) -> bool { 
    for(auto iter = lru_list_.rbegin(); iter != lru_list_.rend(); iter++){
        if(!pinned_pages_.count(*iter)){
            *frame_id = *iter;
            return true;
        } 
    }
    *frame_id = nullptr;
    return false;
}

void LRUReplacer::Pin(frame_id_t frame_id) { pinned_pages_.insert(frame_id); }

void LRUReplacer::Unpin(frame_id_t frame_id) {
    pinned_pages_.erase(frame_id);
    
    lru_list_.erase(lru_frame_mapper_[frame_id_t]);
    lru_frame_mapper_[frame_id_t] = lru_list_.push_front(frame_id_t);
}

auto LRUReplacer::Size() -> size_t { return lru_list_.size(); }

}  // namespace bustub
