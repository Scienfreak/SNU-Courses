# Binary Search Tree

## 이진 탐색 트리

### 1. 이진 탐색 트리의 개념
이진 탐색 트리는 다음 규칙을 만족하는 이진 트리를 말한다.
1. Left-child of the node is smaller than its parent, and right-child of the node is bigger than its parent.
2. Every nodes in left subtree of the node is smaller than the node, and every nodes in right subtree of the node is bigger than the node. 



### 2. Operations of BST (with its implementation)
#### 1. 탐색 ( Searching )

트리 탐색에는 세 가지 방식이 있다.
  - Preorder: this -> left -> right 순으로 탐색한다.
  - Inorder: left -> this -> right 순으로 탐색한다.
  - Postorder: left -> right -> this 순으로 탐색한다.

BST에서는 inorder 탐색을 해야 노드들을 크기 순서대로 탐색할 수 있다.

  // TODO [그림과 의사코드 넣기]


#### 2. Minimum and Maximum
  - Minimum: BST에서 가장 왼쪽에 있는 노드가 최솟값이다.
  - Maximum: BST에서 가장 오른쪽에 있는 노드가 최댓값이다.


#### 3. Successor and Predecessor
  - Successor: 트리 내에서 현재 노드 바로 다음(으로 큰) 값, 오른쪽 서브트리의 최솟값이다.
  - Predecessor: 트리 내에서 현재 노드 바로 이전 값, 왼쪽 서브트리의 최댓값이다.

*** 이때, successor는 오른쪽 서브트리의 가장 왼쪽 노드이므로 반드시 왼쪽 child가 없다. -> Deletion에서 활용한다.


#### 4. Insertion
탐색하여 leaf 자리에 노드를 삽입한다. 이때 반드시 새로 삽입된 노드는 leaf node가 된다.


#### 5. Deletion
삭제는 조금 복잡하다. 다음 경우들을 따져봐야 한다.
  1. 삭제하려는 노드의 한 쪽 child가 없는 경우 ( 혹은 양쪽 모두 없는 경우 )

  2. Successor가 삭제하려는 노드의 right child인 경우
    -> Successor 노드를 삭제하려는 노드의 위치에 그대로 삽입한다. ( 부모와 왼쪽 자식 연결 )
  
  3. Successor가 삭제하려는 노드의 right child가 아닌 경우 ( 가장 일반적인 경우 )
    -> Successor의 right child를 successor node의 자리에 삽입한다.
    -> Successor node를 삽입하려는 노드의 위치에 삽입한다. ( 오른쪽 자식, 부모와 왼쪽 자식 연결 )

---

# 0. Terminology
- Node
- Edge
- Child
- Parent
- Root node
- Leaf node
- Depth
- Height
