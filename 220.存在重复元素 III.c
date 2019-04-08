1.��������+��ϣ��(uthash)

// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t) {
    struct hash {
        int value;
        // makes this structure hashable.
        UT_hash_handle hh; 
    };
    
    struct hash *hashTable = NULL;
    int len = 0;
    
    for (int i = 0; i < numsSize; i++) {
        struct hash *h1, *h2;
        
        // ���ƻ������ڵĴ�С������ϣ��Ĵ�С��
        if (len > k) {
            HASH_FIND_INT(hashTable, nums+len-k-1, h1);
            HASH_DEL(hashTable, h1);
        }

        // ���ҵ�ǰ��ϣ�����Ƿ����|nums[i]-��ֵ| <= t��
        for (struct hash *s = hashTable; s!= NULL; s = s->hh.next) {
            if (labs((long)nums[i]-(long)s->value) <= t)
                return true;
        }
        
        HASH_FIND_INT(hashTable, nums+i, h2);

        if (!h2) {   
            h2 = malloc(sizeof(struct hash));
            h2->value = nums[i];
            HASH_ADD_INT(hashTable, value, h2);
            len++;
        }
    }
    
    return false;
}


2.�����ⷨ

bool containsNearbyAlmostDuplicate(int* nums, int numsSize, int k, int t) {
    for (int i = 0; i < numsSize; i++) {
        int limit = i+k >= numsSize? numsSize: i+k+1;
            
        for (int j = i+1; j < limit; j++) {
            // labs()����:�����͵ľ���ֵ��
            if (labs((long)nums[i]-(long)nums[j]) <= t)
                return true;
        }
    }
    
    return false;
}