n = int(input())
s=""
while n>0:
    n-=1
    c = chr(ord('a')+n%26)
    s += c
    n//=26
print(s[::-1])