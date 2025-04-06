/*
 * 파일명: FinalExperiment.c
 * (학번, 이름, 실행환경 등 필요 정보 기재)
 *
 * [문제: 각 operation(insert, delete, read)의 time complexity 실험]
 *
 * - 데이터 구조: Array, Linked List
 * - 데이터 크기(n): 10,000 ~ 100,000 (10,000 간격)
 * - 연산:
 *   1) Insert: n번 반복 삽입 (예: 배열은 맨 앞 삽입, 연결 리스트도 맨 앞 삽입)
 *   2) Delete: n번 반복 삭제 (예: 랜덤 인덱스 삭제)
 *   3) Read:   n번 랜덤 접근 (랜덤 인덱스의 원소 읽기)
 * - 측정 방식: clock() 함수로 시작/끝 시간을 측정, 밀리초(ms)로 환산
 * - 결과: n과 수행 시간의 관계를 표나 그래프로 나타내고, 
 *         실제 측정 결과를 통해 시간 복잡도를 비교/분석
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 // ------------------------- 공통 설정 -------------------------
 #define NUM_TESTS 10
 // 예: 10,000 ~ 100,000 (10,000 간격)
 static int sizes[NUM_TESTS] = {10000, 20000, 30000, 40000, 50000,
                                60000, 70000, 80000, 90000, 100000};
 
 // ------------------------- Linked List 정의 -------------------------
 typedef struct ListNode {
     int data;
     struct ListNode* next;
 } ListNode;
 
 ListNode* createNode(int data) {
     ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
     if (!newNode) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     newNode->data = data;
     newNode->next = NULL;
     return newNode;
 }
 
 // 연결 리스트 맨 앞에 삽입 (Insert)
 void insertAtHead(ListNode** head, int data) {
     ListNode* newNode = createNode(data);
     newNode->next = *head;
     *head = newNode;
 }
 
 // 연결 리스트 끝에 삽입
 void insertAtEnd(ListNode** head, int data) {
     ListNode* newNode = createNode(data);
     if (*head == NULL) {
         *head = newNode;
         return;
     }
     ListNode* cur = *head;
     while (cur->next != NULL) {
         cur = cur->next;
     }
     cur->next = newNode;
 }
 
 // 연결 리스트에서 index 위치 노드 삭제
 void deleteAtIndex(ListNode** head, int index) {
     if (index == 0) {
         ListNode* temp = *head;
         *head = (*head)->next;
         free(temp);
         return;
     }
     ListNode* cur = *head;
     for (int i = 0; i < index - 1; i++) {
         cur = cur->next;
     }
     ListNode* toDelete = cur->next;
     cur->next = toDelete->next;
     free(toDelete);
 }
 
 // 연결 리스트 해제
 void freeLinkedList(ListNode** head) {
     ListNode* cur = *head;
     while (cur) {
         ListNode* temp = cur;
         cur = cur->next;
         free(temp);
     }
     *head = NULL;
 }
 
 // ------------------------- 1) Insert 측정 함수 -------------------------
 
 // (1-A) 배열에서 n번 '맨 앞 삽입'
 void measureInsertionArray(int n) {
     // 배열의 최대 크기를 n으로 가정(또는 n+1)
     int* arr = (int*)malloc((n + 1) * sizeof(int));
     if (!arr) {
         printf("메모리 할당 오류\n");
         return;
     }
     int length = 0;  // 현재 배열에 들어있는 원소 수
     
     clock_t start = clock();
     for (int i = 0; i < n; i++) {
         // 맨 앞 삽입 -> shift 발생
         // 뒤에서부터 앞으로 이동
         for (int j = length - 1; j >= 0; j--) {
             arr[j + 1] = arr[j];
         }
         arr[0] = i; // 새 원소 삽입
         length++;
     }
     clock_t end = clock();
     
     int elapsed = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[Array Insert] n=%d, time=%d ms\n", n, elapsed);
     
     free(arr);
 }
 
 // (1-B) 연결 리스트에서 n번 '맨 앞 삽입'
 void measureInsertionLinkedList(int n) {
     ListNode* head = NULL;
     
     clock_t start = clock();
     for (int i = 0; i < n; i++) {
         insertAtHead(&head, i);
     }
     clock_t end = clock();
     
     int elapsed = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[LinkedList Insert] n=%d, time=%d ms\n", n, elapsed);
     
     freeLinkedList(&head);
 }
 
 // ------------------------- 2) Delete 측정 함수 -------------------------
 
 // (2-A) 배열에서 n번 '랜덤 삭제'
 void measureDeletionArray(int n) {
     // 초기 배열: 0 ~ (n-1)
     int* arr = (int*)malloc(n * sizeof(int));
     if (!arr) {
         printf("메모리 할당 오류\n");
         return;
     }
     for (int i = 0; i < n; i++) {
         arr[i] = i;
     }
     int length = n;
     
     srand((unsigned int)time(NULL)); // 랜덤 시드
     
     clock_t start = clock();
     for (int i = 0; i < n; i++) {
         int index = rand() % length;
         // index 위치 삭제 -> shift
         for (int j = index; j < length - 1; j++) {
             arr[j] = arr[j + 1];
         }
         length--;
     }
     clock_t end = clock();
     
     int elapsed = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[Array Delete] n=%d, time=%d ms\n", n, elapsed);
     
     free(arr);
 }
 
 // (2-B) 연결 리스트에서 n번 '랜덤 삭제'
 void measureDeletionLinkedList(int n) {
     // 초기 리스트: 0 ~ (n-1)
     ListNode* head = NULL;
     for (int i = 0; i < n; i++) {
         insertAtEnd(&head, i);
     }
     int length = n;
     
     srand((unsigned int)time(NULL));
     
     clock_t start = clock();
     for (int i = 0; i < n; i++) {
         int index = rand() % length;
         deleteAtIndex(&head, index);
         length--;
     }
     clock_t end = clock();
     
     int elapsed = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[LinkedList Delete] n=%d, time=%d ms\n", n, elapsed);
     
     freeLinkedList(&head);
 }
 
 // ------------------------- 3) Read 측정 함수 -------------------------
 
 // (3-A) 배열에서 n번 '랜덤 읽기'
 void measureReadArray(int n) {
     // 배열 생성: 0 ~ (n-1)
     int* arr = (int*)malloc(n * sizeof(int));
     if (!arr) {
         printf("메모리 할당 오류\n");
         return;
     }
     for (int i = 0; i < n; i++) {
         arr[i] = i;
     }
     
     srand((unsigned int)time(NULL));
     
     long long sum = 0; // 오버플로 방지용
     clock_t start = clock();
     for (int i = 0; i < n; i++) {
         int index = rand() % n;
         sum += arr[index];
     }
     clock_t end = clock();
     
     int elapsed = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[Array Read] n=%d, time=%d ms\n", n, elapsed);
     
     // printf("sum=%lld\n", sum); // 최적화 방지용 (필요시)
     free(arr);
 }
 
 // (3-B) 연결 리스트에서 n번 '랜덤 읽기'
 void measureReadLinkedList(int n) {
     // 연결 리스트 생성: 0 ~ (n-1)
     ListNode* head = NULL;
     for (int i = 0; i < n; i++) {
         insertAtEnd(&head, i);
     }
     
     srand((unsigned int)time(NULL));
     
     long long sum = 0;
     clock_t start = clock();
     for (int i = 0; i < n; i++) {
         int index = rand() % n;
         // index까지 이동
         ListNode* cur = head;
         for (int j = 0; j < index; j++) {
             cur = cur->next;
         }
         sum += cur->data;
     }
     clock_t end = clock();
     
     int elapsed = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[LinkedList Read] n=%d, time=%d ms\n", n, elapsed);
     
     // printf("sum=%lld\n", sum);
     freeLinkedList(&head);
 }
 
 // ------------------------- main 함수 -------------------------
 int main() {
     printf("===============================================\n");
     printf("[2번 문제] 배열 vs 연결 리스트 연산별 Time Complexity 실험\n");
     printf("===============================================\n\n");
     
     // sizes 배열에 정의된 n 값들에 대해, 모든 연산을 측정
     for (int i = 0; i < NUM_TESTS; i++) {
         int n = sizes[i];
         
         // 1) Insert
         measureInsertionArray(n);
         measureInsertionLinkedList(n);
         
         // 2) Delete
         measureDeletionArray(n);
         measureDeletionLinkedList(n);
         
         // 3) Read
         measureReadArray(n);
         measureReadLinkedList(n);
         
         printf("------------------------------------------------\n");
     }
     
     return 0;
 }