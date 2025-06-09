/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [과제 설명 - 2번 문제]
 * 몇몇 알고리즘들이 데이터의 상태에 따라 알고리즘의 수행속도가 달라지는 점을 실험하는 프로그램
 * 
 * 실험 내용:
 * - Bubble sort (adaptive): 정렬된 데이터에서 O(n) 성능 검증
 * - Insertion sort: 정렬된 데이터에서 O(n) 성능 검증  
 * - Quick sort: 정렬된 데이터에서 O(n²) 성능 검증
 * - Randomized quick sort: 정렬된 데이터에서도 O(n log n) 성능 검증
 * - n=10,000~100,000 범위에서 실험 수행
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>
 
 /*
  * ===========================================
  * 2번 문제: 공통 유틸리티 함수들
  * ===========================================
  */
 
 // 배열 복사 함수 (2번 문제용)
 void copyArray_problem2(int* dest, int* src, int n) {
     for (int i = 0; i < n; i++) {
         dest[i] = src[i];
     }
 }
 
 // 정렬된 배열 생성 (2번 문제용)
 void generateSortedArray_problem2(int arr[], int n) {
     for (int i = 0; i < n; i++) {
         arr[i] = i + 1;  // 1, 2, 3, ..., n
     }
 }
 
 /*
  * ===========================================
  * 2번 문제: ① Bubble Sort (Adaptive Version) 구현
  * O(n) 성능 검증용 - 정렬된 데이터에서 사용
  * ===========================================
  */
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
 
 /*
  * ===========================================
  * 2번 문제: ③ Insertion Sort 구현  
  * O(n) 성능 검증용 - 정렬된 데이터에서 사용
  * ===========================================
  */
 void insertionSort_problem2(int arr[], int n) {
     for (int i = 1; i < n; i++) {
         int key = arr[i];
         int j = i - 1;
         
         // 정렬된 데이터에서는 while 루프가 바로 종료되어 O(n) 달성
         while (j >= 0 && arr[j] > key) {
             arr[j + 1] = arr[j];
             j = j - 1;
         }
         arr[j + 1] = key;
     }
 }
 
 /*
  * ===========================================
  * 2번 문제: ⑤ Quick Sort 구현
  * O(n²) 성능 검증용 - 정렬된 데이터에서 사용  
  * ===========================================
  */
 int partition_problem2(int arr[], int low, int high) {
     int pivot = arr[high];  // 마지막 원소를 피벗으로 선택
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
 
 void quickSortHelper_problem2(int arr[], int low, int high) {
     if (low < high) {
         int pi = partition_problem2(arr, low, high);
         
         // 정렬된 데이터에서는 매번 최악의 분할이 일어나 O(n²) 달성
         quickSortHelper_problem2(arr, low, pi - 1);
         quickSortHelper_problem2(arr, pi + 1, high);
     }
 }
 
 void quickSort_problem2(int arr[], int n) {
     quickSortHelper_problem2(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 2번 문제: ⑦ Randomized Quick Sort 구현
  * O(n log n) 성능 검증용 - 정렬된 데이터에서도 안정적 성능
  * ===========================================
  */
 int randomizedPartitionHelper_problem2(int arr[], int low, int high) {
     int pivot = arr[low];  // 맨 앞 원소를 피벗으로 사용
     int i = low + 1;
     int j = high;
     
     while (i <= j) {
         while (i <= high && arr[i] <= pivot) {
             i++;
         }
         while (j >= low && arr[j] > pivot) {
             j--;
         }
         if (i < j) {
             int temp = arr[i];
             arr[i] = arr[j];
             arr[j] = temp;
         }
     }
     
     // 피벗을 올바른 위치에 배치
     int temp = arr[low];
     arr[low] = arr[j];
     arr[j] = temp;
     
     return j;
 }
 
 int randomizedPartition_problem2(int arr[], int low, int high) {
     // 랜덤 피벗 선택으로 정렬된 데이터에서도 균형잡힌 분할
     int randomIndex = low + rand() % (high - low + 1);
     
     int temp = arr[randomIndex];
     arr[randomIndex] = arr[low];
     arr[low] = temp;
     
     // 맨 앞을 피벗으로 하는 파티션 수행
     return randomizedPartitionHelper_problem2(arr, low, high);
 }
 
 void randomizedQuickSortHelper_problem2(int arr[], int low, int high) {
     if (low < high) {
         int pi = randomizedPartition_problem2(arr, low, high);
         
         randomizedQuickSortHelper_problem2(arr, low, pi - 1);
         randomizedQuickSortHelper_problem2(arr, pi + 1, high);
     }
 }
 
 void randomizedQuickSort_problem2(int arr[], int n) {
     randomizedQuickSortHelper_problem2(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 2번 문제: 특수 데이터 패턴 성능 분석 실험 함수
  * ===========================================
  */
 void experiment_problem2() {
     printf("=== 특수 데이터 패턴 성능 분석 실험 ===\n");
     printf("실험 조건: 정렬된 데이터에서 알고리즘별 성능 차이 검증\n");
     printf("n=10,000~100,000 범위에서 실험 수행\n\n");
     
     int sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     
     // 2-1: Bubble Sort with sorted data (should be O(n))
     printf("--- 2-1: Bubble Sort (정렬된 데이터) - O(n) 검증 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         int* arr = (int*)malloc(n * sizeof(int));
         
         generateSortedArray_problem2(arr, n);
         
         clock_t start = clock();
         bubbleSort_problem2(arr, n);
         clock_t end = clock();
         
         double time = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("2-1 - Bubble Sort (정렬된 데이터) - n=%6d: %10.6f sec\n", n, time);
         
         free(arr);
     }
     
     // 2-2: Insertion Sort with sorted data (should be O(n))
     printf("\n--- 2-2: Insertion Sort (정렬된 데이터) - O(n) 검증 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         int* arr = (int*)malloc(n * sizeof(int));
         
         generateSortedArray_problem2(arr, n);
         
         clock_t start = clock();
         insertionSort_problem2(arr, n);
         clock_t end = clock();
         
         double time = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("2-2 - Insertion Sort (정렬된 데이터) - n=%6d: %10.6f sec\n", n, time);
         
         free(arr);
     }
     
     // 2-3: Quick Sort with sorted data (should be O(n²))
     printf("\n--- 2-3: Quick Sort (정렬된 데이터) - O(n²) 검증 ---\n");
     printf("2-3: Stack size를 10MB로 설정하여 overflow 방지\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         int* arr = (int*)malloc(n * sizeof(int));
         
         generateSortedArray_problem2(arr, n);
         
         clock_t start = clock();
         quickSort_problem2(arr, n);
         clock_t end = clock();
         
         double time = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("2-3 - Quick Sort (정렬된 데이터) - n=%6d: %10.6f sec\n", n, time);
         
         free(arr);
     }
     
     // 2-4: Randomized Quick Sort with sorted data (should be O(n log n))
     printf("\n--- 2-4: Randomized Quick Sort (정렬된 데이터) - O(n log n) 검증 ---\n");
     printf("2-4: 랜덤 피벗 선택으로 정렬된 데이터에서도 안정적 성능\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         int* arr = (int*)malloc(n * sizeof(int));
         
         generateSortedArray_problem2(arr, n);
         
         clock_t start = clock();
         randomizedQuickSort_problem2(arr, n);
         clock_t end = clock();
         
         double time = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("2-4 - Randomized Quick Sort (정렬된 데이터) - n=%6d: %10.6f sec\n", n, time);
         
         free(arr);
     }
     
     printf("\n=== 2번 문제 실험 결과 요약 ===\n");
     printf("2-1: Bubble Sort (adaptive) - 정렬된 데이터에서 O(n) 성능 확인\n");
     printf("2-2: Insertion Sort - 정렬된 데이터에서 O(n) 성능 확인\n");
     printf("2-3: Quick Sort - 정렬된 데이터에서 O(n²) 성능으로 심각한 성능 저하\n");
     printf("2-4: Randomized Quick Sort - 정렬된 데이터에서도 O(n log n) 안정적 성능\n");
     printf("입력 데이터 패턴이 알고리즘 성능에 미치는 영향 확인\n");
     printf("적응성(adaptability)과 무작위화(randomization) 기법의 효과 검증\n");
 }
 
 int main() {
     printf("=== 정렬 알고리즘 특수 데이터 패턴 분석 (2번 문제) ===\n");
     printf("학번: 202214314, 이름: 이지현\n\n");
     
     srand(time(NULL));
     
     experiment_problem2();
     
     return 0;
 }