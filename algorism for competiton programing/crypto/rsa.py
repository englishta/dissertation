# Public Key
E = 5
N = 323

# Private Key
D = 29
N=323

# Message hirabun
M=100

# Crpytogram
# C=12
C = pow(M, E, N)

print("C=", C)
print(pow(C, D, N))