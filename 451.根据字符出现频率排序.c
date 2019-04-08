1.哈希表 + 排序

// 快排函数(降序)。
// 注意:只需要排序arr[i][0](代表不同字符出现的次数)。
int compare(const void* a, const void* b) {
    return ((int*)b)[0]-((int*)a)[0]; 
}

char* frequencySort(char* s) {
    int hash[128] = {0}, arr[128][2] = {0}, len = strlen(s), size = 0;
   
    // 哈希表。
    for (int i = 0; i < len; i++) 
        hash[s[i]]++;
    for (int i = 0; i < 128; i++) {
        // 记录所有出现过的字母及其出现次数。
        if (hash[i] > 0) {
            arr[size][0] = hash[i];
            arr[size][1] = i;
            size++;
        }
    }
         
    // 对出现次数进行排序。
    qsort(arr, size, sizeof(arr[0]), compare);
    
    // 拼接字符串。
    for (int i = 0, j = 0; i < size; i++) {
        if (arr[i][0] > 0) {
            s[j++] = arr[i][1];
            arr[i][0]--;
            i--;
        }
    }
    
    return s;
}


2. 哈希表 + 字符数组

char* frequencySort(char* s) {
    int hash[128] = {0}, len = strlen(s);
    char** arr = malloc(sizeof(char*)*(len+1));
    
    // 哈希表。
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
            // 字符转字符串。
            char s2[2];
            s2[0] = i;
            s2[1] = '\0';
            
            if (strcmp(arr[hash[i]], "") == 0) {
                arr[hash[i]] = malloc(sizeof(char)*(count+1));
                strcpy(arr[hash[i]], "");
            }
            // 若多个字符出现次数相同。
            else {
                strcpy(s1, arr[hash[i]]);
                arr[hash[i]] = malloc(sizeof(char)*(count+l+1));
                strcpy(arr[hash[i]], s1);
            }
            
            // 拼接相同字符。
            while (count > 0) {
                strcat(arr[hash[i]], s2);             
                count--;
            }
        }
    }
    // 拼接字符串。
    for (int i = len; i > 0; i--) {
        if (strlen(arr[i]) > 0)
            strcat(s, arr[i]);
    }
    
    return s;
}