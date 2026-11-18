def bubble_sort(lst):
    n = len(lst)
    for i in range(n - 1):
        swapped = 0
        for j in range(n - 1 - i):
            if lst[j] > lst[j + 1]:
                lst[j + 1], lst[j] = lst[j], lst[j + 1]
                swapped = 1
        if swapped == 0:
            break

def insert_sort(lst):
    n = len(lst)
    for i in range(1, n):
        key = lst[i]
        j = i - 1
        while j >= 0 and lst[j] > key:
            lst[j + 1] = lst[j]
            j -= 1
        lst[j + 1] = key

def select_sort(lst):
    n = len(lst)
    for i in range(n - 1):
        min_index = i
        min_element = lst[i]
        for j in range(i + 1, n):
            if lst[j] < min_element:
                min_index = j
                min_element = lst[j]
        lst[i], lst[min_index] = lst[min_index], lst[i]

def heapify(lst, n, i):    # this func makes a correct max-heap of 3 el
    root = i
    left = 2 * i + 1
    right = 2 * i + 2
    if left < n and lst[left] > lst[root]:
        root = left
    if right < n and lst[right] > lst[root]:
        root = right

    if root != i:
        lst[i], lst[root] = lst[root], lst[i]
        heapify(lst, n, root)


def heap_sort(lst):
    n = len(lst)
    for i in range(n // 2 , -1, -1):    # we build a max-heap
        heapify(lst, n, i)

    for i in range(n - 1, 0, -1):    # then we get the largest
        lst[i], lst[0] = lst[0], lst[i]
        heapify(lst, i, 0)


def partition(lst, low, high):
    pivot = lst[high]
    i = low
    for j in range(low, high):
        if lst[j] < pivot:
            lst[j], lst[i] = lst[i], lst[j]
            i += 1
    lst[i], lst[high] = lst[high], lst[i]
    return i


def quick_sort(lst):
    _quick_sort(lst, 0, len(lst) - 1)

def _quick_sort(lst, low, high):
    if low < high:
        p = partition(lst, low, high)
        _quick_sort(lst, low, p - 1)
        _quick_sort(lst, p + 1, high)


s1 = [bubble_sort, insert_sort, select_sort, heap_sort, quick_sort]
a = [9, 8, 7, 6, 5, 4, 3, 2, 1]
b = [1, 2, 3, 5, 4, 6, 2]
s2 = [a, b]
task_n = int(input("input a task number: "))
for lst in s2:
    s1[task_n - 1](lst)
    print(lst)
