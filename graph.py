from typing import List

class Queue:
    def __init__(self, queue_list: List[int] = []):
        self.queue_list = queue_list

    def enqueue(self, digit: int):
        self.queue_list.append(digit)

    def dequeue(self) -> int:
        return self.queue_list.pop(0)

    def empty(self) -> bool:
        return len(self.queue_list) == 0


def dfs(graph: List[List[int]], start: int, was: List[int] = None) -> List[int]:
    if was is None:
        was = []
    was.append(start)
    for vert in range(len(graph[start])):
        if graph[vert][start] and vert not in was:
            dfs(graph, vert, was)
    return was

def bfs(graph: List[List[int]], start: int) -> List[int]:
    was = [start]
    queue = Queue([start])

    while not queue.empty():
        current_vert = queue.dequeue()

        for vert in range(len(graph[current_vert])):
            if graph[current_vert][vert] and vert not in was:
                was.append(vert)
                queue.enqueue(vert)
    return was


def dijkstra():
    pass


graph = [
 [0, 1, 0, 1, 1, 0, 0, 0],
 [1, 0, 1, 0, 0, 0, 0, 0],    #     1 -- 2
 [0, 1, 0, 1, 0, 0, 1, 0],    #    /    / \
 [1, 0, 1, 0, 0, 1, 0, 0],    #   0 -- 3   6
 [1, 0, 0, 0, 0, 1, 0, 0],    #    \    \   \
 [0, 0, 0, 1, 1, 0, 0, 1],    #     4 -- 5 - 7
 [0, 0, 1, 0, 0, 0, 0, 1],
 [0, 0, 0, 0, 0, 1, 1, 0]
]

print(dfs(graph, 4))
print(dfs(graph, 0))

print(bfs(graph, 4))
print(bfs(graph, 0))
