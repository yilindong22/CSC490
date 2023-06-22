# Assignment 1: Data Locality and the Memory Wall

_Implement a basic version of the mesh reduction algorithm described in [Fat23] and accelerate single-core performance by 10×_

## Assignment Overview

In this assignment, you should demonstrate an ability to use basic knowledge of computer architecture to accelerate memory-bound software through algorithm redesign. You are given a superficially straight-forward problem, _vertex clustering_, which is an active direction of inquiry in our research lab and implemented in a wide range of computer graphics software suites, such as Blender, Open3D, Modo, and Unity [Fat23]. Later assignments in this course will look at parallelising that algorithm, but parallelism is only successful if a program is compute-bound. A first requirement is to take this memory-access-heavy algorithm and reduce its overall degree of memory latencies.

The first step in the algorithm is to construct an _adjacency list_ "spatial graph" over the points where point _p_ has an edge to point _q_ iff the L2 Euclidean distance between _p_ and _q_ is less than a user-specified constant, _epsilon_. A naive implementation of this on a large dataset is likely to be extremely memory bound, both in terms of reading data and in terms of constructing the adjacency list. You should use techniques described by Carruth [Car14], Doumler [Dou16], and Drepper [Dre07a, Dre07b] to come up with an implementation that is substantially faster than a naive implementation. It will likely help to think in terms of data-oriented design (c.f., [Act14]), i.e., where is data physically located and how do you arrange the sequence of data transformations to place data in low-latency locations. It will also help to think about different ways of representing the output graph (c.f., [Kel20]).

It is not sufficient to simply write some code and time it though. Research involves robust validation. You should develop a well-reasoned explanation (presumably based on knowledge from the readings) and then evaluate that conjecture with additional experiments. For example, Intel's VTune and the linux perf tool can allow you to directly observe what is happening on the computer when you run a software application. Intel even provides an excellent, systematic methodology for understanding program behaviour [Int23] and the linux perf tool can access a wide range of architectural counters [Gre16].

By the end, you will have taken an important problem and shown with solid evidence that you can accelerate algorithmic performance by tackling the memory wall.

This assignment is meant to demonstrate the following course-level competencies:
 1. Given an existing application, improve its data layout and memory access patterns in order to tackle the memory wall and facilitate parallelism
 4. Describe some basic concepts related to the intersection of computer graphics, spatial data processing, and parallel computing



## Deliverable

You should submit a six page pdf report (either by email or by Github pull request) that describes the problem that you are solving, your approach to solving it, and the evidence that you have succeeded. The report should also include a link to a github repository and a commit hash that corresponds to the code described in the report.

The deadline for the report is Sunday, 18 June. However, you can submit up to three weeks late without penalty.


## Evaluation

The report will be evaluated against the four equal-weighted criteria below, some of which may be evaluated by compiling and running the code on the git commit hash provided in the report. With the exception of the failing criterion (F), descriptors are inclusive of the levels below. That is to say, in order to achieve a mark of A+ (100%) on one criterion, all descriptions from P, B-, B, B+, and A must also be true.

Note that there is some subjectivity with respect to terms like "convincingly." You are encouraged to ask in advance of submitting if particular approaches match those descriptions.


| |100% (A+)|85% (A)|79% (B+)|76% (B)|73% (B-)|50% (P)|0% (F)|
|-|----|-----|---|---|---|---|---|---|
|**Performance**|10× improvement over naive implementation|3× improvement over naive implementation|2× improvement over naive implementation|50% faster than naive implementation|At least as fast as naive implementation|Runs and uses ideas from readings|Does not compile or does not run|
|**Evidence**|At least three related plots use metrics other than time to convincingly demonstrate that the proposed approach should outperform the baseline|At least two related plots use metrics other than time to convincingly demonstrate that the proposed approach should outperform the baseline|At least one plot uses metrics other than time to convincingly demonstrate that the proposed approach should outperform the baseline|Some data/evidence of improvement is provided in addition to time|Performance improvement is communicated with plots and/or tables|Performance improvement is communicated with data|Report lacks data and evidence to support claims of improved performance|
|**Description of approach**|Report gives technical detail that convincingly shows why the proposed approach should have better memory access performance than the naive baseline|Report gives technical detail that shows why the proposed approach should have better memory access performance than the naive baseline|Report explains convincingly why the proposed approach should have better memory access performance than the naive baseline|Report explains plausibly why the proposed approach should have better memory access performance than the naive baseline|Report gives enough detail about the proposed approach that it could be implemented exactly by somebody else|Report describes what improvements can be made to try to make the baseline faster|Report lacks technical and algorithmic description|
|**Connection to reference list**|Discussion shows clearly how at least five of the assignment sources are used in the report to improve results|Discussion shows clearly how at least three of the assignment sources are used in the report to improve results|Report describes important content from at least five of the assignment sources|Report describes important content from at least four of the assignment sources|Report describes important content from at least three of the assignment sources|At least five assignment sources are cited|No engagement with literature|



## References

[Act14] Acton (2014). "Data-Oriented Design and C++." In _CppCon 2014_. YouTube video. Accessed 21-June-2023 from: https://youtu.be/rX0ItVEVjHc.

[Car14] Carruth (2014). "Efficiency with Algorithms, Performance with Data Structures." YouTube Video. https://www.youtube.com/watch?v=fHNmRkzxHWs. Retrieved 16 May 2023.

[Dou16] Doumler (2016). "Want fast C++? Know your hardware!." YouTube Video. https://www.youtube.com/watch?v=BP6NxVxDQIs. Retrieved 16 May 2023.

[Dre07a] Drepper (2007). "3. CPU Caches." In What Every Programmer Should Know About Memory. https://people.freebsd.org/~lstewart/articles/cpumemory.pdf. Retrieved 9 May 2023.

[Dre07b] Drepper (2007). "6.2 Cache Access." In What Every Programmer Should Know About Memory. https://people.freebsd.org/~lstewart/articles/cpumemory.pdf. Retrieved 16 May 2023.

[Fat23] Fathollahi (2023). "Lock-free Parallel Mesh Reduction." Master's Thesis. _University of Victoria_. 90 pages. 

[Gre16] Gregg (2016). "perf Examples." Website. Retrieved 22 June 2023 from: https://www.brendangregg.com/perf.html.

[Kel20] Kelly (2020). "Compressed Sparse Row Format for Representing Graphs." _login - The Usenix Magazine_: 45(4), 76–82.

[Int23] Intel (2023). "Top-down Microarchitecture Analysis Method." In Intel VTune Profiler Performance Analysis Cookbook. https://www.intel.com/content/www/us/en/docs/vtune-profiler/cookbook/2023-0/top-down-microarchitecture-analysis-method.html. Retrieved 16 May 2023.

[Sut05] Sutter (2005). "The Free Lunch Is Over: A Fundamental Turn Toward Concurrency in Software." _Dr. Dobb's Journal_: 30(3). Accessed 21-June-2023 from: http://www.gotw.ca/publications/concurrency-ddj.htm

[Sut13] Sutter (2013). "Welcome to the Jungle: Or, A Heterogeneous Supercomputer in Every Pocket." Blog post. Accessed 21-June-2023 from: https://herbsutter.com/welcome-to-the-jungle/ 
