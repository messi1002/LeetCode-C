// 1.�������
public int peakIndexInMountainArray(int[] A) {
    int i = 0;
    // ��Ŀ����һ��ȷ��Ϊɽ�������飬���Բ��õ�������Խ�硣
    while (A[i] < A[i + 1]) {
        i++;
    }
    return i;
}

// 2.���ֲ���
public int peakIndexInMountainArray(int[] A) {
    int left = 0, right = A.length - 1;
    while (left <= right) {
        int mid = (left + right) >>> 1;
        if (A[mid] > A[mid - 1] && A[mid] > A[mid + 1]) {
            return mid;
        }
        if (A[mid] > A[mid - 1] && A[mid] < A[mid + 1]) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}