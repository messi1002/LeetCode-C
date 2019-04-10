1.��ϣ�� + ����

// ���ź���(����)��
// ע��:ֻ��Ҫ����arr[i][0](����ͬ�ַ����ֵĴ���)��
int compare(const void* a, const void* b) {
    return ((int*)b)[0]-((int*)a)[0]; 
}

char* frequencySort(char* s) {
    int hash[128] = {0}, arr[128][2] = {0}, len = strlen(s), size = 0;
   
    // ��ϣ��
    for (int i = 0; i < len; i++) 
        hash[s[i]]++;
    for (int i = 0; i < 128; i++) {
        // ��¼���г��ֹ�����ĸ������ִ�����
        if (hash[i] > 0) {
            arr[size][0] = hash[i];
            arr[size][1] = i;
            size++;
        }
    }
         
    // �Գ��ִ�����������
    qsort(arr, size, sizeof(arr[0]), compare);
    
    // ƴ���ַ�����
    for (int i = 0, j = 0; i < size; i++) {
        if (arr[i][0] > 0) {
            s[j++] = arr[i][1];
            arr[i][0]--;
            i--;
        }
    }
    
    return s;
}


2.��ϣ�� + �ַ�����

char* frequencySort(char* s) {
    int hash[128] = {0}, len = strlen(s);
    char** arr = malloc(sizeof(char*)*(len+1));
    
    // ��ϣ��
    for (int i = 0; i < len; i++) {
        hash[s[i]]++;
        arr[i] = malloc(sizeof(char)*1);   
        strcpy(arr[i], "");
    }
    
    arr[len] = malloc(sizeof(char)*1);
    strcpy(arr[len], "");
    strcpy(s, "");

    for (int i = 0; i < 128; i++) {
        if (hash[i] > 0) {
            int count = hash[i], l = strlen(arr[hash[i]]);
            char* s1 = malloc(sizeof(char)*(len+1));
            // �ַ�ת�ַ�����
            char s2[2];
            s2[0] = i;
            s2[1] = '\0';
            
            if (strcmp(arr[hash[i]], "") == 0) {
                arr[hash[i]] = malloc(sizeof(char)*(count+1));
                strcpy(arr[hash[i]], "");
            }
            // ������ַ����ִ�����ͬ��
            else {
                strcpy(s1, arr[hash[i]]);
                arr[hash[i]] = malloc(sizeof(char)*(count+l+1));
                strcpy(arr[hash[i]], s1);
            }
            
            // ƴ����ͬ�ַ���
            while (count > 0) {
                strcat(arr[hash[i]], s2);             
                count--;
            }
        }
    }
    // ƴ���ַ�����
    for (int i = len; i > 0; i--) {
        if (strlen(arr[i]) > 0)
            strcat(s, arr[i]);
    }
    
    return s;
}


3.��ϣ��(uthash)

// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
struct hash {
    int key;
    int count;
    UT_hash_handle hh; 
};

// �������С�
int count_sort(struct hash* a, struct hash* b) {
    return b->count - a->count;
}

char* frequencySort(char* s) { 
    struct hash* hashTable = NULL;
    int len = strlen(s);
    char* result = malloc(sizeof(char)*(len+1));
    strcpy(result, "");
    
    // �ù�ϣ��ͳ�Ʋ�ͬ�ַ��ĳ��ִ�����
    for (int i = 0; i < len; i++) {
        struct hash* h;
        int n = s[i];
        HASH_FIND_INT(hashTable, &n, h);
        
        if (!h) {
            h = malloc(sizeof(struct hash));
            h->key = s[i];
            h->count = 1;
            HASH_ADD_INT(hashTable, key, h);
        }
        else
            h->count++;
    }
    
    // �����ִ��������ֵ(�ַ�)��
    HASH_SORT(hashTable, count_sort);
    
    // ���������Ĺ�ϣ��
    for (struct hash* s = hashTable; s != NULL; s = s->hh.next) {
        while (s->count > 0) {
            char s1[2];
            s1[0] = s->key;
            s1[1] = '\0';
            strcat(result, s1);
            s->count--;
        }
    }
    
    return result;
}