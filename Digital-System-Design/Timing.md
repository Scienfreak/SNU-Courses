## Timing In Procedural block

### Delay Control

#### *Inter-Assignment Delay Control*

    initial begin
        #25
        #15
    end

#### *Intra-Assignment Delay Control*

    initial begin
        y = #25 ~x;             // evaluate at time 0;  assign to y     at time 25
        count = #15 count + 1;  // evaluate at time 25; assign to count at time 40
    end
  
    initial begin
        y <= #25 ~x;             // evaluate at time 0; assign to y     at time 25
        count <= #15 count + 1;  // evaluate at time 0; assign to count at time 15
    end
    
    
### Event Control

#### *Edge-Triggered Events*

- Use "@"
- Based on the direction of the change toward the value 1
  - posedge: transition from 0 to x, z, or 1, and from x or z to 1
  - negedge: transition from 1 to x, z, or 0, and from x or z to 0

    always @(posedge clock) begin
        reg <= @(negedge clock) in2 ^ in3; // edge-triggered event; evaluated at time 0; assign to reg at next negedge
    end

#### *Named Events*

- (Declaration) event
- (Triggering) triggered by the symbol "->"
- (Recognition) recognized by the symbol "@"

    event received_data; // declare a named event "received_data"
    
    // trigger event received_data
    always @(posedge clock) if (last_byte) -> received_data;
    
    // 
    
#### *Event "or" operator*

- Use the keyword "or" or "," to specify multiple triggers
  - "," is recommended (new in Verilog 2001)
- Use @*\ or @(*\) to mean a change on any signal

#### *Level-Sensitive Event Control*
- Use keywork **Wait**

### Selection Constructs
Two types
- **if...else** statement
- **case** statement

**Example: 4-to-1 Mux**

    always @(*)
        if (s1) begin
            if (s0) out = i3; else out = i2;
        end
        else begin
            if (so) out = i1; else out = i0;
        end

**Example: Simple 4-bit Counter**

    always @(negedge clock or posedge clear) begin
        if (clear)  qout <= 4'd0;
        else        qout <= qout + 1; // qout <= (qout + 1) % 16;
    end

#### *Case Statement*

- Check if the given expression matches one of the other expressions in the list
- Compare every 1 and 0, x, z
- Missing default: can make unexpected latch unless we catch all cases.

#### *casex and casez*

- Used
- Compare only non-x or z positions in the case expression and the case alternatives
- casez: don't care z
- casex: don't care z and x

    always @(data)
        casex (data)
            4'bxxx1:
            4'bxx11:
            4'bx111:
            4'b1111:
            4'b0000:
        endcase
        
### Loop Constructs
- Only inside and initial or always block
- my contain delay expressions
- Used to create **multiple instances** of hardware logic; but, be careful!<br>
  (You should think about these constructs in the context of hardware!)
  
Four types
- while loop
- for loop
- repeat loop
- forever loop

#### *while*
- Hardware 만들 때 loop을 다 unrolling한다. -> 때문에 non-blocking assignment 쓰면 결과가 제대로 나오지 않는다.

#### *for*
- for <-> while
- synthesizalbe: compile time에 loop이 몇 번 도는지 알고 있어야 함.

#### *forever*
- Synthesize 불가능.
