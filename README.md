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
