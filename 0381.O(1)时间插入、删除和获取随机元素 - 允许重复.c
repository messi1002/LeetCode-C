// 1.��ϣ��(uthash)
// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
// ��:�洢���Ԫ�ء�ֵ:�洢���Ԫ���������е�λ��(��������)
struct hash {
    int key;
    // ����key������arr�е��±�ֵ��������ɾ��Ԫ��
    int value[10];
    // ��¼��ֵͬ�ĸ���
    int size;
    UT_hash_handle hh; 
};

typedef struct {
    // ����(��������Ѳ����Ԫ��)��������O(1)ʱ���ȡ���Ԫ��
    int* arr;
    // ��¼������Ԫ�صĸ���
    int size;
    // ��ϣ��������O(1)ʱ������ɾ��Ԫ��
    struct hash* hashTable; 
} RandomizedCollection;

RandomizedCollection* randomizedCollectionCreate() {
    RandomizedCollection* r = malloc(sizeof(RandomizedCollection));
    r->arr = malloc(sizeof(int) * 5000);
    r->size = 0;
    r->hashTable = NULL;
    return r;
}

bool randomizedCollectionInsert(RandomizedCollection* obj, int val) {
    // �������Ԫ��
    struct hash *h; 
    HASH_FIND_INT(obj->hashTable, &val, h);
    if (!h) {
        h = malloc(sizeof(struct hash));
        h->key = val;
        h->size = 0;
        // �������顢����¼���������д洢���±�ֵ��������ɾ��Ԫ�ء�
        h->value[h->size++] = obj->size;
        obj->arr[obj->size++] = val;
        HASH_ADD_INT(obj->hashTable, key, h);
        return true;
    }
    // ��Ϊÿ��Ԫ�ر����صĸ���Ӧ�������ڼ����е�������������أ����Ա����������б����ظ�Ԫ�ء�
    else {
        h->value[h->size++] = obj->size;
        obj->arr[obj->size++] = val;
        return false;
    }
}

bool randomizedCollectionRemove(RandomizedCollection* obj, int val) {
    struct hash *h1, *h2; 
    HASH_FIND_INT(obj->hashTable, &val, h1); 
    // ������ڣ������������һ��Ԫ���Ƶ���Ԫ�ص�λ�ã����Ҹ��¼�¼���һ��Ԫ���±��obj->value���顣
    // ע��: ��ɾ����Ԫ�ش��ڶ�����Ԫ��ʱ��Ĭ��ɾ�����һ����ӵ����Ԫ�ء�
    if (h1) {
        obj->arr[h1->value[h1->size - 1]] = obj->arr[obj->size - 1]; 
        HASH_FIND_INT(obj->hashTable, &obj->arr[obj->size - 1], h2);
        // ���¼�¼���һ��Ԫ���±��obj->value����
        for (int i = 0; i < h2->size; i++) {
            if (h2->value[i] == obj->size - 1) {
                h2->value[i] = h1->value[h1->size - 1];
                obj->size--;
                h1->size--;
                break;
            }
        }
        if (h1->size == 0) {
            HASH_DEL(obj->hashTable, h1);
        }
        return true;
    }
    return false;
}

int randomizedCollectionGetRandom(RandomizedCollection* obj) {
    // ��Ϊ���в����Ԫ�ض������������У�����������ص���������������ʡ�
    return obj->arr[rand() % obj->size];
}

void randomizedCollectionFree(RandomizedCollection* obj) {
    free(obj->arr);
    free(obj);
}