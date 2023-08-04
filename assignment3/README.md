# Assignment 3: Parallelism Research Study

_Implement and compare two separate multi-core algorithms for the mesh reduction problem described in [Fat23] and provide convincing empirical evidence of which is a more effective approach to parallelisation_

## Assignment Overview

In this assignment, you should demonstrate an ability to use conduct a small scientific investigation by empirically comparing two parallel algorithms that express different trade offs between accuracy and parallelism. You are given the same superficially straight-forward problem from the previous report, _vertex clustering_, which is an active direction of inquiry in our research lab and implemented in a wide range of computer graphics software suites, such as Blender, Open3D, Modo, and Unity [Fat23]. You have already implemented a parallel solution to the adjacecy graph construction phase of this problem in the previous reports: the first report used a compressed sparse row (CSR) format to address memory wall challenges and the second report used a parallel reduction and pthreads to exploit multiple cores.

Your report should include any remaining parts of the vertex clustering problem, such as the iteration of vertices and assignment to clusters. We discussed two possible parallel approaches:
  1. using your parallel CSR construction following by a sequential clustering phase
  2. splitting the data into roughly equal two-dimensional "tiles" and launching a thread to process each tile independently

The first approach, we presume will make less use of parallelism because the second phase is constrained by Amdahl's Law. However, the second approach is heuristic and may introduce error. In this study, you should evaluate the relative performance and accuracy of each method by implementing them and measuring appropriate metrics.

By the end, you will have taken an important problem and performed a solid scientific investigation into the relative merits of alternative solutions.

This assignment is meant to demonstrate the following course-level competencies:
 1. Given an existing application, improve its data layout and memory access patterns in order to tackle the memory wall and facilitate parallelism
 2. Given a problem, design an algorithm for it with data-level parallelism and implement and evaluate that algorithm in C or C++
 3. Given a scientific research question, design and execute a novel experiment design to confirm or reject a hypothesis
 4. Describe some basic concepts related to the intersection of computer graphics, spatial data processing, and parallel computing



## Deliverable

You should submit a twelve page pdf report (either by email or by Github pull request) that describes the problem that you are solving, your two algorithmic approaches to parallelising it, and compelling empirical evidence of which is more effective. You can selectively include content from the first and/or second reports if it is relevant here as well. The report should also include a link to a github repository and a commit hash that corresponds to the code described in the report. You are encouraged to format the report in the style of an ACM or IEEE conference paper.

The deadline for the report is 23:59 Vancouver/LA on Friday, 18 August 2023.


## Evaluation

The report will be evaluated against the four equal-weighted criteria below, some of which may be evaluated by compiling and running the code on the git commit hash provided in the report. With the exception of the failing criterion (F), descriptors are inclusive of the levels below. That is to say, in order to achieve a mark of A+ (100%) on one criterion, all descriptions from P, B-, B, B+, and A must also be true.

Note that there is some subjectivity with respect to terms like "convincingly." You are encouraged to ask in advance of submitting if particular approaches match those descriptions. You are encouraged to use elements like mathematical formulae, pseudocode, and plots or tables to make the exposition more precise.


| |100% (A+)|85% (A)|79% (B+)|76% (B)|73% (B-)|50% (P)|0% (F)|
|-|----|-----|---|---|---|---|---|
|**Performance Analysis**|Report makes convincing that the same results would be observed on new datasets|Analysis richly discusses the experiment results by describing non-obvious trends across plots and relating those to algorithm descriptions|At least three distinct metrics evaluate both algorithms relative to each other ("triangulation")|At least two distinct metrics evaluate both algorithms relative to each other|At least one distinct metric evaluates both algorithms relative to each other|No comparison and/or analysis|
|**Accuracy Analysis**|Report makes convincing that the same results would be observed on new datasets|Analysis richly discusses the experiment results by describing non-obvious trends across plots and relating those to algorithm descriptions|At least three distinct metrics evaluate both algorithms relative to each other ("triangulation")|At least two distinct metrics evaluate both algorithms relative to each other|At least one distinct metric evaluates both algorithms relative to each other|No comparison and/or analysis|
|**Evidence of Correctness**|Report provides convincing evidence that the implementation of both algorithms is correct and non-deterministic|Report provides evidence that the implementation of both algorithms is correct and non-deterministic|N/A|Report provides evidence that the implementation of both algorithms is non-deterministic|Report provides evidence that either of the implementations is likely correct|Report lacks data and evidence to support claims of implementation correctness|
|**Clarity of Algorithm Descriptions**|Code and parallelisation strategy is reproducible from clear and technically precise algorithm descriptions in the report|Code and parallelisation strategy is reproducible from clear algorithm descriptions in the report|N/A|Report describes parallel strategy well enough to convey a conceptual understanding|Report describes algorithms well enough to convey a conceptual understanding|Report contains algorithm description|No algorithm nor description of exposing parallelism included in report|



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
