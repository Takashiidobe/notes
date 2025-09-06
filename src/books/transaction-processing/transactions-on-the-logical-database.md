---
title: Transactions on the Logical Database
date created: Saturday, July 26th 2025, 3:47:58 pm
date modified: Saturday, July 26th 2025, 3:48:34 pm
---

# Transactions on the Logical Database

Next: [operations-on-the-physical-database](operations-on-the-physical-database.md)

# Transactions on the Logical Database Level

## Problems

### 1.1

The personnel database of an enterprise contains, among others, the relations created by the following SQL statements:

```sql
create table employee (
  empnr integer not null,
  name varchar(40) not null,
  address varchar(80) not null,
  job varchar(20),
  salary integer,
  deptnr integer not null,
  constraint pk primary key (empnr),
  constraint dfk foreign key (deptnr) references department
);

create table department (
  deptnr integer not null,
  name varchar(20) not null,
  managernr integer,
  constraint pk primary key (deptnr),
  constraint efk foreign key (managernr) references employee
);
```

Consider the transaction on the database produced by the SQL program fragment:

```sql
exec sql select max(empnr) into :e from employee;
exec sql select max(deptnr) into :d from department;
exec sql insert into department values (:d + 1, 'Research', :e);
exec sql insert into employee values (:e + 1, 'Jones, Mary',
  'Sisselinkuja 2, Helsinki', 'research director', 3500, :d + 1);
exec sql update department set managernr = :e + 1
  where deptnr = :d + 1;
exec sql insert into employee values (:e + 2, 'Smith, John',
  'Rouvienpolku 11, Helsinki', 'researcher', 2500, :d + 1);
exec sql commit;
```

a. Give the string of tuple-wise actions (readings and insertions of single tuples) that constitutes the transaction. We assume that the tuples of the relations `employee` and `department` reside in the data pages in an arbitrary order and that there exist no index to the relations.

b. Repeat (a) in the case in which there exists an ordered (B-tree or ISAM) index to the relation `employee` on attribute `empnr` and an ordered index to the relation `department` on attribute `deptnr`.

c. Are the transactions created in (a) and (b) logically consistent? That is, do they preserve the integrity constraints of the database?

---

### 1.2

The following SQL program fragments operate on relation $r(X, V)$. Describe the transaction produced by the program fragments (1) in the read-write model of transactions and (2) in the key-range model of transactions:

a.  
```sql
update r set V = V + 1 where X = x; commit;
```

b.  
```sql
update r set V = V + 1 where X = x;
```

c.  
```sql
update r set V = V + 1 where X = x; rollback;
```

---

### 1.3

Explain the meaning of the transaction

$$
\begin{align*}
B[r, x_1, v_1]S[P_1]I[r, x_2, v_2]S[P_2]/[r, x_3, v_3]A[P_2] \\
I[r, x_3, v_3]C[P_2]/[r, x_4, v_4]A[P_1] \\
W[r, x_1, v_1']W[r, x_2, v_2']C[P_1]/[r, x_5, v_5]4 \\
I[r, x_1, v_1]C
\end{align*}
$$

Give SQL statements to generate this transaction.

---

### 1.4

A banking database contains the relations:

```sql
account(number, balance),
holder(card number, account number),
card(number, holder name, holder address, crypted password),
transaction(site, date time, type, amount, account number, card number)
```

where the relation `transaction` stores information about every completed or attempted withdrawal and deposit and about every balance lookup.

Give an embedded SQL program for a transaction for a withdrawal of $s$ euros using card $c$ with password $p$, where the withdrawal is allowed only if no overdraft will occur. The transaction also shows the balance that remains in the account after completing the withdrawal. We assume that the program includes the following statement:

```sql
exec sql whenever sqlerror goto L;
```

where $L$ is a program address to which the program control is transferred whenever an error status is returned by the execution of some SQL statement.

---

### 1.5

Consider extending the read-write transaction model with an action $C[x]$ which **declares** the updates on $x$ as committed. This action can appear in the forward-rolling phase of the transaction, and it has the effect that **even if** the transaction eventually aborts and rolls back, the updates on $x$ done before $C[x]$ will not be undone. Accordingly, complete the transaction:

$$
\begin{align*}
BR[x, u][x, u', u'']R[v, v]W[v, v, v'] \\
C[x]R[z, w]W[z, w, w']W[v, v', v''] \\
C[v]W[x, u'', u''']A
\end{align*}
$$

to a rolled back transaction. Consider situations in which this feature might be useful.

---

### 1.6

Our key-range transaction model assumes that the tuples $(x, v)$ are only referenced via the unique primary keys $x$. Extend the model to include relations $r(X, Y, V)$, where tuples $(x, y, v)$ can be referenced by either the primary key $x$ or by the (non-unique) secondary key $y$.

---

### 1.7

We extend our key-range transaction model by a **cursor mechanism** that works as follows. When a transaction starts, it allocates a main-memory **cursor** (the cursor), private to the transaction, to store the tuples returned by all the read actions performed by the transaction, in the order of the actions. Each read action $R[r, x]$ appends the tuple $(x, v)$ to the next available entry in the cursor. In a more general setting, we would have several cursors, with special actions to open and close a cursor.

Now if the transaction performs a partial rollback to a savepoint, the contents of the cursor should be restored to the state that existed at the time the savepoint was set. Obviously, to that effect, we should define an undo action, say

$$
R^{-1}[x]
$$

for a rollback. Elaborate this extension of our transaction model.

Next: [operations-on-the-physical-database](operations-on-the-physical-database.md)
