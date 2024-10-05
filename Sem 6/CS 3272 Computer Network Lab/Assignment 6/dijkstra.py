class UndirectedGraph:
    def __init__(self) -> None:
        self.edges = dict()

    def add_edge(self,
                 initial_node: str,
                 final_node: str,
                 edge_wt: int) -> None:
        self.edges.setdefault(initial_node, []).append((edge_wt, final_node))
        self.edges.setdefault(final_node, []).append((edge_wt, initial_node))

    def __str__(self) -> str:
        for (key, value) in self.edges.items():
            print(f"{key} -> {value}")
        return ""

    def print_adjacency_matrix(self):
        self.__str__()

    def dijkstra(self, initial_node: str) -> dict:
        # import heap stuffs
        from heapq import heappush, heappop

        if initial_node not in self.edges.keys():
            raise Exception("Initial node not in graph")

        # initialization
        # visited_nodes = {initial_node}
        distance_vector = {initial_node: 0}
        heap = []

        # add neighboring edges of the initial node to the heap
        for (edge_wt, node_adj_to_initial_node) in self.edges[initial_node]:
            heappush(heap, (edge_wt, node_adj_to_initial_node))

        # loop part of the specified algo
        while len(distance_vector.keys()) != len(self.edges.keys()):

            # find  minimum edge which has node not in the visited_nodes
            while True:
                if len(heap) == 0:
                    raise Exception("Heap is empty when it should not be")
                min_edge_wt, min_edge_node = heappop(heap)
                if min_edge_node not in distance_vector.keys():
                    break

            # this min_edge is greedily selected and is reflected to the
            # return values
            distance_vector[min_edge_node] = min_edge_wt

            # add all the neighboring edges wrt current min_node to the heap
            for (edge_wt,
                 node_adj_to_min_edge_node) in self.edges[min_edge_node]:
                heappush(
                    heap,
                    (min_edge_wt + edge_wt,  node_adj_to_min_edge_node)
                )

        return distance_vector


def test_dijkstra_algo():
    undirected_graph = UndirectedGraph()
    undirected_graph.add_edge('A', 'B', 4)
    undirected_graph.add_edge('A', 'C', 5)
    undirected_graph.add_edge('A', 'D', 3)
    undirected_graph.add_edge('B', 'C', 2)
    undirected_graph.add_edge('B', 'F', 3)
    undirected_graph.add_edge('B', 'G', 4)
    undirected_graph.add_edge('C', 'D', 6)
    undirected_graph.add_edge('C', 'E', 4)
    undirected_graph.add_edge('C', 'F', 4)
    undirected_graph.add_edge('D', 'E', 3)
    undirected_graph.add_edge('E', 'F', 2)
    undirected_graph.add_edge('F', 'G', 5)

    print("Adjacency Matrix")
    undirected_graph.print_adjacency_matrix()

    distance_vector = undirected_graph.dijkstra('A')

    print("A's Distance Vector")
    for key, value in distance_vector.items():
        print(f"{key}: {value}")

    nodes_taken = "".join(distance_vector.keys())
    print(f"nodes taken in order: {nodes_taken}")


if __name__ == "__main__":
    test_dijkstra_algo()
