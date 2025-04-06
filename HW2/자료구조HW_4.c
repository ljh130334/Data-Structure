/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [1-(3)번 문제: Array vs Linked List Random Access (Deletion)]
 *
 * <문제 설명>
 * 1) Array:
 *    - 크기가 100,000인 배열을 준비하고 0 ~ 99,999로 초기화
 *    - 100,000번 반복하면서 매번 rand() % 현재길이 로 삭제할 인덱스를 고른 뒤,
 *      해당 원소를 삭제하고 뒤의 원소들을 한 칸씩 shift
 *    - 전체 걸린 시간을 밀리초 단위로 측정
 *
 * 2) Linked List:
 *    - 단일 연결 리스트를 0 ~ 99,999로 초기화 (노드 100,000개)
 *    - 100,000번 반복하면서 매번 rand() % 현재길이 로 삭제할 인덱스를 고른 뒤,
 *      순차 접근으로 그 노드를 찾아 삭제
 *    - 전체 걸린 시간을 밀리초 단위로 측정
 *
 * 시간 측정은 clock() 함수를 사용하며,
 * (end - start) * 1000 / CLOCKS_PER_SEC 로 밀리초 단위로 변환합니다.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 #define SIZE 100000 // 초기 배열/리스트 크기 (0 ~ 99,999)
 #define NUM_DELETE 100000 // 삭제 횟수 (100,000번)
 
 // --------------------------------------------------------
 // 연결 리스트 (Linked List) 관련 구조체 및 함수
 // --------------------------------------------------------
 typedef struct ListNode {
     int data;
     struct ListNode* next;
 } ListNode;
 
 // 새 노드를 생성하는 함수
 ListNode* createNode(int data) {
     ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
     if (newNode == NULL) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     newNode->data = data;
     newNode->next = NULL;
     return newNode;
 }
 
 // 연결 리스트의 끝에 노드를 추가 (0 ~ 99,999로 초기화 시 사용)
 void insertAtEnd(ListNode** head, int data) {
     ListNode* newNode = createNode(data);
     if (*head == NULL) {
         *head = newNode;
         return;
     }
     ListNode* current = *head;
     while (current->next != NULL) {
         current = current->next;
     }
     current->next = newNode;
 }
 
 // 연결 리스트에서 index 위치의 노드를 삭제하는 함수
 void deleteAtIndex(ListNode** head, int index) {
     // index = 0이면 head 삭제
     if (index == 0) {
         ListNode* temp = *head;
         *head = (*head)->next;
         free(temp);
         return;
     }
     
     // index번째 노드를 찾기 위해 (index-1)번째 노드까지 이동
     ListNode* current = *head;
     for (int i = 0; i < index - 1; i++) {
         current = current->next;
     }
     
     // current->next가 삭제 대상 노드
     ListNode* nodeToDelete = current->next;
     current->next = nodeToDelete->next;
     free(nodeToDelete);
 }
 
 // 연결 리스트 메모리를 해제
 void freeLinkedList(ListNode** head) {
     ListNode* current = *head;
     while (current != NULL) {
         ListNode* temp = current;
         current = current->next;
         free(temp);
     }
     *head = NULL;
 }
 
 // --------------------------------------------------------
 // 배열(Array) 관련 함수
 // --------------------------------------------------------
 
 // 배열에서 index 위치의 원소를 삭제하고, 뒤의 원소들을 한 칸씩 shift
 void arrayDeleteAt(int* arr, int* length, int index) {
     // index 이후의 요소들을 앞으로 한 칸씩 복사
     for (int i = index; i < (*length) - 1; i++) {
         arr[i] = arr[i + 1];
     }
     (*length)--;
 }
 
 // --------------------------------------------------------
 // 삭제 연산 시간 측정 함수 (Array)
 // --------------------------------------------------------
 void measureArrayRandomDeletion() {
     // 배열 생성 및 초기화
     int* arr = (int*)malloc(SIZE * sizeof(int));
     if (arr == NULL) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     for (int i = 0; i < SIZE; i++) {
         arr[i] = i;
     }
     
     int currentLength = SIZE;
     
     // 랜덤 시드 설정
     srand((unsigned int)time(NULL));
     
     clock_t start = clock();
     
     // NUM_DELETE(100,000)번 삭제
     for (int i = 0; i < NUM_DELETE; i++) {
         int index = rand() % currentLength; // 현재 길이 범위 내에서 랜덤 인덱스
         arrayDeleteAt(arr, &currentLength, index);
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     
     printf("[1-(3)번 문제] Array 랜덤 삭제 (100,000번) 수행 시간: %d 밀리초\n", elapsed_ms);
     
     free(arr);
 }
 
 // --------------------------------------------------------
 // 삭제 연산 시간 측정 함수 (Linked List)
 // --------------------------------------------------------
 void measureLinkedListRandomDeletion() {
     // 연결 리스트 생성 및 초기화
     ListNode* head = NULL;
     for (int i = 0; i < SIZE; i++) {
         insertAtEnd(&head, i);
     }
     
     // 랜덤 시드 설정
     srand((unsigned int)time(NULL));
     
     clock_t start = clock();
     
     // NUM_DELETE(100,000)번 삭제
     int currentLength = SIZE;
     for (int i = 0; i < NUM_DELETE; i++) {
         int index = rand() % currentLength; // 현재 길이 범위 내에서 랜덤 인덱스
         deleteAtIndex(&head, index);
         currentLength--;
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     
     printf("[1-(3)번 문제] Linked List 랜덤 삭제 (100,000번) 수행 시간: %d 밀리초\n", elapsed_ms);
     
     freeLinkedList(&head);
 }
 
 // --------------------------------------------------------
 // main 함수
 // --------------------------------------------------------
 int main() {
     printf("===============================================\n");
     printf("[1-(3)번 문제] Array vs Linked List Random Access (Deletion)\n");
     printf("===============================================\n\n");
     
     // Array에서 랜덤 삭제
     measureArrayRandomDeletion();
     
     // Linked List에서 랜덤 삭제
     measureLinkedListRandomDeletion();
     
     return 0;
 }