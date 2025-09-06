---
title: active-record-vs-data-mapper
date created: Tuesday, July 22nd 2025, 6:53:06 pm
date modified: Tuesday, July 22nd 2025, 7:23:56 pm
---

The ActiveRecord pattern involves having an in-memory Object that can be manipulated for each row in a table:

```ruby
part = Part.new()
part.name = "Part Name"
part.price = 20.34
part.save() # save to db
```

At the `.save()` call, the calling code will materialize the object to the database:

```sql
INSERT INTO parts(name, price) VALUES('Part Name', 20.34);
```

You can also query with it:

```rb
p = Part.find(0) # get the first part
```

The DataMapper pattern separates 