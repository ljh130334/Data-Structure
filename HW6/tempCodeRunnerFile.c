 void bubbleSort_problem2(int arr[], int n) {
     int swapped;
     for (int i = 0; i < n - 1; i++) {
         swapped = 0;
         for (int j = 0; j < n - i - 1; j++) {
             if (arr[j] > arr[j + 1]) {
                 // Swap
                 int temp = arr[j];
                 arr[j] = arr[j + 1];
                 arr[j + 1] = temp;
                 swapped = 1;
             }
         }
         // 적응성: 스왑이 없으면 이미 정렬됨 (O(n) 달성)
         if (swapped == 0) {
             break;
         }
     }
 }