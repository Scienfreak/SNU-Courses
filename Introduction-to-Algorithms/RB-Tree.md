# Red-Black Tree
## 레드 블랙 트리 ( BST에서 파생된 자료구조 )

### 1. RB Tree의 개념
> 탄생 배경: BST의 높이 불균형을 해결하고자 함. Balanced Tree.

#### RB Tree의 규칙 ** -> 여기서 balance가 증명된다.
  1. 모든 노드는 red or black, 두 가지 색으로 이루어진다.
  2. 루트 노드는 black이다.
  3. 모든 leaf 노드는 NIL이며 black이다.
  4. Red node의 두 자식 노드는 반드시 black node이다.
  5. 한 노드에서 어떤 leaf node에 도달하는 path는 모두 같은 black height를 지닌다.
      -> Black Height (bh(v)) -> 한 노드의 ancestor 중 black node의 개수 ( 자기자신은 세지 않는다. )

#### RB Tree의 Balance : `( v의 서브트리의 내부 노드 개수 ) >= 2 ^(h/2) - 1`이다. 따라서 h = O(logn).
// Todo
