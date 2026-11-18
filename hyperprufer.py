from typing import List


def connections(incidence: List[List[int]], vert: int) -> List[int]:
    """
    Returns a list of edges incident to vertex.
    
    :param incidence: an incidence matrix (rows — edges, cols — verts).
    :param vert: an index of a vertex.
    :return: a list of edges incident to vertex.
    """
    connected_edges = []
    for edge_i in range(len(incidence)):
        if incidence[edge_i][vert] == 1:
            connected_edges.append(edge_i)
    return connected_edges

def find_leaf_edge(incidence: List[List[int]]) -> int:
    """
    Finds a leaf edge with the lowest index vertex.
    Leaf edge is such an edge, that contains only one vertex incident to other edges.

    :param incidence: an incidence matrix (rows — edges, cols — verts).
    :return: an index of a leaf edge.
    """
    for vert in range(len(incidence[0])):                    # we search for a vertex incident to only one edge.
        connected_edges = connections(incidence, vert)
        if len(connected_edges) != 1:
            continue
        edge_i = connected_edges[0]
        much_connected = 0
        for vert_i in range(len(incidence[0])):              # then we check if this edge is a leaf by counting 
            if incidence[edge_i][vert_i] == 1:               # the connections of each incident vert.
                if len(connections(incidence, vert_i)) > 1:
                    much_connected += 1
        if much_connected == 1:
            return edge_i
                  
def coder(incidence: List[List[int]]) -> str:
    """
    Makes a Prufer code for a hypergraph.

    :param incidence: an incidence matrix (rows — edges, cols — verts).
    :return: a string code.
    """
    work = incidence.copy()                # a work matrix, where edges will be erased
    code = ""
    for _ in range(len(incidence) - 1):
        edge = find_leaf_edge(work)
        much_connected = None
        lower = None
        for vert in range(len(work[edge])):
            if work[edge][vert]:
                if len(connections(work, vert)) > 1:
                    much_connected = vert
                else:
                    if lower is None:
                        lower = vert
                    else:
                        code += str(vert) + ' '
                work[edge][vert] = 0
        code += str(much_connected) + ' '
    return code


def decoder(prufer_code: str, edge_size: int) -> List[List[int]]:
    """
    Reads a Prufer code for a hypergraph and returns an incidence matrix
    
    :param prufer_code: a string with code.
    :param edge_size: how many verts are incident to one edge.
    """
    list_code = [int(x) for x in prufer_code.split()]
    n = (len(list_code) // (edge_size - 1) + 1) * edge_size
    hidden_verts = [x for x in range(n) if x not in list_code]
    incidence = [[0 for _ in range(n)] for _ in range(n - 1)]

    for _ in range(n - 1):
        edge = []
        edge.append(hidden_verts.pop(0))
        for _ in range(edge_size - 2):
            edge.append(list_code.pop(-1))
        edge.append(list_code.pop(-1))
        if edge[-1] not in list_code:
            pass

def get_incidence(hyperedges: List[List[int]]) -> List[List[int]]:
    """
    Makes an incidence matrix from a list of hyperedges.

    :param hyperedges: a list of hyperedges, hyperedges are lists of connected verteces.
    :return: a matrix (list of lists), where rows are edges, cols are verts. 1 if incident, else 0. 
    """
    n = max(max(x) for x in hyperedges)
    incidence = [[0 for _ in range(n + 1)] for _ in range(len(hyperedges))]
    for i in range(len(hyperedges)):
        for vert in hyperedges[i]:
            incidence[i][vert] = 1
    return incidence

s1 = [[3, 4, 5], [0, 1, 2], [0, 3, 6], [6, 7, 8], [7, 9, 10]]
i1 = get_incidence(s1)
# print(i1)

s2 = [[5, 6, 3], [1, 3, 4], [0, 1, 2], [2, 7, 8]]
i2 = get_incidence(s2)
# print(i2)
# print(find_leaf_edge(i2))
print(coder(i2))