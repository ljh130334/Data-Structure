/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [과제 설명]
 * Linear search와 Binary search의 시간 복잡도를 실험적으로 비교하는 프로그램
 * - 배열은 array[i] = 2 * i 형태로 저장 (정렬된 상태)
 * - Linear search는 unordered linear search로 구현
 * - Binary search는 iteration version으로 구현
 * - 0 ~ 2*(n-1) 범위의 랜덤 숫자를 검색
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 /*
  * Unordered Linear Search 구현
  * 정렬된 배열이지만 정렬되지 않은 것처럼 처음부터 끝까지 순차 탐색
  * 시간 복잡도: O(n)
  */
 int unorderedLinearSearch(int arr[], int size, int target) {
     for (int i = 0; i < size; i++) {
         if (arr[i] == target) {
             return i;
         }
     }
     return -1;
 }
 
 /*
  * Binary Search (Iterative Version) 구현
  * 정렬된 배열에서 이진 탐색 수행
  * 시간 복잡도: O(log n)
  */
 int binarySearchIterative(int arr[], int size, int target) {
     int low = 0;
     int high = size - 1;
     
     while (low <= high) {
         int mid = (low + high) / 2;
         
         if (arr[mid] == target) {
             return mid;
         } else if (arr[mid] < target) {
             low = mid + 1;
         } else {
             high = mid - 1;
         }
     }
     return -1;
 }
 
 /*
  * 배열 생성 함수
  * array[i] = 2 * i 형태로 데이터 저장
  */
 void createArray(int arr[], int size) {
     for (int i = 0; i < size; i++) {
         arr[i] = 2 * i;
     }
 }
 
 int main() {
     printf("=== Linear Search vs Binary Search 시간 복잡도 분석 ===\n");
     printf("학번: 202214314, 이름: 이지현\n\n");
     
     // 실험할 배열 크기 설정 (100만 ~ 1000만)
     int sizes[] = {1000000, 2000000, 3000000, 4000000, 5000000, 
                    6000000, 7000000, 8000000, 9000000, 10000000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     
     srand(time(NULL));  // 랜덤 시드 초기화
     
     // rand() 함수 테스트 (과제 요구사항)
     printf("=== rand() 함수 테스트 ===\n");
     printf("0 ~ 20 범위에서 10개의 랜덤 숫자 생성:\n");
     for (int i = 0; i < 10; i++) {
         printf("%d ", rand() % 21);
     }
     printf("\n\n");
     
     // Linear Search 실험
     printf("=== (1) Linear Search Time Complexity ===\n");
     printf("실험 조건: 각 크기별로 1000번 검색 수행\n\n");
     
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         int* arr = (int*)malloc(sizeof(int) * n);
         
         // 배열 생성 (array[i] = 2 * i)
         createArray(arr, n);
         
         // 1000번 검색 수행
         int numSearches = 1000;
         clock_t start = clock();
         
         for (int j = 0; j < numSearches; j++) {
             int target = rand() % (2 * n);  // 0 ~ 2*(n-1) 범위
             unorderedLinearSearch(arr, n, target);
         }
         
         clock_t end = clock();
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / numSearches;
         
         printf("Array size: %10d, Total time: %8.4f sec, Avg time per search: %10.8f sec\n", 
                n, totalTime, avgTime);
         
         free(arr);
     }
     
     // Binary Search 실험
     printf("\n=== (2) Binary Search Time Complexity ===\n");
     printf("실험 조건: 각 크기별로 1,000,000번 검색 수행\n\n");
     
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         int* arr = (int*)malloc(sizeof(int) * n);
         
         // 배열 생성 (array[i] = 2 * i)
         createArray(arr, n);
         
         // 1,000,000번 검색 수행
         int numSearches = 1000000;
         clock_t start = clock();
         
         for (int j = 0; j < numSearches; j++) {
             int target = rand() % (2 * n);  // 0 ~ 2*(n-1) 범위
             binarySearchIterative(arr, n, target);
         }
         
         clock_t end = clock();
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / numSearches;
         
         printf("Array size: %10d, Total time: %8.4f sec, Avg time per search: %10.8f sec\n", 
                n, totalTime, avgTime);
         
         free(arr);
     }
     
     // 결과 요약 및 분석
     printf("\n=== 결과 분석 ===\n");
     printf("1. Linear Search: 배열 크기에 비례하여 검색 시간 증가 (O(n))\n");
     printf("2. Binary Search: 배열 크기에 로그 비례하여 검색 시간 증가 (O(log n))\n");
     printf("3. 대용량 데이터에서 Binary Search가 Linear Search보다 훨씬 효율적\n");
     
     return 0;
 }