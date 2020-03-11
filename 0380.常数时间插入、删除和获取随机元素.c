// 1.��ϣ��(uthash)
// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
// ��:�洢���Ԫ�ء�ֵ:�洢���Ԫ���������е�λ��(����)
struct hash {
    int key;
    int value;
    UT_hash_handle hh; 
};

typedef struct {
    // ����(��������Ѳ����Ԫ��)��������O(1)ʱ���ȡ���Ԫ��
    int* arr;
    // ��¼������Ԫ�صĸ���
    int size;
    // ��ϣ��������O(1)ʱ������ɾ��Ԫ��
    struct hash* hashTable; 
} RandomizedSet;

/** Initialize your data structure here. */
RandomizedSet* randomizedSetCreate() {
    RandomizedSet* r = malloc(sizeof(RandomizedSet));
    r->arr = malloc(sizeof(int) * 5000);
    r->size = 0;
    r->hashTable = NULL;
    return r;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    struct hash *h; 
    HASH_FIND_INT(obj->hashTable, &val, h);
    if (!h) {
        // �������顢����¼���������д洢���±�ֵ(�����ϣ��)��������ɾ��Ԫ��
        h = malloc(sizeof(struct hash));
        h->key = val;
        h->value = obj->size;
        obj->arr[obj->size++] = val;
        HASH_ADD_INT(obj->hashTable, key, h);
        return true;
    }
    return false;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    struct hash *h1, *h2; 
    HASH_FIND_INT(obj->hashTable, &val, h1);
    // ������ڣ������������һ��Ԫ���Ƶ���Ԫ�ص�λ�ã��Ӷ���֤0~obj->size������ֵ��Ч��
    if (h1) {
        obj->arr[h1->value] = obj->arr[obj->size - 1]; 
        HASH_FIND_INT(obj->hashTable, &obj->arr[obj->size - 1], h2);
        h2->value = h1->value;
        obj->size--;
        HASH_DEL(obj->hashTable, h1);
        return true;
    }
    return false;
}

// ��ȡ���Ԫ��
int randomizedSetGetRandom(RandomizedSet* obj) {
    return obj->arr[rand() % obj->size];
}

void randomizedSetFree(RandomizedSet* obj) {
    free(obj->arr);
    free(obj);
}