---
title: Codeforce Round 926 
date: 2024-02-20
categories: [Algorithm]
tags: [algorithm]     # TAG names should always be lowercase
math: true
mermaid: true
---


## Porblem D [Sasha and a Walk in the City] (https://codeforces.com/contest/1929/problem/D)

The statement of this problem is not clear.
Problem statement from the comment in [tutorial page](https://codeforces.com/blog/entry/125851?#comment-1117492).

> Given a tree, you need to color each node in black or white. How many colorings exist such that the path between any two vertices contains atmost 2 black vertices.


Define the state of dynamic programming as the tutorial.
> Let $dp_v$ be the number of non-empty sets of vertices in the subtree rooted at $v$ such that there are no pairs of vertices in the set where one vertex is the ancestor of the other.

Now we consider how to calculate the states from leaf to root. Supporse we have done this for all subtree in current node, $u$. $dp_u$ can be calculate by $dp_u = \pi_(dp_v + 1)$ where $v$ is child of $u$. 

To get this equation, we first consider current node is one element of the set. Then all subtree should be empty. Otherwise we voilate the $dp$ state. If current node not the element of the set. All the subtree can be selected or keep empty. That's why $dp_v + 1$. Notice if all subtree is emtpy, current node should be selected. So first situation already include in the second one. 

The answer of the problem $\sum_i^n dp_i + 1$. To get the answer we need to consider for all situations. There is not double we need to have the $dp_{root}$. But if we consider for each subtree. $dp_{v}$ does not contain and pairs of vertices in the set where one vertex is the ancestor of the other. If we put everyting beyong this sub-tree empty. Then we chan have $v$ in the set. This is not include in $dp_{root}$. The last $1$ is the root can be also not in the set.






