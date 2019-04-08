1.��ϣ��

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    // ��ϣ��
    int hash[1000] = {0};
    int* result = malloc(sizeof(int)*nums1Size);
    *returnSize = 0;

    for (int i = 0; i < nums1Size; i++)
        hash[nums1[i]] = 1;
    for (int i = 0; i < nums2Size; i++) {
        // �����ظ����֡�
        if (hash[nums2[i]] == 1) {
            result[(*returnSize)++] = nums2[i];
            // ȥ�ء�
            hash[nums2[i]] = 0;
        }
    }
    
    return result;
}


2.uthash

// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    struct hash {
        int value;
        // makes this structure hashable.
        UT_hash_handle hh; 
    };
    
    struct hash *hashTable = NULL;
    int* result = malloc(sizeof(int)*nums1Size);
    
    for (int i = 0; i < nums1Size; i++) {
        struct hash *h;
        // ����ֵ��
        HASH_FIND_INT(hashTable, nums1+i, h);
        
        if (!h) {
            h = malloc(sizeof(struct hash));
            h->value = nums1[i];
            // ��ֵ����������ӡ�
            HASH_ADD_INT(hashTable, value, h);
        }
    }
    for (int i = 0; i < nums2Size; i++) {
        struct hash *h;
        HASH_FIND_INT(hashTable, nums2+i, h);
        
        // �ҵ�����Ԫ�غ󣬵ôӹ�ϣ����ɾ����(��Ϊ�������е�ÿ��Ԫ����Ψһ��)��
        if (h) {
            result[(*returnSize)++] = h->value;
            HASH_DEL(hashTable, h);
        }
    }
    
    return result;
}


3.���� + ˫ָ�����

// ���ź���(����)��
int compare(const void* a, const void* b) {
    return (*(int*)a)-(*(int*)b); 
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {    
    // ����
    qsort(nums1, nums1Size, sizeof(int), compare);
    qsort(nums2, nums2Size, sizeof(int), compare);
    
    int pos1 = 0, pos2 = 0; 
    int* result = malloc(sizeof(int)*nums1Size);
    *returnSize = 0;
    
    // ˫ָ�롣
    while (pos1 < nums1Size && pos2 < nums2Size) {
        if (nums1[pos1] < nums2[pos2])
            pos1++;
        else if (nums1[pos1] > nums2[pos2])
            pos2++;
        else {
            // ȥ�ء�
            if (*returnSize == 0 || nums1[pos1] != result[*returnSize-1])
                result[(*returnSize)++] = nums1[pos1];
            
            pos1++;
            pos2++;
        }
    }
    
    return result;
}