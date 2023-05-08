# Find matching version ranges

> In android, APKs contain a manifest that contains minimum and maximum SDK versions
> Min and Max SDK versions are optional and inclusive.
> A developer can upload multiple APKs with different manifests like
> APK MinSDKVer MaxSDKVer
> A   4         inf
> B   1         16
> C   7         10
>
> Since we have multiple APKs per App, we need to divide the integer list of SDK versions
> into intervals that match the APKs.
> [(<=3), (4-6), (7-10), (11-16), (>=17)] # possible intervals.
> <=3 is only B, 4-6 is B and A but not C, etc...
> Use whatever sensible data structure you want to represent input and output

## Answer

Imagine an input and output like this:

input = {'A': (4, None), 'B': (None, 16), 'C': (7, 10) }
output = [(1, 3), (4, 6), (7-10), (11-16), (17, None)]

You don't want to use an array for this, because most slots could be empty.

Instead, insert each item to a sorted set, and iterate through it with two pointers to get each range.

## Notes

This will take O(n log n) time. You can also use a normal list and sort at the end, since we don't require insertions + deletions.

Followups could be to ask if versions follow into a certain bucket - what sort version would you use in this case?
