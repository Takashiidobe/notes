---
title: design-a-movie-ticketing-system
---

A Movie Ticketing System

# Design a Movie Ticketing System

Let\'s assume that this is an online system; we have many movie theaters
across the nation. Allow the user to select the movie theater they want.
Allow the user to select which date they want to find a booking. Allow
the user to choose the showing (ie. (unique time + movie for the user)
and (unique time + room + movie theater for the backend)) they want.

We have to allow the user to reserve a seat in the theater. We can show
them an interactive map of the seats for each theater, and have them
reserve a seat for 5 minutes, or if they buy the seat, transition the
seat to bought.

When a user visits the site, they can see all chairs that are not
reserved and not bought.

time room seat_number bought time_to_live

---

unix_time number number boolean unix_time

[design-an-atm](design-an-atm.md): design an atm
