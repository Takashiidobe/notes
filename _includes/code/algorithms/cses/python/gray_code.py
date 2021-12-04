x = int(input())

result = [bin(i ^ (i // 2))[2:].zfill(x) for i in range(pow(2, x))]

print(*result, sep='\n')
