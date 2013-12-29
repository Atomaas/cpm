# Generate random strings

import random

def rotate(s, k):
    return s[k:] + s[:k]

def randrot(s):
    return rotate(s, random.randrange(len(s)))
    
def genstr(length, alphabet = ['A', 'G', 'C', 'T']):
    return ''.join([random.choice(alphabet) for i in range(length)])

def insertpats(text, patterns):
    random.shuffle(patterns)
    positions = sorted(random.sample(range(len(text) + 1), len(patterns)))
    new_text_positions = [positions[0]]
    new_text = text[:positions[0]] + patterns[0]
    i = 1
    while i < len(positions):
        new_text += text[positions[i - 1]:positions[i]]
        new_text_positions.append(len(new_text))
        new_text += randrot(patterns[i])
        i += 1
    new_text += text[positions[i - 1]:]
    return new_text, new_text_positions

def writeString(s, filename):
    with open(filename, 'w') as f:
        f.write(s)

def genTestData():
    for i in range(5, 30 + 1, 5):
        n = i * 1000000
        m = i * 1000
        p1, p2, p3 = genstr(m), genstr(m), genstr(m)
        t = genstr(n - 2*m)
        t, pos = insertpats(t, [p1, p2])
        writeString(p1, 'p' + str(i) + 'a.fas')
        writeString(p2, 'p' + str(i) + 'b.fas')
        writeString(p3, 'p' + str(i) + 'c.fas')
        writeString(t, 't' + str(i) + '.fas')
        print i, pos

genTestData()
