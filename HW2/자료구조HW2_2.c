/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 *
 * [1-(1)번 문제: Array vs Linked List Insertion]
 *
 * <문제 설명>
 * 1) Array의 경우:
 *    - 크기가 100,000인 배열(또는 capacity 100,000)을 준비
 *    - 배열의 맨 앞(index=0)에 요소를 삽입할 때 기존 원소들을 모두 한 칸씩 이동(shift)시키는 방식으로 구현
 *    - 100,000번의 삽입 작업에 걸리는 시간을 측정하여 밀리초 단위로 출력
 *
 * 2) Linked List의 경우:
 *    - 단일 연결 리스트(singly linked list)를 이용
 *    - 매번 리스트의 head(맨 앞)에 새로운 노드를 삽입하는 방식으로 구현
 *    - 100,000번의 삽입 작업에 걸리는 시간을 측정하여 밀리초 단위로 출력
 *
 * 시간 측정은 clock() 함수를 사용하며,
 * (end - start) * 1000 / CLOCKS_PER_SEC 를 통해 밀리초 단위로 변환합니다.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 #define SIZE 100000
 
 // --------------------------------------------------------
 // 단일 연결 리스트 (Linked List) 관련 함수들
 // --------------------------------------------------------
 
 // 단일 연결 리스트의 노드 구조체 정의
 typedef struct ListNode {
     int data;
     struct ListNode* next;
 } ListNode;
 
 // 새로운 노드를 생성하는 함수
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
 
 // 연결 리스트의 head(맨 앞)에 노드를 삽입하는 함수 (O(1) 삽입)
 void insertAtHead(ListNode** head, int data) {
     ListNode* newNode = createNode(data);
     newNode->next = *head;
     *head = newNode;
 }
 
 // 연결 리스트의 메모리를 해제하는 함수
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
 // 배열 (Array) 관련 함수들
 // --------------------------------------------------------
 
 // 배열의 맨 앞(index=0)에 삽입하는 함수 (shift 연산 발생)
 // arr: 배열, length: 현재 배열의 원소 수, index: 삽입 위치, data: 삽입할 데이터
 void arrayInsert(int* arr, int* length, int index, int data) {
     // 현재 원소들을 뒤로 한 칸씩 이동시킴 (index부터 끝까지)
     for (int i = *length - 1; i >= index; i--) {
         arr[i + 1] = arr[i];
     }
     arr[index] = data;
     (*length)++;
 }
 
 // --------------------------------------------------------
 // 시간 측정 함수들
 // --------------------------------------------------------
 
 // Array에서 맨 앞 삽입 연산을 100,000번 수행하고 시간을 측정하는 함수
 void measureArrayInsertion() {
     // 삽입 후 최대 원소 수 SIZE+1 만큼 공간 확보
     int* arr = (int*)malloc((SIZE + 1) * sizeof(int));
     if (arr == NULL) {
         printf("메모리 할당 오류\n");
         exit(1);
     }
     
     int length = 0;  // 현재 배열에 들어있는 원소 수
     clock_t start = clock();
     
     for (int i = 0; i < SIZE; i++) {
         // 매번 배열의 맨 앞(index=0)에 삽입 (shift 발생)
         arrayInsert(arr, &length, 0, i);
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[1-(1)번 문제] Array 맨 앞 삽입(100,000번) 수행 시간: %d 밀리초\n", elapsed_ms);
     
     free(arr);
 }
 
 // Linked List에서 맨 앞 삽입 연산을 100,000번 수행하고 시간을 측정하는 함수
 void measureLinkedListInsertion() {
     ListNode* head = NULL;
     clock_t start = clock();
     
     for (int i = 0; i < SIZE; i++) {
         // 매번 리스트의 head(맨 앞)에 노드 삽입
         insertAtHead(&head, i);
     }
     
     clock_t end = clock();
     int elapsed_ms = (int)((end - start) * 1000 / CLOCKS_PER_SEC);
     printf("[1-(1)번 문제] Linked List 맨 앞 삽입(100,000번) 수행 시간: %d 밀리초\n", elapsed_ms);
     
     freeLinkedList(&head);
 }
 
 // --------------------------------------------------------
 // main 함수
 // --------------------------------------------------------
 int main() {
     printf("===============================================\n");
     printf("[1-(1)번 문제] Array vs Linked List Insertion\n");
     printf("===============================================\n\n");
     
     // Array 삽입 연산 시간 측정
     measureArrayInsertion();
     
     // Linked List 삽입 연산 시간 측정
     measureLinkedListInsertion();
     
     return 0;
 }