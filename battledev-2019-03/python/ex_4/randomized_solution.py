import random

lines = []
with open('input4.txt') as input_file:
    for line in input_file:
        lines.append(line.rstrip('\n'))


# test if word contains query as a subsequence
def word_contains(word, query):
    i = 0
    for ch in word:
        if ch == query[i]:
            i += 1
            if i == len(query):
                return True
    return False


# test if all words contains query as a subsequence
def test_subsequence(query, words):
    for w in words:
        if not word_contains(w, query):
            return False
    return True


n = int(lines[0])
words = lines[1:]

max_len, best = 0, 'KO'
for _ in range(10000):
    # create a random query
    query = ''.join(random.sample(words[0],  random.randint(1, 10)))
    # test the query only if it is longer than current maximal length
    if len(query) > max_len and test_subsequence(query, words[1:]):
        max_len = len(query)
        best = query

# print the result
print(best)
