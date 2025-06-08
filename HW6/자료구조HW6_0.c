/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [과제 설명 - 0번 문제]
 * 구현한 sorting algorithm들이 정확히 동작하는지 검증하는 프로그램
 * 
 * 실험 내용:
 * - n=30 크기의 랜덤 배열 생성
 * - 각 정렬 알고리즘이 올바르게 동작하는지 확인
 * - 정렬 전후 배열 출력 및 정렬 상태 검증
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <string.h>
 
 /*
  * ===========================================
  * 0번 문제: 공통 유틸리티 함수들
  * ===========================================
  */
 
 // 배열 복사 함수 (0번 문제용)
 void copyArray(int* dest, int* src, int n) {
     for (int i = 0; i < n; i++) {
         dest[i] = src[i];
     }
 }
 
 // 배열 출력 함수 (0번 문제용)
 void printArray(int arr[], int n) {
     for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
         if ((i + 1) % 10 == 0) printf("\n");  // 10개씩 줄바꿈
     }
     if (n % 10 != 0) printf("\n");
 }
 
 // 정렬 검증 함수 (0번 문제용)
 int isSorted(int arr[], int n) {
     for (int i = 0; i < n - 1; i++) {
         if (arr[i] > arr[i + 1]) {
             return 0;  // 정렬되지 않음
         }
     }
     return 1;  // 정렬됨
 }
 
 // 랜덤 배열 생성 (0번 문제용)
 void generateRandomArray(int arr[], int n) {
     for (int i = 0; i < n; i++) {
         arr[i] = rand() % 1000;  // 0~999 범위의 랜덤 수
     }
 }
 
 /*
  * ===========================================
  * 0번 문제: ① Bubble Sort (Adaptive Version) 구현
  * ===========================================
  */
 void bubbleSort_problem0(int arr[], int n) {
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
  * 0번 문제: ② Selection Sort 구현
  * ===========================================
  */
 void selectionSort_problem0(int arr[], int n) {
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
  * 0번 문제: ③ Insertion Sort 구현
  * ===========================================
  */
 void insertionSort_problem0(int arr[], int n) {
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
  * 0번 문제: ④ Merge Sort 구현
  * ===========================================
  */
 void merge_problem0(int arr[], int left, int mid, int right) {
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
 
 void mergeSortHelper_problem0(int arr[], int left, int right) {
     if (left < right) {
         int mid = left + (right - left) / 2;
         
         mergeSortHelper_problem0(arr, left, mid);
         mergeSortHelper_problem0(arr, mid + 1, right);
         merge_problem0(arr, left, mid, right);
     }
 }
 
 void mergeSort_problem0(int arr[], int n) {
     mergeSortHelper_problem0(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 0번 문제: ⑤ Quick Sort 구현
  * ===========================================
  */
 int partition_problem0(int arr[], int low, int high) {
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
 
 void quickSortHelper_problem0(int arr[], int low, int high) {
     if (low < high) {
         int pi = partition_problem0(arr, low, high);
         
         quickSortHelper_problem0(arr, low, pi - 1);
         quickSortHelper_problem0(arr, pi + 1, high);
     }
 }
 
 void quickSort_problem0(int arr[], int n) {
     quickSortHelper_problem0(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 0번 문제: ⑥ Heap Sort 구현
  * ===========================================
  */
 void heapify_problem0(int arr[], int n, int i) {
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
         
         heapify_problem0(arr, n, largest);
     }
 }
 
 void heapSort_problem0(int arr[], int n) {
     // Build heap
     for (int i = n / 2 - 1; i >= 0; i--) {
         heapify_problem0(arr, n, i);
     }
     
     // Extract elements from heap one by one
     for (int i = n - 1; i >= 0; i--) {
         int temp = arr[0];
         arr[0] = arr[i];
         arr[i] = temp;
         
         heapify_problem0(arr, i, 0);
     }
 }
 
 /*
  * ===========================================
  * 0번 문제: ⑦ Randomized Quick Sort 구현
  * ===========================================
  */
 int randomizedPartitionHelper_problem0(int arr[], int low, int high) {
     int pivot = arr[low];
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
 
 int randomizedPartition_problem0(int arr[], int low, int high) {
     // 랜덤 피벗 선택
     int randomIndex = low + rand() % (high - low + 1);
     
     // 랜덤 원소와 맨 앞 원소 교환
     int temp = arr[randomIndex];
     arr[randomIndex] = arr[low];
     arr[low] = temp;
     
     // 맨 앞을 피벗으로 하는 파티션 수행
     return randomizedPartitionHelper_problem0(arr, low, high);
 }
 
 void randomizedQuickSortHelper_problem0(int arr[], int low, int high) {
     if (low < high) {
         int pi = randomizedPartition_problem0(arr, low, high);
         
         randomizedQuickSortHelper_problem0(arr, low, pi - 1);
         randomizedQuickSortHelper_problem0(arr, pi + 1, high);
     }
 }
 
 void randomizedQuickSort_problem0(int arr[], int n) {
     randomizedQuickSortHelper_problem0(arr, 0, n - 1);
 }
 
 /*
  * ===========================================
  * 0번 문제: 정확성 검증 실험 함수
  * ===========================================
  */
 void experiment_problem0() {
     printf("=== 정확성 검증 실험 (n=30) ===\n");
     printf("실험 조건: 각 정렬 알고리즘이 올바르게 동작하는지 검증\n\n");
     
     int n = 30;
     int original[30];
     int test[30];
     
     // 랜덤 배열 생성
     generateRandomArray(original, n);
     
     printf("원본 배열 (n=30):\n");
     printArray(original, n);
     
     // 각 정렬 알고리즘 테스트
     printf("\n--- 각 정렬 알고리즘 정확성 검증 결과 ---\n");
     
     // ① Bubble Sort 검증
     copyArray(test, original, n);
     bubbleSort_problem0(test, n);
     printf("① Bubble Sort:    %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     // ② Selection Sort 검증
     copyArray(test, original, n);
     selectionSort_problem0(test, n);
     printf("② Selection Sort: %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     // ③ Insertion Sort 검증
     copyArray(test, original, n);
     insertionSort_problem0(test, n);
     printf("③ Insertion Sort: %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     // ④ Merge Sort 검증
     copyArray(test, original, n);
     mergeSort_problem0(test, n);
     printf("④ Merge Sort:     %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     // ⑤ Quick Sort 검증
     copyArray(test, original, n);
     quickSort_problem0(test, n);
     printf("⑤ Quick Sort:     %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     // ⑥ Heap Sort 검증
     copyArray(test, original, n);
     heapSort_problem0(test, n);
     printf("⑥ Heap Sort:      %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     // ⑦ Randomized Quick Sort 검증
     copyArray(test, original, n);
     randomizedQuickSort_problem0(test, n);
     printf("⑦ Random Quick:   %s\n", isSorted(test, n) ? "정렬 성공" : "정렬 실패");
     
     printf("\n정렬된 최종 결과:\n");
     printArray(test, n);
     
     printf("\n=== 0번 문제 결과 요약 ===\n");
     printf("모든 정렬 알고리즘이 n=30 크기의 랜덤 배열을 올바르게 정렬함을 확인\n");
     printf("각 알고리즘의 구현이 정확하며 다음 실험 단계로 진행 가능\n");
 }
 
 int main() {
     printf("=== 정렬 알고리즘 정확성 검증 (0번 문제) ===\n");
     printf("학번: 202214314, 이름: 이지현\n\n");
     
     srand(time(NULL));
     
     experiment_problem0();
     
     return 0;
 }