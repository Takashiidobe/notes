---
title: design-an-atm
---

An Atm

# Design an ATM

What are some of the core features of an ATM? You can do three main
things; deposit money, withdraw money, and check your balance. Consider
that the ATM is a frontend node that connects to a backend that will
store this information and display it to the user. It seems as though
the backend does most of the heavy lifting, but an ATM must be made to
be tamper proof, so that a robber cannot pilfer its money.

We\'ll avoid physical security of the ATM itself, and discuss the high
level API and approaches to design an ATM that is resilient to failure.

We\'ll discuss an ideal situation (where the ATM can connect to the
backend), and a network partition (where the ATM cannot connect to the
backend).

In an ideal situation, depositing money, withdrawing money, and checking
your balance is simple; you deposit money, the ATM takes the money you
provide, counts it, and sends a request to the backend to confirm the
money has been accepted. The backend confirms this, and increases the
amount of money in your account. Simple. Withdrawing is the same, after
making sure you have enough money in your account, the ATM removes some
money from its store and presents it to you. Checking your balance is a
simple check with the backend, which won\'t fail since the ATM is
connected to the backend.

In the case of a network partition, this changes. Checking your balance
is not as straightforward. If we have stale data (the value of the
user\'s balance before the network partition), we can display that and
be available, but possibly not correct. We could try to be 100% correct
and not display any balance at all. This is a fundamental trade-off
between consistency and availability.

We could allow the user to deposit money, and persist a log of
transactions to be sent to the backend for reconciliation on disk. That
way, we can sync the ATM to the backend when the network is available
again. If the file size is too big, or there is an I/O error, the ATM
can reject the transaction and depending on the error, shut down the
functionality for depositing until the ATM is reconnected.

Withdrawing becomes tricky; if a user knew that the ATM was not
connected to the backend, and the ATM didn\'t impose any restrictions on
withdrawal, a cheeky user could withdraw all of the money from the ATM.
The ATM would write the withdrawal amount to disk, as with a deposit,
but would have no way to verify that the user hasn\'t withdrawn too
much, and make off with a lot of money. One way to solve this problem is
to disallow withdrawals during a network partition, or make the amount
of money to be withdrawn very small, so it would take a very long time
to take all of the money out of the ATM. Again, we can be available at
the cost of correctness, and some gnarly edge cases.

Transfers (sending money to another account) could also be done in a
network partition, by having a log on file and allowing a resync when
the system is up. Only sending money would be allowed, and would be
disallowed if the log file was full.
