lines = []

with open('input3.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))


# find a path between two cells of the labyrinth
def go_to(_from, _to):
    s = ''
    dx = _from[0] - _to[0]
    for _ in range(abs(dx)):
        s += '>' if dx < 0 else '<'
    dy = _from[1] - _to[1]
    for _ in range(abs(dy)):
        s += 'v' if dy < 0 else '^'
    s += 'x'
    return s


# split coins ('o') and multiplicators ('*')
n = int(lines[0])
mults = []
coins = []
for y in range(n):
    for x in range(n):
        if lines[y + 1][x] == '*':
            mults.append((x, y))
        if lines[y + 1][x] == 'o':
            coins.append((x, y))

# collect all coins first
me = (0, 0)
path = ''
for coin in coins:
    path += go_to(me, coin)
    me = coin

# then, collect all multiplicators
for mult in mults:
    path += go_to(me, mult)
    me = mult

# print the reply
print(path)
