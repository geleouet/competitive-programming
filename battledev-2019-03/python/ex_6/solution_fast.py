lines = []
from time import time
from math import ceil

with open('input3.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))

n = int(lines[0])
s1 = lines[1]
s2 = lines[2]

# t0 = time()
X = 2
Q = 2 ** 31 - 1
coefficients = []
c = 1
for i in range(n):
    coefficients.append(c)
    c = (c * X) % Q


def compute_prefix_hash(s, l):
    hash = 0
    for ch, c in zip(s[:l], reversed(coefficients[:l])):
        hash += ord(ch) * c
    return hash % Q


def update_hash(s, l, old_hash, i_first):
    # return old_hash - ord(s[i_first]) + ord(s[i_first + l])
    hash = old_hash - ((coefficients[l - 1] * ord(s[i_first])) % Q)
    return (hash * X + ord(s[i_first + l])) % Q


def test(s1, s2, i1, i2, length):
    for ch1, ch2 in zip(s1[i1: i1 + length], s2[i2: i2 + length]):
        if ch1 != ch2:
            return False
    return True


def test_len(s1, s2, l):
    n = len(s1)
    hashes = {}
    hash = compute_prefix_hash(s1, l)
    # hash = 42
    hashes[hash] = [0]
    for i in range(n - l):
        hash = update_hash(s1, l, hash, i)
        # hash = i
        if hash in hashes:
            hashes[hash].append(i + 1)
        else:
            hashes[hash] = [i + 1]
    # print(hashes)
    # print(hashes.keys())

    hash = compute_prefix_hash(s2, l)
    for i2 in range(n - l + 1):
        # print(hash)
        if hash in hashes:
            for i1 in hashes[hash]:
                if test(s1, s2, i1, i2, l):
                    return True
        if i2 < n - l:
            hash = update_hash(s2, l, hash, i2)
    return False


# best = 0
# for l in range(1, n + 1):
#     if test_len(s1, s2, l):
#         best = l
#     else:
#         break
# print(best)


def binarySearch(l, r):
    if r > l:
        mid = l + ceil((r - l) / 2)
        # print(l, r, mid)
        # If element is present at the middle itself
        # test_res = test_len(s1, s2, l)
        # print(l, test_res, l, r)
        if test_len(s1, s2, mid):
            return binarySearch(mid, r)
        else:
            return binarySearch(l, mid - 1)
    else:
        return l


print(binarySearch(0, n))
