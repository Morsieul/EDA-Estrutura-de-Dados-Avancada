#MaxHeap 

def maxheapfy (a, i):
    l = 2*i
    r = 2*i + 1 
    if l <= len(a) and a[l] > a[i]: 
        largest = l
    else:
        largest = i
    if r <= len(a) and a[r] > a[largest]:
        largest = r
    if largest != i:
        a[i], a[largest] = a[largest], a[i]
        maxheapfy(a, largest)
    return a

exa = [0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1]

print(maxheapfy(exa, 2))