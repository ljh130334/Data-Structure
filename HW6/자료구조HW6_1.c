/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [과제 설명 - 1번 문제]
 * array의 크기가 증가함에 따라서, 평균의 경우 (random data) 각 sorting algorithm의 time complexity를 측정하는 프로그램
 * 
 * 실험 내용:
 * - n=10,000인 array에 정수 data를 random하게 대입
 * - 각 sorting algorithm이 같은 array를 sort해야 하므로 array를 6개의 set로 생성
 * - 각 sorting algorithm이 sorting을 수행한 시간을 순차적으로 측정
 * - n=20,000, 30,000, ..., n=100,000일 때 같은 실험을 반복 실행하여 time complexity 비교
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>
 
 /*
  * ===========================================
  * 1번 문제: 공통 유틸리티 함수들
  * ===========================================
  */
 
 // 배열 복사 함수 (1번 문제용)
 void copyArray_problem1(int* dest, int* src, int n) {
     for (int i = 0; i < n; i++) {
         dest[i] = src[i];
     }
 }
 
 // 랜덤 배열 생성 (1번 문제용)
 void generateRandomArray_problem1(int arr[], int n) {
     for (int i = 0; i < n; i++) {
         arr[i] = rand() % (n * 10);  // 0 ~ n*10 범위의 랜덤 수
     }
 }
 
 /*
  * ===========================================
  * 1번 문제: ① Bubble Sort (Adaptive Version) 구현
  * ===========================================
  */
 void bubbleSort_problem1(int arr[], int n) {
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
         // 적응성: 스왑이 없으면 이미 정렬됨
         if (swapped == 0) {
             break;
         }
     }
 }
 
 /*
  * ===========================================
  * 1번 문제: ② Selection Sort 구현
  * ===========================================
  */
 void selectionSort_problem1(int arr[], int n) {
     for (int i = 0; i < n - 1; i++) {
         int minIdx = i;
         for (int j = i + 1; j < n; j++) {
             if (arr[j] < arr[minIdx]) {
                 minIdx = j;
             }
         }
         // 최솟값과 현재 위치 교환
         if (minIdx != i) {
             int temp = arr[i];
             arr[i] = arr[minIdx];
             arr[minIdx] = temp;
         }
     }
 }
 
 /*
  * ===========================================
  * 1번 문제: ③ Insertion Sort 구현
  * ===========================================
  */
 void insertionSort_problem1(int arr[], int n) {
     for (int i = 1; i < n; i++) {
         int key = arr[i];
         int j = i - 1;
         
         while (j >= 0 && arr[j] > key) {
             arr[j + 1] = arr[j];
             j = j - 1;
         }
         arr[j + 1] = key;
     }
 }
 
 /*
  * ===========================================
  * 1번 문제: ④ Merge Sort 구현
  * ===========================================
  */
 void merge_problem1(int arr[], int left, int mid, int right) {
     int n1 = mid - left + 1;
     int n2 = right - mid;
     
     int* L = (int*)malloc(n1 * sizeof(int));
     int* R = (int*)malloc(n2 * sizeof(int));
     
     for (int i = 0; i < n1; i++) {
         L[i] = arr[left + i];
     }
     for (int j = 0; j < n2; j++) {
         R[j] = arr[mid + 1 + j];
     }
     
     int i = 0, j = 0, k = left;
     
     while (i < n1 && j < n2) {
         if (L[i] <= R[j]) {
             arr[k] = L[i];
             i++;
         } else {
             arr[k] = R[j];
             j++;
         }
         k++;
     }
     
     while (i < n1) {
         arr[k] = L[i];
         i++;
         k++;
     }
     
     while (j < n2) {
         arr[k] = R[j];
         j++;
         k++;
     }
     
     free(L);
     free(R);
 }
 
 void mergeSortHelper_problem1(int arr[], int left, int right) {
     if (left < right) {
         int mid = left + (right - left) / 2;
         
         mergeSortHelper_problem1(arr, left, mid);
         mergeSortHelper_problem1(arr, mid + 1, right);
         merge_problem1(arr, left, mid, right);
     }
 }
 
 void mergeSort_problem1(int arr[], int n) {
     mergeSortHelper_problem1(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 1번 문제: ⑤ Quick Sort 구현
  * ===========================================
  */
 int partition_problem1(int arr[], int low, int high) {
     int pivot = arr[high];
     int i = (low - 1);
     
     for (int j = low; j <= high - 1; j++) {
         if (arr[j] < pivot) {
             i++;
             int temp = arr[i];
             arr[i] = arr[j];
             arr[j] = temp;
         }
     }
     int temp = arr[i + 1];
     arr[i + 1] = arr[high];
     arr[high] = temp;
     return (i + 1);
 }
 
 void quickSortHelper_problem1(int arr[], int low, int high) {
     if (low < high) {
         int pi = partition_problem1(arr, low, high);
         
         quickSortHelper_problem1(arr, low, pi - 1);
         quickSortHelper_problem1(arr, pi + 1, high);
     }
 }
 
 void quickSort_problem1(int arr[], int n) {
     quickSortHelper_problem1(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 1번 문제: ⑥ Heap Sort 구현
  * ===========================================
  */
 void heapify_problem1(int arr[], int n, int i) {
     int largest = i;
     int left = 2 * i + 1;
     int right = 2 * i + 2;
     
     if (left < n && arr[left] > arr[largest]) {
         largest = left;
     }
     
     if (right < n && arr[right] > arr[largest]) {
         largest = right;
     }
     
     if (largest != i) {
         int temp = arr[i];
         arr[i] = arr[largest];
         arr[largest] = temp;
         
         heapify_problem1(arr, n, largest);
     }
 }
 
 void heapSort_problem1(int arr[], int n) {
     // Build heap
     for (int i = n / 2 - 1; i >= 0; i--) {
         heapify_problem1(arr, n, i);
     }
     
     // Extract elements from heap one by one
     for (int i = n - 1; i >= 0; i--) {
         int temp = arr[0];
         arr[0] = arr[i];
         arr[i] = temp;
         
         heapify_problem1(arr, i, 0);
     }
 }
 
 /*
  * ===========================================
  * 1번 문제: 랜덤 데이터 성능 비교 실험 함수
  * ===========================================
  */
 void experiment_problem1() {
     printf("=== 랜덤 데이터 성능 비교 실험 ===\n");
     printf("실험 조건: n=10,000~100,000, 각 크기별로 랜덤 데이터 정렬 시간 측정\n");
     printf("각 알고리즘이 같은 배열을 정렬하므로 6개의 동일한 배열 세트 사용\n\n");
     
     int sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         printf("--- n = %d 성능 측정 ---\n", n);
         
         // 동적 메모리 할당
         int* original = (int*)malloc(n * sizeof(int));
         int* test1 = (int*)malloc(n * sizeof(int));  // Bubble Sort용
         int* test2 = (int*)malloc(n * sizeof(int));  // Selection Sort용
         int* test3 = (int*)malloc(n * sizeof(int));  // Insertion Sort용
         int* test4 = (int*)malloc(n * sizeof(int));  // Merge Sort용
         int* test5 = (int*)malloc(n * sizeof(int));  // Quick Sort용
         int* test6 = (int*)malloc(n * sizeof(int));  // Heap Sort용
         
         // 랜덤 배열 생성
         generateRandomArray_problem1(original, n);
         
         // 모든 알고리즘이 같은 배열을 정렬하도록 복사
         copyArray_problem1(test1, original, n);
         copyArray_problem1(test2, original, n);
         copyArray_problem1(test3, original, n);
         copyArray_problem1(test4, original, n);
         copyArray_problem1(test5, original, n);
         copyArray_problem1(test6, original, n);
         
         // ① Bubble Sort 시간 측정 (1번 문제)
         clock_t start = clock();
         bubbleSort_problem1(test1, n);
         clock_t end = clock();
         double bubbleTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("① Bubble Sort:    %8.4f sec\n", bubbleTime);
         
         // ② Selection Sort 시간 측정 (1번 문제)
         start = clock();
         selectionSort_problem1(test2, n);
         end = clock();
         double selectionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("② Selection Sort: %8.4f sec\n", selectionTime);
         
         // ③ Insertion Sort 시간 측정 (1번 문제)
         start = clock();
         insertionSort_problem1(test3, n);
         end = clock();
         double insertionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("③ Insertion Sort: %8.4f sec\n", insertionTime);
         
         // ④ Merge Sort 시간 측정 (1번 문제)
         start = clock();
         mergeSort_problem1(test4, n);
         end = clock();
         double mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("④ Merge Sort:     %8.4f sec\n", mergeTime);
         
         // ⑤ Quick Sort 시간 측정 (1번 문제)
         start = clock();
         quickSort_problem1(test5, n);
         end = clock();
         double quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("⑤ Quick Sort:     %8.4f sec\n", quickTime);
         
         // ⑥ Heap Sort 시간 측정 (1번 문제)
         start = clock();
         heapSort_problem1(test6, n);
         end = clock();
         double heapTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("⑥ Heap Sort:      %8.4f sec\n", heapTime);
         
         printf("\n");
         
         // 메모리 해제
         free(original);
         free(test1);
         free(test2);
         free(test3);
         free(test4);
         free(test5);
         free(test6);
     }
     
     printf("=== 실험 결과 요약 ===\n");
     printf("랜덤 데이터에서 시간 복잡도 측정 완료\n");
     printf("시간 복잡도:\n");
     printf("  - O(n²): Bubble Sort, Selection Sort, Insertion Sort (평균)\n");
     printf("  - O(n log n): Merge Sort, Quick Sort, Heap Sort (평균)\n");
     printf("데이터 크기 증가에 따른 시간 복잡도 증가 패턴 확인\n");
 }
 
 int main() {
     printf("=== 정렬 알고리즘 랜덤 데이터 성능 비교 (1번 문제) ===\n");
     printf("학번: 202214314, 이름: 이지현\n\n");
     
     srand(time(NULL));
     
     experiment_problem1();
     
     return 0;
 }