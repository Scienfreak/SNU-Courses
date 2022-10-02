# Memory Hierarchy

CPU와 Memory는 data를 read, write 하는 방식으로 소통한다.

이때 문제는 data access speed.

용량이 큰 hard disk는 접근 속도가 느리고, 접근 속도가 빠른 RAM이나 Cache는 용량이 작다.

-> 해결: 여러 종류의 메모리들로 계층을 구성한다.

    그럼 자주 쓰는 data를 CPU에서 가까운 Memory에 넣어 하위 메모리로의 접근을 줄일 수 있다. -> 이게 포인트.
    
### Caching!!! Locality Principle : 자주 쓰는 data를 고르는 규칙 ( 중요 )
  - Temporal Locality (시간): 한 번 쓴 data는 또 사용할 확률이 높다.
  - Spatial Locality (공간) : 사용된 데이터에 가까이 위치한 데이터는 사용될 확률이 높다.
        -> Spatial Locality를 만족하기 위해 data를 caching 할 때 그 data의 주변 data도 함께 load한다.
        
