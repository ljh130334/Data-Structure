/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [과제 설명 - 문제1]
 * BST와 AVL Tree에 10만~100만 범위의 랜덤 데이터를 insert/find하여 시간 복잡도를 실험적으로 비교하는 프로그램
 * 
 * 실험 내용:
 * - 10만, 20만, ..., 100만까지 각 크기별로 랜덤 insert 10만번 수행
 * - 각 크기별로 랜덤 find 10만번 수행
 * - 1회 평균 수행시간 측정 및 시간 복잡도 분석
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 // BST 노드 구조체
 typedef struct BSTNode {
     int data;
     struct BSTNode* left;
     struct BSTNode* right;
 } BSTNode;
 
 // AVL 노드 구조체 (높이 정보 추가)
 typedef struct AVLNode {
     int data;
     int height;
     struct AVLNode* left;
     struct AVLNode* right;
 } AVLNode;
 
 /*
  * ===========================================
  * 문제1: BST 관련 함수들
  * ===========================================
  */
 
 // BST 노드 생성
 BSTNode* createBSTNode(int data) {
     BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
     newNode->data = data;
     newNode->left = NULL;
     newNode->right = NULL;
     return newNode;
 }
 
 // BST Insert 함수
 BSTNode* bstInsert(BSTNode* root, int data) {
     if (root == NULL) {
         return createBSTNode(data);
     }
     
     if (data < root->data) {
         root->left = bstInsert(root->left, data);
     } else if (data > root->data) {
         root->right = bstInsert(root->right, data);
     }
     // 중복값은 무시
     
     return root;
 }
 
 // BST Find 함수
 BSTNode* bstFind(BSTNode* root, int data) {
     if (root == NULL || root->data == data) {
         return root;
     }
     
     if (data < root->data) {
         return bstFind(root->left, data);
     } else {
         return bstFind(root->right, data);
     }
 }
 
 // BST 메모리 해제
 void freeBST(BSTNode* root) {
     if (root != NULL) {
         freeBST(root->left);
         freeBST(root->right);
         free(root);
     }
 }
 
 /*
  * ===========================================
  * 문제1: AVL Tree 관련 함수들
  * ===========================================
  */
 
 // AVL 노드 생성
 AVLNode* createAVLNode(int data) {
     AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
     newNode->data = data;
     newNode->height = 1;
     newNode->left = NULL;
     newNode->right = NULL;
     return newNode;
 }
 
 // 높이 반환 함수
 int getHeight(AVLNode* node) {
     if (node == NULL) return 0;
     return node->height;
 }
 
 // 균형 인수 계산
 int getBalance(AVLNode* node) {
     if (node == NULL) return 0;
     return getHeight(node->left) - getHeight(node->right);
 }
 
 // 높이 업데이트
 void updateHeight(AVLNode* node) {
     if (node != NULL) {
         int leftHeight = getHeight(node->left);
         int rightHeight = getHeight(node->right);
         node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
     }
 }
 
 // 우회전 (Right Rotation)
 AVLNode* rotateRight(AVLNode* y) {
     AVLNode* x = y->left;
     AVLNode* T2 = x->right;
     
     // 회전 수행
     x->right = y;
     y->left = T2;
     
     // 높이 업데이트
     updateHeight(y);
     updateHeight(x);
     
     return x;
 }
 
 // 좌회전 (Left Rotation)
 AVLNode* rotateLeft(AVLNode* x) {
     AVLNode* y = x->right;
     AVLNode* T2 = y->left;
     
     // 회전 수행
     y->left = x;
     x->right = T2;
     
     // 높이 업데이트
     updateHeight(x);
     updateHeight(y);
     
     return y;
 }
 
 // AVL Insert 함수
 AVLNode* avlInsert(AVLNode* root, int data) {
     // 1. 일반적인 BST 삽입
     if (root == NULL) {
         return createAVLNode(data);
     }
     
     if (data < root->data) {
         root->left = avlInsert(root->left, data);
     } else if (data > root->data) {
         root->right = avlInsert(root->right, data);
     } else {
         // 중복값은 무시
         return root;
     }
     
     // 2. 높이 업데이트
     updateHeight(root);
     
     // 3. 균형 인수 확인
     int balance = getBalance(root);
     
     // 4. 불균형 상태면 회전으로 균형 조정
     // Left Left Case
     if (balance > 1 && data < root->left->data) {
         return rotateRight(root);
     }
     
     // Right Right Case
     if (balance < -1 && data > root->right->data) {
         return rotateLeft(root);
     }
     
     // Left Right Case
     if (balance > 1 && data > root->left->data) {
         root->left = rotateLeft(root->left);
         return rotateRight(root);
     }
     
     // Right Left Case
     if (balance < -1 && data < root->right->data) {
         root->right = rotateRight(root->right);
         return rotateLeft(root);
     }
     
     return root;
 }
 
 // AVL Find 함수
 AVLNode* avlFind(AVLNode* root, int data) {
     if (root == NULL || root->data == data) {
         return root;
     }
     
     if (data < root->data) {
         return avlFind(root->left, data);
     } else {
         return avlFind(root->right, data);
     }
 }
 
 // AVL 메모리 해제
 void freeAVL(AVLNode* root) {
     if (root != NULL) {
         freeAVL(root->left);
         freeAVL(root->right);
         free(root);
     }
 }
 
 /*
  * ===========================================
  * 문제1: 큰 수 범위 랜덤 넘버 생성 함수
  * ===========================================
  */
 int generateLargeRandom(int max) {
     // rand()는 0~32767 범위이므로 큰 수를 위해 조합
     // (rand() * 111) % max 방식보다 더 균등한 분포 생성
     return (int)(((long long)rand() * rand()) % max);
 }
 
 /*
  * ===========================================
  * 문제1: 실험 함수
  * ===========================================
  */
 void experiment1_randomData() {
     printf("=== 문제1: 랜덤 데이터 실험 (10만~100만) ===\n");
     printf("실험 조건: 각 크기별로 10만번 insert/find 수행\n\n");
     
     int sizes[] = {100000, 200000, 300000, 400000, 500000, 
                    600000, 700000, 800000, 900000, 1000000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     int numOperations = 100000;
     
     printf("--- BST Random Insert 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         BSTNode* bstRoot = NULL;
         
         clock_t start = clock();
         for (int j = 0; j < numOperations; j++) {
             int data = generateLargeRandom(n);
             bstRoot = bstInsert(bstRoot, data);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / numOperations;
         
         printf("BST Insert - Range: %7d, Total: %8.4f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeBST(bstRoot);
     }
     
     printf("\n--- AVL Random Insert 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         AVLNode* avlRoot = NULL;
         
         clock_t start = clock();
         for (int j = 0; j < numOperations; j++) {
             int data = generateLargeRandom(n);
             avlRoot = avlInsert(avlRoot, data);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / numOperations;
         
         printf("AVL Insert - Range: %7d, Total: %8.4f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeAVL(avlRoot);
     }
     
     printf("\n--- BST Random Find 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         BSTNode* bstRoot = NULL;
         
         // 먼저 데이터 삽입 (트리 구성)
         for (int j = 0; j < numOperations; j++) {
             int data = generateLargeRandom(n);
             bstRoot = bstInsert(bstRoot, data);
         }
         
         // Find 성능 측정
         clock_t start = clock();
         for (int j = 0; j < numOperations; j++) {
             int data = generateLargeRandom(n);
             bstFind(bstRoot, data);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / numOperations;
         
         printf("BST Find   - Range: %7d, Total: %8.4f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeBST(bstRoot);
     }
     
     printf("\n--- AVL Random Find 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         AVLNode* avlRoot = NULL;
         
         // 먼저 데이터 삽입 (트리 구성)
         for (int j = 0; j < numOperations; j++) {
             int data = generateLargeRandom(n);
             avlRoot = avlInsert(avlRoot, data);
         }
         
         // Find 성능 측정
         clock_t start = clock();
         for (int j = 0; j < numOperations; j++) {
             int data = generateLargeRandom(n);
             avlFind(avlRoot, data);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / numOperations;
         
         printf("AVL Find   - Range: %7d, Total: %8.4f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeAVL(avlRoot);
     }
 }
 
 int main() {
     printf("=== BST vs AVL Tree 시간 복잡도 분석 (문제1) ===\n");
     
     srand(time(NULL));
     
     // 큰 수 랜덤 생성 테스트
     printf("=== 큰 수 랜덤 생성 테스트 ===\n");
     printf("0 ~ 1000000 범위에서 10개의 랜덤 숫자:\n");
     for (int i = 0; i < 10; i++) {
         printf("%d ", generateLargeRandom(1000000));
     }
     printf("\n\n");
     
     // 문제1 실험 수행
     experiment1_randomData();
     
     // 문제1 결과 요약
     printf("\n=== 문제1 실험 결과 요약 ===\n");
     printf("1. 랜덤 데이터에서 BST와 AVL 모두 평균적으로 O(log n) 성능을 보임\n");
     printf("2. AVL Tree가 BST보다 약간 느릴 수 있으나 균형 유지로 안정적 성능 보장\n");
     printf("3. 데이터 범위가 커져도 두 트리 모두 로그 시간 복잡도 유지\n");
     printf("4. 랜덤 데이터의 경우 BST도 비교적 균형잡힌 형태로 구성됨\n");
     
     return 0;
 }