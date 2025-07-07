---
title: "{{date:dddd, MMMM Do, YYYY}}"
date created: Sunday, July 6th 2025, 10:36:20 pm
date modified: Sunday, July 6th 2025, 10:36:40 pm
---

<< [[{{yesterday}}|yesterday]] || [[{{date:YYYY-MM}}|month]] || [[{{tomorrow}}|tomorrow]] >>

# {{date:dddd, MMMM Do, YYYY}}

## Agenda

> [!todo]+ Today
> ```tasks
> not done
> happens {{date:YYYY-MM-DD}}
> hide recurrence rule
> hide due date
> hide scheduled date
> sort by priority
> ```

> [!danger]+ Overdue 
> ```tasks
> not done
> (due before {{date:YYYY-MM-DD}}) OR ((happens before {{date:YYYY-MM-DD}}) AND (priority is above none))
> hide recurrence rule
> sort by due date
> ```

> [!tip]- Next two weeks
> ```tasks
> not done
> happens after {{date:YYYY-MM-DD}}
> happens before {{date+14d:YYYY-MM-DD}}
> hide recurrence rule
> hide due date
> hide scheduled date
> group by happens
