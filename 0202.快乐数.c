// 1.����
bool isHappy(int n) {
    int hash[500] = {0};
    while (n != 1) {
        int sum = 0;
        // ��ÿ��λ���ϵ����ֵ�ƽ����
        while (n > 0) {
            int d = n % 10;
            n /= 10;
            sum += d * d;
        }
        // �ж��Ƿ�������ѭ��
        if (hash[sum] == 0) {
            hash[sum] = 1;
            n = sum;
        }
        else {
            return false;
        }
    }
    return true;
}

// 2.��ϣ��(uthash)
// uthash��һ����c���Ա�д�Ŀ�Դ�⣬ʹ�ú�ʵ���˹�ϣ�����ɾ�Ĳ�ȹ��ܡ�
struct hash {
    int value;
    UT_hash_handle hh; 
};

bool isHappy(int n) {
    struct hash *hashTable = NULL;
    while (n != 1) {
        int sum = 0;
        // ��ÿ��λ���ϵ����ֵ�ƽ����
        while (n > 0) {
            int d = n % 10;
            n /= 10;
            sum += d * d;
        }
        struct hash *h;
        HASH_FIND_INT(hashTable, &sum, h);
        // �ж��Ƿ�������ѭ��
        if (!h) {
            h = malloc(sizeof(struct hash));
            h->value = sum;
            HASH_ADD_INT(hashTable, value, h);
            n = sum;
        } 
        else {
            return false;
        }
    }
    return true;
}

// 3.��ѧ
bool isHappy(int n) {
    while (n != 1) {
        int sum = 0;
        // �ж��Ƿ�������ѭ��
        if (n == 4) {
            return false;
        }
        // ��ÿ��λ���ϵ����ֵ�ƽ����
        while (n > 0) {
            int d = n % 10;
            n /= 10;
            sum += d * d;
        }
        n = sum;
    }
    return true;
}

// 4.��ѧ�����Ż�
// ��n<=6������ѭ������ʱ��n==1�����ǿ���������n==2/3/4/5/6�����ǿ�����(һ������ѭ���Ĺ����У���ѭ�����ǿ��������������������Ϊ������)��
bool isHappy(int n) {
    while (n > 6) {
        int sum = 0;
        // ��ÿ��λ���ϵ����ֵ�ƽ����
        while (n > 0) {
            int d = n % 10;
            n /= 10;
            sum += d * d;
        }        
        n = sum;
    }
    return n == 1;
}