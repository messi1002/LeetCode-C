1.��ϣ��

bool isIsomorphic(char* s, char* t) {
    int hash1[128] = {0}, hash2[128] = {0}, len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        /*
         ���������������false:
            1.t�е���ͬ�ַ�ӳ����b�еĲ�ͬ�ַ���
            2.b�е���ͬ�ַ�ӳ����t�еĲ�ͬ�ַ���
         */
        if ((hash1[s[i]] == 0 && hash2[t[i]+1] != 0) || (hash1[s[i]] > 0 && hash1[s[i]] != t[i]+1))
            return false;
        else {
            hash1[s[i]] = t[i]+1;
            hash2[t[i]+1] = 1;
        }
    }
                 
    return true;
}