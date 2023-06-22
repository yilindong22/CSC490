# CSC 490: Directed Studies: Data-Level Parallelism

_Yilin Dong & Dr. Sean Chester_
_Summer 2023_

## Course Overview

Since about 2005, the design of computers has changed fundamentally from trying to increase processor clock speeds to achieving greater peak throughput with parallel computing [Sut05]. Indeed, this trend continues and modern processors have shifted since about 2013 to favouring cloud-based distributed systems on one end and highly specialised, typically data-parallel, processors on the other [Sut13]. Software that is meant to be fast must keep pace with this changing architectural landscape, which suggests that much of it should be redesigned to expose more data-level parallelism. We already see many examples of real-time or high-performance systems moving towards data-oriented programming [Act14] and vectorisation [Fre15].

One application area that typically benefits from acceleration is computer graphics, particularly the rendering pipelines. For example, a 3D mesh can often be rendered at different resolutions depending on its position within a scene, and this suggests the value in quickly being able to reduce or simplify a mesh [Hop96]. Very recently, the mesh simplification algorithm was parallelised by Fathollahi [Fat23] using a data-parallel design, but it assumed the existence of a spatial index. In this course, we will learn data-parallel algorithm design through the process of redesigning the spatial index for all-points range search and evaluating a grid-based decomposition as an alternative to the algorithm suggested by Fathollahi.


## Course Competencies

This course is meant to develop competencies that relate to research skills and data-parallel algorithm design. In particular, after this course, you can:

1. Given an existing application, improve its data layout and memory access patterns in order to tackle the memory wall and facilitate parallelism
2. Given a problem, design an algorithm for it with data-level parallelism and implement and evaluate that algorithm in C or C++
3. Given a scientific research question, design and execute a novel experiment design to confirm or reject a hypothesis
4. Describe some basic concepts related to the intersection of computer graphics, spatial data processing, and parallel computing

## Deliverables

The course will consist of four deliverables:
- a preliminary report demonstrating mastery of concepts of data locality and an ability to convert memory-bound computation into compute-bound computation
- an interim report that compares two multi-core implementations of all-points k-nearest neighbour search applied to a LiDaR point cloud
- a final report that poses a scientific question related to parallel mesh reduction and compelling evaluates a hypothesis for that question
- a presentation summarizing key points from the final report, aimed at an audience of graduate-student peers who have no background in computer graphics or parallel computing

The due dates and relative weights of these deliverables are as per the table below:

| **Deliverable** | **Weight** | **Due** |
|-----------------|------------|---------|
| Report 1        | 15%        | 18 Jun  |
| Report 2        | 30%        | 18 Jul  |
| Final Report    | 40%        | 18 Aug  |
| Presentation    | 15%        | 18 Aug  |


## References

[Act14] Acton (2014). "Data-Oriented Design and C++." In _CppCon 2014_. YouTube video. Accessed 21-June-2023 from: https://youtu.be/rX0ItVEVjHc.

[Fat23] Fathollahi (2023). "Lock-free Parallel Mesh Reduction." Master's Thesis. _University of Victoria_. 90 pages. 

[Fre15] Fredriksson (2015). "SIMD at Insomniac Games: How we do the shuffle." In _Game Developers Conference 2015_. GDCVault video. Accessed 21-June-2023 from: https://www.gdcvault.com/play/1022248/SIMD-at-Insomniac-Games-How.

[Hop96] Hoppe (1996). "Progressive Meshes." In _Proc. SIGGRAPH_, 10 pages. 

[Sut13] Sutter (2013). "Welcome to the Jungle: Or, A Heterogeneous Supercomputer in Every Pocket." Blog post. Accessed 21-June-2023 from: https://herbsutter.com/welcome-to-the-jungle/ 

[Sut05] Sutter (2005). "The Free Lunch Is Over: A Fundamental Turn Toward Concurrency in Software." _Dr. Dobb's Journal_: 30(3). Accessed 21-June-2023 from: http://www.gotw.ca/publications/concurrency-ddj.htm


