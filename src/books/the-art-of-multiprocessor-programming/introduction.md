---
title: "Introduction"
---

# Introduction

Next: [mutual-exclusion](mutual-exclusion.md)

## Exercises

Exercise 1.1. The dining philosophers problem was invented by E.W. Dijkstra, a con-
currency pioneer, to clarify the notions of deadlock- and starvation-freedom. Imagine
five philosophers who spend their lives just thinking and feasting on rice. They sit
around a circular table, illustrated in Fig. 1.5. However, there are only five chopsticks (forks, in the original formulation). Each philosopher thinks. When he gets hungry,
he picks up the two chopsticks closest to him. If he can pick up both chopsticks, he
can eat for a while. After a philosopher finishes eating, he puts down the chopsticks
and again starts to think.

1. Write a program to simulate the behavior of the philosophers, where each philosopher is a thread and the chopsticks are shared objects. Note that you must prevent
a situation where two philosophers hold the same chopstick at the same time.
2. Amend your program so that it never reaches a state where philosophers are dead-
locked, that is, it is never the case that every philosopher holds one chopstick and
is stuck waiting for another to get the second chopstick.
3. Amend your program so that no philosopher ever starves.
4. Write a program to provide a starvation-free solution for n philosophers for any
natural number n.

```rs
use arr_macro::arr;
use lazy_static::lazy_static;
use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Duration;

lazy_static! {
    // the amount of philosophers you want
    static ref FORKS: Arc<[Mutex<()>]> = Arc::new(arr![Mutex::new(()); 50]);
}

#[derive(Clone)]
struct Table {
    philosophers: Vec<(usize, usize, usize)>,
}

impl Table {
    fn new() -> Self {
        let mut philosophers = vec![];
        let count = FORKS.len();

        // make the last philosopher left handed
        for i in 1..=count {
            philosophers.push((
                i.saturating_sub(1),
                i.saturating_sub(1) % count.saturating_sub(1),
                if i < count {
                    i % count.saturating_add(1)
                } else {
                    i - 1
                },
            ));
        }

        Table { philosophers }
    }

    fn eat(&self, index: usize) {
        let duration = Duration::from_millis(100);

        let _left = FORKS[self.philosophers[index].1].lock().unwrap();
        thread::sleep(duration);

        let _right = FORKS[self.philosophers[index].2].lock().unwrap();

        println!("{} is eating.", self.philosophers[index].0);

        thread::sleep(duration);

        println!("{} is done eating.", self.philosophers[index].0);
    }
}

fn main() {
    let table = Table::new();

    let round_duration = Duration::from_millis(1000);
    let mut round = 1;

    loop {
        println!("Round {}", round);
        thread::sleep(round_duration);
        let handles: Vec<_> = table
            .philosophers
            .clone()
            .into_iter()
            .enumerate()
            .map(|(index, _)| {
                let table = table.clone();

                thread::spawn(move || {
                    table.eat(index);
                })
            })
            .collect();

        for handle in handles {
            handle.join().unwrap();
        }
        round += 1;
    }
}
```

Exercise 1.2. For each of the following, state whether it is a safety or liveness property. Identify the bad or good thing of interest.

1. Patrons are served in the order they arrive.

Safety: a bad thing that will never happen is that patrons are served
out of order.

2. Anything that can go wrong, will go wrong.

Liveness: something will always go wrong.

3. No one wants to die.

Safety: a correctness property

4. Two things are certain: death and taxes.

Liveness: two things must occur

5. As soon as one is born, one starts dying.

Liveness: progress is always made toward death

6. If an interrupt occurs, then a message is printed within one second.

Safety:

7. If an interrupt occurs, then a message is printed.

Safety

8. I will finish what Darth Vader has started.

Liveness: progress is made toward what darth vader started

9. The cost of living never decreases.

Safety: an invariant

10. You can always tell a Harvard man.

Safety

