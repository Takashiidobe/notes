---
title: "A Critique Of Ansi Sql Isolation Levels"
pdf_url: "[[a-critique-of-ansi-sql-isolation-levels.pdf]]"
---
## Notes

This paper discusses ANSI's isolation levels and the phenomena that each one allows, and then discusses new phenomena that can happen. These have been extended throughout the years as well.

## ANSI's four Phenomena

1. Dirty Write: A transaction overwrites another transaction's uncommitted update.
	- initially, $x$ = 0.
	- $T_1$ writes $x$ to 10. It doesn't commit or abort yet.
	- $T_2$ writes $x$ to 20. It then commits. 
	- $T_1$ then aborts.
	- This breaks later undo of $T_1$ to $x$.
2. Dirty Read: A transaction reads data from another uncommitted transaction.
	- initially, $x$ = 0, $y$ = 0.
	- $T_1$ writes $x$ to 10.
	- $T_2$ reads $x$, which is 10. It has code to set $y$ to 10 if $x$ is 10.
	- $T_1$ then aborts.
	- $T_2$ then sets $y$ to 10, and aborts.
	- $y$ is set to 10 even though $x$ was never 10 in a committed transaction.
3. Nonrepeatable Read: A transaction reads a row, another transaction changes it before the first commits.
	- initially, $x$ = 100.
	- $T_1$ reads $x$, which is 100.
	- $T_2$ writes $x$ to 150, and then commits.
	- $T_1$ then reads $x$ again later in the transaction, and sees 150. It commits.
	- Thus, $T_1$ cannot repeat its read.
4. Phantom Read: A transaction reads a set of rows, transaction 2 updates rows match that predicate.
	- initially, $x$ is the number of doctors, 1.
	- There is a constraint, $C_{x}$ that there must always be 1 doctor available per shift.
	- $T_1$ makes sure that there's at least one doctor twice, once at the beginning and once at the end of the transaction, before reporting the shift is ok.
	- $T_2$ notes that a doctor has to take vacation. So $x$ is set to 0.
	- $T_1$ reads again, and notes that $x$ is 0, so a row disappeared.

## New Phenomena

1. Lost Update:
	- $T_1$ reads $x$ at $t_1$.
	- $T_2$ reads $x$ at $t_1$ and then increments it. It then commits, incrementing to $t_2$.
	- $T_1$ still has its copy of $x$ from $t_1$, so it also increments it as well. This overwrites $T_2$'s update, and only one increment is persisted, even though $T_1$ and $T_2$ complete.
	- This can happen under Read Committed, and is prevented by Repeatable Read.

2. Cursor Lost update:
	- Pretty much the same as Lost Update, just using a cursor. This is fixed by Cursor Stability, where on FETCH of a cursor, the row it fetched is locked for reads, making updating that row impossible and removing lost update for cursors.
	
3. Read Skew:
	- The table has a constraint, $C_{x,y}$, which is a property of columns $x$ and $y$.
	- $T_1$ reads $x$.
	- $T_2$ updates $x$ and $y$, following $C_{x,y}$, and commits. 
	- $T_1$ then reads $y$.
	- Since $T_1$ sees $x$ at $t_1$ and $y$ at $t_2$, is no guarantee that $C_{x,y}$ is enforced. 

4. Write Skew:
	- The table has a constraint, $C_{x,y}$, which is a property of columns $x$ and $y$.
	- $T_1$ reads $x$ and $y$.
	- $T_2$ reads $x$ and $y$.
	- $T_2$ writes $x$ and commits, maintaining $C_{x,y}$.
	- $T_1$ writes $y$ and commits, maintaining $C_{x, y}$.
	- There is no guarantee that $C_{x, y}$ holds, since $x$ and $y$ were written at different times.

## Other Phenomena

There are more phenomena as well -- Adya has Generalized Isolation Level Definitions (GILD). which discuss the following:

1. Write Cycles:
	- Initially, $x$ = 0.
	- $T_1$ reads $x$ and increments it to 1. It then commits.
	- $T_2$ reads $x$ and increments it twice in the transaction. It then commits.
	- $x$ should be 3, but it is 2, so $T_2$ has overwritten $T_1$.
2. Aborted reads:
	- Initially, $x$ = 0.
	- $T_1$ sets $x$ = 1, and then $x$ = 2, and then aborts.
	- $T_2$ reads $x$ in the middle of $T_1$, reading 1, an aborted read.
3. Intermediate read:
	- Initially, $x$ = 0.
	- $T_1$ sets $x$ to 10 at $t_1$, and then x to 20 at $t_2$ in a long running transaction, then commits at $t_3$.
	- $T_2$ reads $x$ at $t_1$, so it sees $x$ = 10. However, this value of $x$ has never been committed.
4. Cyclic Information Flow:
	- Initially, $x$ = 0, and $y$ = 0.
	- $T_1$ sets $x$ = 1.
	- $T_2$ sets $y$ = 1.
	- Then, $T_1$ reads $y$, which is 1.
	- Then, $T_2$ reads $x$, which is 1.
	- This means that $T_1$ $\rightarrow$  $T_2$ $\rightarrow$ $T_1$, which makes this impossible to serialize.
5. Anti-dependency cycles:
	- Initially, $x$ = 0, and $y$ = 0.
	- $C_{x, y}$ is that at most, $x$ or $y$ can be 1. 
	- $T_1$ reads $x$ and $y$, and sees they are both 0. It then sets $x$ to 1, which satisfies $C_{x, y}$, because it believes $y$ is 0. It commits.
	- $T_2$ reads $x$ and $y$, and sees they are both 0. It then sets $y$ to 1, which satisfies $C_{x, y}$, because it believes $x$ is 0. It commits.
	- $x$ = 1 and $y$ = 1, which violates $C_{x, y}$, even though both transactions followed $C_{x, y}$ in their transaction.