lines = []

with open('input1.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))


n = int(lines[0])
s1 = lines[1]
s2 = lines[2]


X = 37
Q = 2 ** 31 - 1
coefficients = []
c = 1
for i in range(n):
    coefficients.append(c)
    c = (c * X) % Q


a = np.zeros(n + 1)
b = np.zeros(n + 1)

# for i in range(n + 1):
#     b[i] = 0
best = 0

for i in range(1, n + 1):
    if i % 100 == 0:
        print(i)
    temp = a
    a = b
    b = temp
    ch1 = s1[i - 1]
    b = np.zeros(n + 1)
    for j, ch2 in enumerate(s2):
        if ch1 == ch2:
            b[j + 1] = a[j] + 1
    best = max(best, np.max(b))

print(int(best))
