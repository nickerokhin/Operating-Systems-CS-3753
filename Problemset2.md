1.There is a one-lane east-west bridge in Hawaii such that when a car is on the bridge going eastbound, no westbound cars are allowed until the eastbound car has left the bridge.


Similarly when a westbound car is on the bridge, no eastbound cars are allowed until the westbound car has left the bridge. 
To make matters more complicated, if an eastbound car arrives and sees another eastbound car already on the bridge, then that eastbound car will also proceed onto the bridge.
This is true even if there is a westbound car already waiting to enter the bridge.  
Similarly, a westbound car can tailgate behind another westbound car already on the bridge even if an eastbound car was waiting. 
Deign a synchronization solution using only locks, semaphores and integer variables that achieves the following: allows all cars bound in a certain direction to continue crossing as long as there is at least one car still on the bridge that is bound in that direction, then toggles to allow all cars in the opposite direction to proceed in a similar manner.
The solution need not be starvation-free.



```
lock bridge;
semaphore east_s, west_s;
int east;
int west;

going_west(){
  
  p(west_s)
  west++;
  if(west == 1){
    p(bridge)
    v(west_s)
  }
    p(west_s)
    west--;
    if(!west){
    v(bridge)
    }
    v(west_s);
    v(east_s)
}


going_east(){
  p(east_s);
  east++;
  if(east == 1){
    p(bridge)
    v(east_s)
  }
  if(!east){
    p(bridge);
    east--;
    v(bridge)
  }
  v(east_s)
  v(west_s)
}


```


2.Suppose task T1 has code C1 that must execute before task T2's code C2.
Design a solution that enforces this ordering using only condition variables, locks, and integer variables.
Semaphores and monitors are not allowed.

```

lock proglock;
condition c;
int t1;

Acquire(proglock); //Block all other code
Do T1
t1 = 1; //T1 done
Release(proglock); //Release lock
c.signal();

Aquire(proglock); //Check if lock is blocked or not
while(!t1){ //Repeatedly checks if t1 is complete
Release(proglock) ]]
c.wait()
Acquire(proglock)
}
Do t2
Release(proglock)

```


3.Explain why the solution to the 3rd Readers/Writers problem is starvation-free.

The third readers-writers problem depends on serving readers/writers in order of arrival to prevent starvation. By not prioritizing readers or writiers, neither category will be starved. Each thread will be locked on the data for a bounded amount of time, then releasing it in a bounded amount of time, this allows each thread to be treated fairly and starvation free.



4.a.Is the swap() function below thread-safe or not? Explain your reasoning.

```
int temp;
 
void swap(int *y, int *z)
{
    int local;
 
    local = temp;
    temp = *y;
    *y = *z;
    *z = temp;
    temp = local;

}
```

4.b.(+10) Suppose the swap() function above is called by the interrupt service routine (ISR) below.  Assume that if swap() is interrupted during normal execution, the ISR below is called and calls swap() again, reentering swap() and executing in the context of the interrupted thread.  Is swap() reentrant?  Explain your reasoning.

This code is not reentrant because it depends on a global variable. Despite no synchronization mechanisms in place. If the function gets interrupted after temp = *y by an ISR, and another thred enters the function, the function will execute with the temp variable set by the previous thread and cause a lot of inconsisetncies. 


This code isn't thread safe because swap changes the value of the global variable temp. This causes an insonsistency between 
threads accessing the same variable.

5.Suppose you are asked to design a server application consisting of two processes P1 and P2, such that (1) P2 is to sleep until woken up by P1, whereupon (2) P2 would take a 10 MB file from P1 and compress it. What forms of IPC would be best suited to implement these types of information sharing? Describe your solution.

A pipe could work for this problem. P2 would sleep until data is finished being written to the buffer. Then P1 sends P2 a signal to wake up and p2 would start to compress the file.

6.Suppose processes P0 and P1 share variable V1, and processes P1 and P2 share variable V2, while processes P0, P1 and P2 share V3.  Operations on V1 are limited to increment() and decrement().  Operations on V2 are limited to square() and squareroot().  Operations on V3 are limited to sin() and cos().  Design a monitor-based solution that synchronizes access to and manipulation of these variables between the three processes so that race conditions are eliminated.

```

moitor Monitor {
  condition p1, p2, p3; //condition of the processes P1, P2....
  int v1, v2, v3


  increment(v1){
  p1.wait() //Wait for p1 to finish being used
  v1+=1
  p1.signal() //Signal p1 is ready for use
  }
  
  decrement(v1){
  p1.wait()
  v1-=1
  p1.signal()
  }
  
  square(v2){
  p2.wait()
  v2*=v2
  p2.signal()
  }
  
  squareRoot(v2)
  p2.wait()
  v2.sqrt()
  p2.signal()
  
  sin(v3){
  p3.wait()
  v3.sin()
  p3.signal()
  }
  
  cos(v3){
  p3.wait()
  v3.cos()
  p3.signal()
  }
 }
```

Thank you https://en.wikipedia.org/wiki/Monitor_(synchronization) for monitor help

