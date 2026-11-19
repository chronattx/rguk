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
    for vert in range(len(graph)):
        if graph[vert][start] and vert not in was:
            dfs(graph, vert, was)
    return was

def bfs(graph: List[List[int]], start: int) -> List[int]:
    was = [start]
    queue = Queue([start])

    while not queue.empty():
        current_vert = queue.dequeue()

        for vert in range(len(graph)):
            if graph[current_vert][vert] and vert not in was:
                was.append(vert)
                queue.enqueue(vert)
    return was


def dijkstra(graph: List[List[int]], start: int, finish: int) -> List[int]:
    distances = [float("infinity") for _ in range(len(graph))]
    used = [-1 for _ in range(len(graph))]
    distances[start] = 0

    for _ in range(len(graph)):

        min_dist_vert = -1                # first, we find a vertex with minimal current distance
        for vert in range(len(graph)):
            if used[vert] == -1 and (min_dist_vert == -1 or distances[vert] < distances[min_dist_vert]):
                min_dist_vert = vert

        used[min_dist_vert] = 1
        if min_dist_vert == finish:
            return distances[min_dist_vert]
        
        for vert in range(len(graph)):
            dist = graph[vert][min_dist_vert]    # second, we relax incident edges
            if dist == 0:
                continue
            distances[vert] = min(distances[min_dist_vert] + dist, distances[vert])

def shortest_path_bfs(graph: List[List[int]], start: int, finish: int) -> List[int]:
    was = [(0, 0) for _ in range(len(graph))]
    was[start] = (1, -1)
    queue = Queue([start])
       
    while not queue.empty():
        current_vert = queue.dequeue()
        
        for vert in range(len(graph)):
            if graph[current_vert][vert] and was[vert][0] == 0:
                was[vert] = (1, current_vert)
                if vert == finish:
                    break
                queue.enqueue(vert)

    path = []
    current_vert = finish
    while current_vert != start:
        path.append(current_vert)
        current_vert = was[current_vert][1]
    path.append(start)

    return path[::-1]



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
print(dfs(graph, 0), "\n")

print(bfs(graph, 4))
print(bfs(graph, 0), "\n")

weighted_graph = [
 [0, 4, 0, 2, 9, 0, 0, 0],
 [4, 0, 3, 0, 0, 0, 0, 0],
 [0, 3, 0, 8, 0, 0, 4, 0],
 [2, 0, 8, 0, 0, 6, 0, 0],
 [9, 0, 0, 0, 0, 1, 0, 0],
 [0, 0, 0, 6, 1, 0, 0, 3],
 [0, 0, 4, 0, 0, 0, 0, 2],
 [0, 0, 0, 0, 0, 3, 2, 0]
]

print(dijkstra(weighted_graph, 0, 7))
print(dijkstra(weighted_graph, 2, 4), "\n")

print(shortest_path_bfs(graph, 0, 7))
print(shortest_path_bfs(graph, 1, 5))
print(shortest_path_bfs(graph, 2, 4), "\n")

print(dijkstra(graph, 0, 7))
print(dijkstra(graph, 1, 5))
print(dijkstra(graph, 2, 4), "\n")