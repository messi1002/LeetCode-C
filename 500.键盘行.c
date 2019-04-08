1.��ϣ��

char** findWords(char** words, int wordsSize, int* returnSize) {
    // �ù�ϣ���¼26����ĸ�����ļ���������
    int hash[26] = {1, 0, 0, 1, 2, 1, 1, 1, 2, 1, 1, 1, 0, 0, 2, 2, 2, 2, 1, 2, 2, 0, 2, 0, 2, 0};
    int** result = malloc(sizeof(int*)*wordsSize);
    *returnSize = 0;
    
    for (int i = 0; i < wordsSize; i++) {
        // ��mark��¼ÿ�е�һ����ĸ�����ļ���������
        int mark = hash[tolower(words[i][0])-'a'], len = strlen(words[i]), j = 0;
        
        while (j < len) {
            // �鿴֮�����ĸ�Ƿ�͵�һ����ĸ���ڼ��̵�ͬһ�С�
            if (hash[tolower(words[i][j])-'a'] != mark)
                break;   
            else if (j == len-1) {
                result[*returnSize] = malloc(sizeof(int)*len);
                result[*returnSize] = words[i];
                (*returnSize)++;
            }
            
            j++;
        }
    }

    return result;
}