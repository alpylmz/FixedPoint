Fixed Point Library
===================

This is a header-only fixed point arithmetic library. It is used to build a fixed-point floating number based controller, and the library's primary goal is to simulate an ALU working with fixed-point floating numbers. Therefore, overflow is allowed and naturally expected in some cases. There are some manual test cases, but the reference implementation is [spfpm](https://github.com/alpylmz/spfpm/tree/51f1250afa343212984b37a97cea2644a4844121) library, and both libraries are tested with randomly generated test cases.

### Notes
I couldn't exactly match the spfpm behaviour and our library's behaviour in bit clamps and especially overflow. It seems that will be future me's problem. But I expect the clamp mode to work perfectly fine. 
