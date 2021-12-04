for _ in range(int(input())):
    k = int(input())

    length = 1
    while k > 9 * 10**(length-1) * length:
        k -= 9 * 10**(length-1) * length
        length += 1
    q, r = divmod(k-1, length)
    print(str(10**(length-1) + q)[r])
