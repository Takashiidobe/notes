from collections import Counter 
s = input()

def reorder(s):
    counter = Counter(s)

    odd_count = 0

    left = ''
    mid = ''
    right = ''

    for c, i in counter.items():
        if i % 2 != 0:
            odd_count += 1
            mid += c * i
        else:
            left += c * (i // 2) 
            right += c * (i // 2)
        
    right = right[::-1] 
    if odd_count > 1:
        print("NO SOLUTION")
    else:
        print(left + mid + right)
    

reorder(s)
