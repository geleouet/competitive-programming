lines = []

with open('input4.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))

n = int(lines[0])


def test(letters, s):
    i = 0
    for ch in s:
        if ch == letters[i]:
            i += 1
            if i == len(letters):
                return True
    return False


def substr(a, source):
    res = ''
    for i in range(len(source)):
        if a % 2 == 0:
            res += source[i]
        a = a // 2
    return res



queries = []
for a in range(1023):
    queries.append(substr(a, lines[1]))
queries.sort(key=lambda q: len(q), reverse=True)


solved = False
for query in queries:
    fail = False
    for line in lines[2:]:
        if not test(query, line):
            fail = True
            break
    if not fail:
        print(query)
        solved = True
        break

if not solved:
    print('KO')


# print(test('abda', 'abracadabra'))
# print(test('abba', 'abracadabra'))
# print(test('ddabda', 'abracadabra'))
