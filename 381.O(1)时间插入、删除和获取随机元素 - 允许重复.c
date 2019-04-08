1.��ϣ��(uthash)

// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
struct hash {
    int key;
    // ����key������arr�е��±�ֵ��������ɾ��Ԫ�ء�
    int value[10];
    // ��¼��ֵͬ�ĸ�����
    int size;
    UT_hash_handle hh; 
};

typedef struct {
    // ����(��������Ѳ����Ԫ��)��������O(1)ʱ���ȡ���Ԫ�ء�
    int* arr;
    // ��¼������Ԫ�صĸ�����
    int size;
    // ��ϣ��������O(1)ʱ������ɾ��Ԫ�ء�
    struct hash* hashTable; 
} RandomizedCollection;

RandomizedCollection* randomizedCollectionCreate() {
    RandomizedCollection* r = malloc(sizeof(RandomizedCollection));
    r->arr = malloc(sizeof(int)*5000);
    r->size = 0;
    r->hashTable = NULL;
    
    return r;
}

bool randomizedCollectionInsert(RandomizedCollection* obj, int val) {
    struct hash *h; 
    HASH_FIND_INT(obj->hashTable, &val, h);
    
    // ���val�����ڣ�����ӡ�
    if (!h) {    
        h = malloc(sizeof(struct hash));
        h->key = val;
        // �������顢����¼���������д洢���±�ֵ��������ɾ��Ԫ�ء�
        obj->arr[obj->size] = val;
        h->value[0] = obj->size;
        obj->size++;
        h->size = 1;
        HASH_ADD_INT(obj->hashTable, key, h);
        
        return true;
    }
    // ��Ϊ�����ظ������Լ�¼�ظ�������
    // ��Ϊÿ��Ԫ�ر����صĸ���Ӧ�������ڼ����е�������������أ����Ա����������б����ظ�Ԫ�ء�
    else {
        obj->arr[obj->size] = val;
        h->value[h->size] = obj->size;
        obj->size++;
        h->size++;
        
        return false;
    }
}

// O(N)���Ӷȣ���ʱû���뵽�Ż�������
bool randomizedCollectionRemove(RandomizedCollection* obj, int val) {
    struct hash *h1, *h2; 
    HASH_FIND_INT(obj->hashTable, &val, h1);
    
    // ������ڣ������������һ��Ԫ���Ƶ���Ԫ�ص�λ��(��֤0~obj->size������ֵ��Ч)�����Ҹ��¼�¼���һ��Ԫ���±��obj->value���顣
    // ע��:��ɾ����Ԫ�ش��ڶ��ʱ��Ĭ��ɾ�������±�ֵ�����Ǹ���
    if (h1) {
        obj->arr[h1->value[h1->size-1]] = obj->arr[obj->size-1]; 
        HASH_FIND_INT(obj->hashTable, &obj->arr[obj->size-1], h2);
       
        for (int i = 0; i < h2->size;i++) {
            if (h2->value[i] == obj->size-1) {
                h2->value[i] = h1->value[h1->size-1];
                break;
            }
        }
        
        obj->size--;
        h1->size--;
        
        if (h1->size == 0)
            HASH_DEL(obj->hashTable, h1);

        return true;
    }
    
    return false;
}

// ��Ϊ���в����Ԫ�ض������������У�����������ص���������������ʡ�
int randomizedCollectionGetRandom(RandomizedCollection* obj) {
    return obj->arr[rand()%obj->size];
}

void randomizedCollectionFree(RandomizedCollection* obj) {
    free(obj->arr);
    free(obj);
}