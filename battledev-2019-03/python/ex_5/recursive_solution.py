lines = []

with open('input4.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))


# compute the result, if the current profit == s and we step on the cell containing ch
def apply(ch, s):
    if ch == 'X':
        return s
    if ch == '*':
        return s * 2
    if ch == 'o':
        return s + 1


n = int(lines[0])
corridor = lines[1]

# find the start position and the size of the cache table
i_x = corridor.index('X')
max_right = n - i_x - 1
max_left = (n - max_right - 1)

# gain corresponds to p in the article
gain = [[-1 for _ in range(max_right + 1)] for _ in range(max_left + 1)]
# walks contain the best walks for the segment of the corridor w.r.t. gain
walks = [['na' for _ in range(max_right + 1)] for _ in range(max_left + 1)]

# trivial case - the corridor of length 1
gain[0][0] = 0
walks[0][0] = ''

# we start from the left side of the corridor
for r in range(1, max_right + 1):
    gain[0][r] = apply(corridor[i_x + r], gain[0][r - 1])
    walks[0][r] = walks[0][r - 1] + corridor[i_x + r]
# we start from the right side of the corridor
for l in range(1, max_left + 1):
    gain[l][0] = apply(corridor[i_x - l], gain[l - 1][0])
    walks[l][0] = walks[l - 1][0] + corridor[i_x - l]


# compute, save, and return the pair (gain[i_left, i_right], walks[i_left, i_right])
def solve(i_left, i_right):
    # if already computed, return the content of gain and walks
    if gain[i_left][i_right] >= 0:
        return gain[i_left][i_right], walks[i_left][i_right]
    best = -1
    best_walk = ''
    for r in range(i_right + 1):
        curr, curr_walk = solve(i_left - 1, r)
        curr = apply(corridor[i_x - i_left], curr)
        curr_walk += corridor[i_x - i_left]
        for i_r in range(r + 1, i_right + 1):
            curr = apply(corridor[i_x + i_r], curr)
            curr_walk += corridor[i_x + i_r]
        if curr > best:
            best = curr
            best_walk = curr_walk
    gain[i_left][i_right] = best
    walks[i_left][i_right] = best_walk
    return best, best_walk


print(solve(max_left, max_right))
