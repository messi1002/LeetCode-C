1.暴力解法

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    for (int i = 0; i < numsSize; i++) {
        int limit = i+k >= numsSize? numsSize: i+k+1;
        
        for (int j = i+1; j < limit; j++) {
            if (nums[j] == nums[i])
                return true;
        }
    }            
    
    return false;
}


2.滑动窗口 + 哈希表(uthash)

// uthash是一个用c语言编写的开源库，使用宏实现了哈希表的增删改查等功能。
bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    struct hash {
        int value;
        // makes this structure hashable.
        UT_hash_handle hh; 
    };
    
    struct hash *hashTable = NULL;
    int len = 0;
    
    for (int i = 0; i < numsSize; i++) {
        struct hash *h;
        
        // 控制滑动窗口的大小，即哈希表的大小。
        if (len > k) {
            HASH_FIND_INT(hashTable, nums+len-k-1, h);
            HASH_DEL(hashTable, h);
            h = NULL;
        }

        // 查找当前哈希表中有没有重复值。
        HASH_FIND_INT(hashTable, nums+i, h);

        if (h)
            return true;
        else {
            h = malloc(sizeof(struct hash));
            h->value = nums[i];
            HASH_ADD_INT(hashTable, value, h);
            len++;
        }
    }
    
    return false;
}