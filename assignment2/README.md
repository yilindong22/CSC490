# Assignment 2: Multi-core Parallelism

_Implement a multi-core version of the mesh reduction algorithm described in [Fat23] that accelerates performance relative to a single core by a factor of 3× on 4 cores_

## Assignment Overview

In this assignment, you should demonstrate an ability to use basic knowledge of multi-threading to accelerate software by exposing parallelism. You are given a superficially straight-forward problem, _vertex clustering_, which is an active direction of inquiry in our research lab and implemented in a wide range of computer graphics software suites, such as Blender, Open3D, Modo, and Unity [Fat23]. You have already implemented this problem in the first report that investigated the memory wall and should now identify a way to accelerate this problem using multiple cores.

Your report should include both a theoretical discussion and experimental results, both of which are meant to provide evidence that the parallelism will be effective. For the theoretical content, it may help to consider Amdahl's Law [Adm67] or Gustafson's Law [Gus13] as means of evaluating theoretical limits to parallelism. You may also consider different theoretical models for analysing an algorithm, such as the work-span model [Aca16] or the PRAM model [CLR08]. Finally, you should describe _how_ you parallelised the algorithm, and for this is may be helpful to think in terms of standard parallel design patterns [MMS05]. Together, these approaches should give you a strong arsenal for reasoning about your approach and at least one will probably apply to the report.

As before, it is not sufficient to simply write some code and time it though. Research involves robust validation. You should develop a well-reasoned explanation (presumably based on knowledge from the readings) and then evaluate that conjecture with additional experiments. For example, Intel's VTune and the linux perf tool can allow you to directly observe what is happening on the computer when you run a software application. Intel even provides an excellent, systematic methodology for understanding program behaviour [Int23] and the linux perf tool can access a wide range of architectural counters [Gre16]. It could be helpful to apply these same ideas that you used in the previous report to this multi-threaded context. Consider if there is a way that they could help you to measure the amount of "work" done by the algorithm so that you can empirically demonstrate work efficiency.

By the end, you will have taken an important problem and shown with solid evidence that you can accelerate algorithmic performance by tackling the memory wall and then parallelising it for a multi-core architecture.

This assignment is meant to demonstrate the following course-level competencies:
 1. Given an existing application, improve its data layout and memory access patterns in order to tackle the memory wall and facilitate parallelism
 2. Given a problem, design an algorithm for it with data-level parallelism and implement and evaluate that algorithm in C or C++
 4. Describe some basic concepts related to the intersection of computer graphics, spatial data processing, and parallel computing



## Deliverable

You should submit a nine page pdf report (either by email or by Github pull request) that describes the problem that you are solving, your approach to solving it, and the evidence that you have succeeded. You can selectively include content from the first report if it is relevant here as well. The report should also include a link to a github repository and a commit hash that corresponds to the code described in the report.

The deadline for the report is midnight Vancouver/LA on Tuesday, 18 July. However, you can submit up to ten days late without penalty.


## Evaluation

The report will be evaluated against the four equal-weighted criteria below, some of which may be evaluated by compiling and running the code on the git commit hash provided in the report. With the exception of the failing criterion (F), descriptors are inclusive of the levels below. That is to say, in order to achieve a mark of A+ (100%) on one criterion, all descriptions from P, B-, B, B+, and A must also be true.

Note that there is some subjectivity with respect to terms like "convincingly." You are encouraged to ask in advance of submitting if particular approaches match those descriptions. You are encouraged to use elements like mathematical formulae, pseudocode, and plots or tables to make the exposition more precise.


| |100% (A+)|85% (A)|79% (B+)|76% (B)|73% (B-)|50% (P)|0% (F)|
|-|----|-----|---|---|---|---|---|
|**Performance**|3× improvement over single-threaded on 4 cores|2× improvement over single-threaded on 4 cores|1.5× improvement over single-threaded on 4 cores|50% faster than single core|At least as fast as single core|Runs and uses ideas from readings|Does not compile or does not run|
|**Throughput**|Report provides convincing theoretical arguments and supporting evidence that parallel throughput is very high|Report provides theoretical arguments and supporting evidence that parallel throughput is very high|Report provides convincingly theoretical arguments or convincing supporting evidence that parallel throughput is very high|N/A|Report provides theoretical arguments or supporting evidence that parallel throughput is very high|Throughput can be expected from a description of how parallelism is exposed|Report lacks data and evidence to support claims of parallel throughput|
|**Work-efficiency**|Report provides convincing theoretical arguments and supporting evidence that work efficiency is very high|Report provides theoretical arguments and supporting evidence that work efficiency is very high|Report provides convincingly theoretical arguments or convincing supporting evidence that work efficiency is very high|N/A|Report provides theoretical arguments or supporting evidence that work efficiency is very high|Work efficiency can be expected from a description of how parallelism is exposed|Report lacks data and evidence to support claims of work efficiency|
|**Connection to reference list**|Discussion shows clearly how at least five of the assignment sources are used in the report to improve parallelism|Discussion shows clearly how at least three of the assignment sources are used in the report to improve parallelism|Report describes important content from at least five of the assignment sources|Report describes important content from at least four of the assignment sources|Report describes important content from at least three of the assignment sources|At least five assignment sources are cited|No engagement with literature|



