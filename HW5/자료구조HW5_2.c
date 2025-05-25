/*
 * 학번: 202214314
 * 이름: 이지현
 * 실행환경: Mac
 * 
 * [과제 설명 - 문제2]
 * BST와 AVL Tree에 1, 2, 3, ..., n까지의 순차 데이터를 insert한 후 랜덤 find를 수행하여 시간 복잡도를 실험적으로 비교하는 프로그램
 * 
 * 실험 내용:
 * - 1000, 2000, 3000, 4000, 5000까지 각 크기별로 순차 insert 수행
 * - 각 크기별로 랜덤 find n번 수행
 * - 1회 평균 수행시간 측정 및 시간 복잡도 분석
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <math.h>
 
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
  * 문제2: BST 관련 함수들
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
  * 문제2: AVL Tree 관련 함수들
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
  * 문제2: 실험 함수
  * ===========================================
  */
 void experiment2_sequentialData() {
     printf("=== 문제2: 순차 데이터 실험 (1000~5000) ===\n");
     printf("실험 조건: 1, 2, 3, ..., n까지 순차 insert 후 n번 랜덤 find 수행\n\n");
     
     int sizes[] = {1000, 2000, 3000, 4000, 5000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     
     printf("--- BST Sequential Insert 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         BSTNode* bstRoot = NULL;
         
         clock_t start = clock();
         for (int j = 1; j <= n; j++) {
             bstRoot = bstInsert(bstRoot, j);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / n;
         
         printf("BST Sequential Insert - Size: %4d, Total: %8.6f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeBST(bstRoot);
     }
     
     printf("\n--- AVL Sequential Insert 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         AVLNode* avlRoot = NULL;
         
         clock_t start = clock();
         for (int j = 1; j <= n; j++) {
             avlRoot = avlInsert(avlRoot, j);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / n;
         
         printf("AVL Sequential Insert - Size: %4d, Total: %8.6f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeAVL(avlRoot);
     }
     
     printf("\n--- BST Sequential Find 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         BSTNode* bstRoot = NULL;
         
         // 먼저 순차적으로 데이터 삽입 (1, 2, 3, ..., n)
         for (int j = 1; j <= n; j++) {
             bstRoot = bstInsert(bstRoot, j);
         }
         
         // 랜덤 Find 성능 측정 (1~n 범위에서 n번)
         clock_t start = clock();
         for (int j = 0; j < n; j++) {
             int data = (rand() % n) + 1;  // 1~n 범위
             bstFind(bstRoot, data);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / n;
         
         printf("BST Sequential Find   - Size: %4d, Total: %8.6f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeBST(bstRoot);
     }
     
     printf("\n--- AVL Sequential Find 성능 측정 ---\n");
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         AVLNode* avlRoot = NULL;
         
         // 먼저 순차적으로 데이터 삽입 (1, 2, 3, ..., n)
         for (int j = 1; j <= n; j++) {
             avlRoot = avlInsert(avlRoot, j);
         }
         
         // 랜덤 Find 성능 측정 (1~n 범위에서 n번)
         clock_t start = clock();
         for (int j = 0; j < n; j++) {
             int data = (rand() % n) + 1;  // 1~n 범위
             avlFind(avlRoot, data);
         }
         clock_t end = clock();
         
         double totalTime = ((double)(end - start)) / CLOCKS_PER_SEC;
         double avgTime = totalTime / n;
         
         printf("AVL Sequential Find   - Size: %4d, Total: %8.6f sec, Avg: %12.10f sec\n", 
                n, totalTime, avgTime);
         
         freeAVL(avlRoot);
     }
 }
 
 /*
  * ===========================================
  * 문제2: 트리 구조 분석 함수 (선택적)
  * ===========================================
  */
 int getBSTDepth(BSTNode* root) {
     if (root == NULL) return 0;
     int leftDepth = getBSTDepth(root->left);
     int rightDepth = getBSTDepth(root->right);
     return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
 }
 
 int getAVLDepth(AVLNode* root) {
     if (root == NULL) return 0;
     return root->height;
 }
 
 void analyzeTreeStructure() {
     printf("\n=== 트리 구조 분석 (순차 데이터 삽입 시) ===\n");
     
     int sizes[] = {1000, 2000, 3000, 4000, 5000};
     int numSizes = sizeof(sizes) / sizeof(sizes[0]);
     
     for (int i = 0; i < numSizes; i++) {
         int n = sizes[i];
         
         // BST 구조 분석
         BSTNode* bstRoot = NULL;
         for (int j = 1; j <= n; j++) {
             bstRoot = bstInsert(bstRoot, j);
         }
         int bstDepth = getBSTDepth(bstRoot);
         
         // AVL 구조 분석
         AVLNode* avlRoot = NULL;
         for (int j = 1; j <= n; j++) {
             avlRoot = avlInsert(avlRoot, j);
         }
         int avlDepth = getAVLDepth(avlRoot);
         
         printf("Size: %4d, BST Depth: %4d (이론적 최악: %4d), AVL Depth: %4d (이론적 최적: %.1f)\n", 
                n, bstDepth, n, avlDepth, log2(n) + 1);
         
         freeBST(bstRoot);
         freeAVL(avlRoot);
     }
 }
 
 int main() {
     printf("=== BST vs AVL Tree 시간 복잡도 분석 (문제2) ===\n");
     
     srand(time(NULL));
     
     // 랜덤 함수 테스트
     printf("=== 랜덤 함수 테스트 ===\n");
     printf("1 ~ 1000 범위에서 10개의 랜덤 숫자:\n");
     for (int i = 0; i < 10; i++) {
         printf("%d ", (rand() % 1000) + 1);
     }
     printf("\n\n");
     
     // 문제2 실험 수행
     experiment2_sequentialData();
     
     // 트리 구조 분석 (선택적)
     analyzeTreeStructure();
     
     // 문제2 결과 요약
     printf("\n=== 문제2 실험 결과 요약 ===\n");
     printf("1. 순차 데이터 Insert:\n");
     printf("   - BST: O(n) - 완전히 불균형한 일자형 트리 구조\n");
     printf("   - AVL: O(log n) - 균형 유지로 안정적 성능\n");
     printf("2. 순차 데이터 Find:\n");
     printf("   - BST: O(n) - 최악의 경우 모든 노드 탐색\n");
     printf("   - AVL: O(log n) - 균형잡힌 구조로 효율적 탐색\n");
     printf("3. BST는 데이터 입력 순서에 따라 성능이 크게 좌우됨\n");
     printf("4. AVL Tree는 입력 순서와 관계없이 안정적 성능 보장\n");
     
     return 0;
 }