Exercise 1.3. In the producer-consumer fable, we assumed that Bob can see whether
the can on Alice’s windowsill is up or down. Design a producer-consumer protocol
using cans and strings that works even if Bob cannot see the state of Alice’s can (this is how real-world interrupt bits work).

Have a two cans connected by a string on both Bob and Alice's
windowsill.

Initially, both cans are standing up.

When Alice wants to release the pets:

1. She waits until her can is down.
2. She releases the pets and resets her can.
3. When the pets finish eating, she pulls her string, knocking down
   Bob's can, signaling she is done.

For Bob:

1. He waits until the can on his side is down
2. He puts food in the yard and resets the can on his side.
3. He pulls his string to notify Alice there's food.

Exercise 1.4:

You are one of P recently arrested prisoners. The warden, a deranged computer scientist, makes the following announcement:
you may meet together today and plan a strategy, but after today you will be in isolated cells and have no communication with one another.
I have set up a “switch room” which contains a light switch, which is either on or off. The switch is not connected to anything.
Every now and then, I will select one prisoner at random to enter the “switch room.” This prisoner may throw the switch (from on to off, or vice-versa), or may leave the switch unchanged. Nobody else will ever enter this room.
Each prisoner will visit the switch room arbitrarily often. More precisely, for any N, eventually each of you will visit the switch room at least N times.
At any time, any of you may declare: “we have all visited the switch room at least once.” If the claim is correct, I will set you free. If the claim is incorrect, I will feed all of you to the crocodiles. Choose wisely.

If the state is off:

Select one person to be the consumer and the others as producers.

The producers follow this protocol:

1. Turn on the light if it was off and they haven't turned it on before.
2. Do nothing (if they turned it off before or the light is on).

The consumer then:

1. Turns off the light and increments their counter if the lamp is on.
When the counter hits N - 1, declare all of us have been in the room at
least once.
2. Do nothing (if the lamp is off)

If the initial state is either on or off, then you should do the same,
except producers turn on the light twice, and the consumer counts to (2
* N - 1)

Exercise 1.5. The same warden has a different idea. He orders the prisoners to stand
in line, and places red and blue hats on each of their heads. No prisoner knows the
color of his own hat, or the color of any hat behind him, but he can see the hats of
the prisoners in front. The warden starts at the back of the line and asks each prisoner
to guess the color of his own hat. The prisoner can answer only “red” or “blue.” If
he gives the wrong answer, he is fed to the crocodiles. If he answers correctly, he is
freed. Each prisoner can hear the answer of the prisoners behind him, but cannot tell
whether that prisoner was correct.
The prisoners are allowed to consult and agree on a strategy beforehand (while
the warden listens in) but after being lined up, they cannot communicate any other
way besides their answer of “red” or “blue.”
Devise a strategy that allows at least P − 1 of P prisoners to be freed.

The prisoners need to do the following:

The first prisoner counts the number of red and blue hats. If red is
odd, he says red, otherwise blue. The next prisoner then counts the
number of red hats. If the number is odd, but the previous prisoner said
red, he knows he has a blue hat. He says blue. Otherwise, he has a red
hat, so he says red. Every other prisoner follows the same protocol.

Exercise 1.6. A financial risk management program is sped up by making 85% of
the application concurrent, while 15% remains sequential. However, it turns out that
during a concurrent execution the number of cache misses grows in a way dependent
on N , the number of cores used. The dependency is CacheMiss = N
N +10 . Profiling the program reveals that 20% of the operations performed are memory accesses for both the sequential and parallel parts. The cost of other operations, including cache
accesses, is 1 unit, and accessing memory has a cost of 3N + 11 units for the parallel part and a cost of 14 for the sequential part. Compute the optimal number of
processors on which the program should run.

Exercise 1.9 You have a choice between buying one uniprocessor that executes five
zillion instructions per second or a 10-processor multiprocessor where each processor
executes one zillion instructions per second. Using Amdahl’s law, explain how you
would decide which to buy for a particular application.

Next: [mutual-exclusion](mutual-exclusion.md)
