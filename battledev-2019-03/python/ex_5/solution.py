lines = []

with open('input4.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))


def apply(ch, s):
    if ch == 'X':
        return s
    if ch == '*':
        return s * 2
    if ch == 'o':
        return s + 1


n = int(lines[0])
corridor = lines[1]

for i, ch in enumerate(corridor):
    if ch == 'X':
        i_x = i

# print(i_x)
max_right = n - i_x - 1
max_left = (n - max_right - 1)

gain = [[-1 for _ in range(max_right + 1)] for _ in range(max_left + 1)]
walks = [['' for _ in range(max_right + 1)] for _ in range(max_left + 1)]

gain[0][0] = 0
for i_right in range(max_right + 1):
    if i_right > 0:
        gain[0][i_right] = apply(corridor[i_x + i_right], gain[0][i_right - 1])
        walks[0][i_right] = walks[0][i_right - 1] + corridor[i_x + i_right]
    # print('i_right =', i_right)
    for i_left in range(0, max_left):
        best = 0
        best_walk = ''
        for r in range(i_right + 1):
            curr_walk = walks[i_left][r]
            curr = gain[i_left][r]
            curr = apply(corridor[i_x - i_left - 1], curr)
            curr_walk += corridor[i_x - i_left - 1]
            # print(i_right, i_left, corridor[i_x - i_left - 1])
            for i_r in range(r + 1, i_right + 1):
                curr = apply(corridor[i_x + i_r], curr)
                curr_walk += corridor[i_x + i_r]
            if curr > best:
                best = curr
                best_walk = curr_walk
            if best_walk == '':
                best_walk = curr_walk
        gain[i_left + 1][i_right] = best
        walks[i_left + 1][i_right] = best_walk
        # print(i_left, i_right, best, best_walk)
    # best = 0
    # for l in range(max_left):
    #     curr = gain[l][i_right]
    #     curr = apply(corridor[i_x + i_right + 1], curr)
    #     for i_l in range(l + 1, i_left + 1):
    #         curr = apply(corridor[i_x - i_l], curr)
    #     if curr > best:
    #         best = curr
    # gain[max_left][i_right + 1] = best

# print(gain[max_left][max_right])
print(walks[max_left][max_right])

# for l in range(max_left + 1):
    # print(gain[l])
