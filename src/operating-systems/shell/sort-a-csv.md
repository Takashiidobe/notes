---
title: sort-a-csv
---

a CSV

# Sort a CSV

You can sort a csv using the `sort` command.

This sorts the file by the 2nd and 3rd columns while skipping the
header.

```sh
head -1 file_to_sort.csv > output.csv
tail -n+2 file_to_sort.csv | sort --field-separator=',' -k2,3 >> output.csv
mv output.csv file_to_sort.csv
```
