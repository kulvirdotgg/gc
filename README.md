# Garbage Collector

Garbage collection(GC) is form of automatic memory management. Garbage collector attempts to reclaims the memory that was allocated to program, but no longer referenced which is called `Garbage`.
Garbage collection relieves from doing manual memory management and saves us from the bugs that occurs due to poor memory management practices. GC, however affects the performance of program because the GC thread can start in between the execution of program and stopping the normal flow of program. Therefore this conviniece causes extra overhead which may not be ideal for certain kind of application. The moment when garbage will be collected can be unpredictable.

## Reference Counter GC

This is the simplest implementation of GC. Reference counter is just a counter. For each allocation counter is incremented. When the counter reaches zero we know object is no longer referenced in the program so we can garbage collect it or free the memory.

### Disadvantages:

- If two objects reference each other, they create a cycle so neither of them will be garbage collected as their mutual references never let their count become zero.
- Ref counting requires us to maintain a counter with each object so it requires additional storage.
- Each assignment of a reference and each deallocation modifies the counter value. Hence this is overhead and is expensive operatin which affects the speed of program.
- Increment and decrement operations need to be atomic such as `compare and swap`. Atomic operations are expensive for the processor.

## Mark and Sweep GC

This is more sophisticated and more reliable GC which can detect cyclic reference too. `Mark and Sweep` algorithm work in two phases. In first phase we start from every object outside heap and do a graph traversal (DFS) on every object referenced by them and mark them. In second stage we look at every other object in heap and if its marked it means these objects are referenced by some object outside the heap so do not garbage collect it whereas all the objects not marked are garbage collected.

```c
void markAndSweep() {
    // mark phase
    for (all pointers P on the run-time stack or in the static data area) {
        mark *P;
    }

    // sweep phase
    for (all objects *P on the heap) {
        if *P is not marked then
        delete P
        else
        unmark *P
    }
}
```
### Disadvantages

- It has sophisticated implementation and requires a graph traversal.
- Since this algorithm run and check for all elements there may be times when CPU is allocated to only garbage collect elements and our program execution might be stopped.
- Since GC is activated when system is running low on memory, mark and sweep algorithm uses memory itself which is quite ironic KEKW.
- It has less predictable performance because GC can be triggered anytime and it will `stop the world` to garbage collect.
