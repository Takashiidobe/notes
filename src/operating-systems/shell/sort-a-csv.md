---
title: Sort a CSV
date created: Friday, May 12th 2023, 5:07:55 pm
date modified: Tuesday, November 12th 2024, 8:31:02 pm
---

# Sort a CSV

You can sort a csv using the `sort` command.

This sorts the file by the 2nd and 3rd columns while skipping the
header.

```sh
head -1 file_to_sort.csv > output.csv
tail -n+2 file_to_sort.csv | sort --field-separator=',' -k2,3 >> output.csv
mv output.csv file_to_sort.csv
```