## References

[Aca16] Acar (2016). "Chapter 5.1. Cost Model: Work and Span." In _Parallel Computing: Theory and Practice_. Accessed 22-July-2023 from: http://www.cs.cmu.edu/afs/cs/academic/class/15210-f15/www/tapp.html.

[Act14] Acton (2014). "Data-Oriented Design and C++." In _CppCon 2014_. YouTube video. Accessed 21-June-2023 from: https://youtu.be/rX0ItVEVjHc.

[Amd67] Amdahl (1967). "Validity of the Single Processor Approach to Achieving Large Scale Computing Capabilities." _AFIPS Conference Proceedings_. Accessed 22-July-2023 from: https://www3.cs.stonybrook.edu/~rezaul/Spring-2012/CSE613/reading/Amdahl-1967.pdf.

[Car14] Carruth (2014). "Efficiency with Algorithms, Performance with Data Structures." YouTube Video. https://www.youtube.com/watch?v=fHNmRkzxHWs. Retrieved 16 May 2023.

[CLR08] Casanova, Legrand, & Robert (2008). "Chapter 1. PRAM Model." In _Parallel Algorithms_. Accessed 22-July-2023 from: https://search.library.uvic.ca/permalink/01VIC_INST/12198k2/alma9957689933507291.

[Dou16] Doumler (2016). "Want fast C++? Know your hardware!." YouTube Video. https://www.youtube.com/watch?v=BP6NxVxDQIs. Retrieved 16 May 2023.

[Dre07a] Drepper (2007). "3. CPU Caches." In What Every Programmer Should Know About Memory. https://people.freebsd.org/~lstewart/articles/cpumemory.pdf. Retrieved 9 May 2023.

[Dre07b] Drepper (2007). "6.2 Cache Access." In What Every Programmer Should Know About Memory. https://people.freebsd.org/~lstewart/articles/cpumemory.pdf. Retrieved 16 May 2023.

[Fat23] Fathollahi (2023). "Lock-free Parallel Mesh Reduction." Master's Thesis. _University of Victoria_. 90 pages. 

[Gre16] Gregg (2016). "perf Examples." Website. Retrieved 22 June 2023 from: https://www.brendangregg.com/perf.html.

[Gus13] Gustafson (2013). "Reevaluating Amdahl's Law." _Communications of the ACM_ 31(5): 3 pages.

[Kel20] Kelly (2020). "Compressed Sparse Row Format for Representing Graphs." _login - The Usenix Magazine_: 45(4), 76–82.

[Int23] Intel (2023). "Top-down Microarchitecture Analysis Method." In Intel VTune Profiler Performance Analysis Cookbook. https://www.intel.com/content/www/us/en/docs/vtune-profiler/cookbook/2023-0/top-down-microarchitecture-analysis-method.html. Retrieved 16 May 2023.

[MMS05] Mattson, Massingill, & Sanders (2005). _Patterns for Parallel Programming_. Accessed 22-July-2023 from: https://search.library.uvic.ca/permalink/01VIC_INST/12198k2/alma9957516936307291.

[Sut05] Sutter (2005). "The Free Lunch Is Over: A Fundamental Turn Toward Concurrency in Software." _Dr. Dobb's Journal_: 30(3). Accessed 21-June-2023 from: http://www.gotw.ca/publications/concurrency-ddj.htm

[Sut13] Sutter (2013). "Welcome to the Jungle: Or, A Heterogeneous Supercomputer in Every Pocket." Blog post. Accessed 21-June-2023 from: https://herbsutter.com/welcome-to-the-jungle/ 
