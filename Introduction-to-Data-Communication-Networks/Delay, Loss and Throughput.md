### 1.4.1 Delay

End-to-end network를 통해 한 host에서 다른 host로 data가 이동한다.<br>
Packet switched network에서 data는 packet 단위로 쪼개져 전송된다.<br>
Packet은 host를 출발하여 access network를 거쳐 네트워크 core에 도달, 여러 router와 link를 지나 receiver에 도달한다.<br>
Packet은 각 node(router)를 지날 때마다 지연되는데, 이때 겪는 nodal delay는 processing delay, queuing delay, transmission delay, propagation delay로 구성된다.<br>
각 delay의 발생 과정과 어떤 상황에서 nodal delay를 결정하는 핵심 요소가 되는지 살펴보자<br>

#### ***Processing Delay***

Router에서 header를 처리하여 경로를 결정하는데 걸리는 시간<br>
router throughput의 최대 속도와 관련이 있다.<br>
> less than ~us

#### ***Queuing Delay ( 중요 )***

Outbound link에 전송 대기 중인 다른 packet이 있을 때 큐에서 대기하는 동안 걸리는 시간<br>
이때 마주하는 다른 packet의 수는 intensity function과 `// Todo [nature of traffic]`을 만족한다.<br>
> us ~ ms

#### *Transmission Delay*

Packet을 link에 전부 push하기까지 걸리는 시간<br>
Packet의 크기와 Transmission Rate ( Bandwidth, R )에 좌우된다.<br>
(one-hop delay) = L/R (L is the size of the packet)<br>
> us ~ ms

#### *Propagation Delay*

Packet이 한쪽 끝에서 다른 쪽 끝까지 이동하는데 걸리는 시간<br>
Medium에 따라 2x10^8 m/s ~ 3x10^8 m/s의 속력을 보이며, 두 end 간의 거리에 좌우된다.<br>
> us ~ ms

---
### Quiz

Transmission Delay와 Propagation Delay의 차이를 비교하시오.<br>
