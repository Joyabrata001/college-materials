class Router:
    def __init__(self, router_name: str) -> None:
        # key is router name and value is the distance vector from it,
        # this will keep on changing
        # key not present means that distance from self to other router in inf
        self.__distance_vector = {router_name: 0}
        # key is a string and value is the dist from it,
        # this will most probably be same
        self.__neighbors = dict()
        self.__router_name = router_name

    def add_neighbor(self, other_router_name: str, dist: int) -> None:
        # if other_router_name already present,
        # set minimum of already present value else set dist
        self.__neighbors[other_router_name] = dist \
            if other_router_name not in self.__neighbors.keys() \
            else min(dist,  self.__neighbors[other_router_name])

        self.__distance_vector[other_router_name] = dist \
            if other_router_name not in self.__distance_vector.keys() \
            else min(dist, self.__distance_vector[other_router_name])

    def update_dv(
            self,
            other_router_name: str,
            other_distance_vector: dict[str, int],
            verbose=False) -> None:

        if other_router_name == self.__router_name:
            return

        if other_router_name not in self.__neighbors.keys():
            raise Exception("error: got distance vector from non neighbor")

        if verbose:
            print(
                f"{other_router_name} gave {other_distance_vector}"
                f" to {self.__router_name}, edge dist ="
                f" {self.__neighbors[other_router_name]}")

            print(f"initial dv: {self.__distance_vector}")

        for key, value in other_distance_vector.items():
            self.__distance_vector[key] =\
                value + self.__neighbors[other_router_name] \
                if key not in self.__distance_vector.keys() \
                else min(self.__distance_vector[key],
                         value + self.__neighbors[other_router_name]
                         )

        if verbose:
            print(f"updated dv: {self.__distance_vector}")
            print()

    def get_distance_vector(self) -> dict[str, int]:
        return self.__distance_vector

    def get_neighbors(self) -> dict[str: int]:
        return self.__neighbors

    def print_distance_vector(self) -> None:
        print(f"{self.__router_name} ->", end="")
        print(" { ", end="")
        for key, value in sorted(
            self.__distance_vector.items(), key=lambda x: x[0]
        ):
            print(f"{key}: {value}, ", end="")
        print("}")


class UndirectedNetwork:
    def __init__(self) -> None:
        # key is router name and the value is a router object
        self.__routers = dict()

    def add_edge(self, initial_router_name: str,
                 final_router_name: str,
                 link_weight: int) -> None:

        if initial_router_name == final_router_name:
            return

        self.__routers.setdefault(
            initial_router_name,
            Router(router_name=initial_router_name)
        ).add_neighbor(final_router_name, link_weight)

        self.__routers.setdefault(
            final_router_name,
            Router(router_name=final_router_name)
        ).add_neighbor(initial_router_name, link_weight)

    def share_distance_vector(
            self,
            sender_router_name: str,
            receiver_router_name: str) -> None:

        if sender_router_name not in self.__routers.keys():
            raise Exception('error: sender router name invalid')

        if receiver_router_name not in self.__routers.keys():
            raise Exception('error: receiver router name invalid')

        self.__routers[receiver_router_name].update_dv(
            sender_router_name,
            self.__routers[sender_router_name].get_distance_vector()
        )

    def print_distance_vectors(self) -> None:
        for _, value in sorted(self.__routers.items(), key=lambda x: x[0]):
            value.print_distance_vector()

    def distance_vector_routing(self, num_iter: int):
        for num in range(num_iter):
            print(f"iter {num}:")
            for router_name, router in self.__routers.items():
                for neighbor_name in router.get_neighbors().keys():
                    self.share_distance_vector(
                        router_name, neighbor_name
                    )
            self.print_distance_vectors()


def distance_vector():
    network = UndirectedNetwork()

    network.add_edge("u", "v", 1)
    network.add_edge("u", "y", 2)
    network.add_edge("v", "x", 3)
    network.add_edge("v", "z", 6)
    network.add_edge("x", "y", 3)
    network.add_edge("x", "z", 2)

    network.distance_vector_routing(num_iter=3)


if __name__ == "__main__":
    distance_vector()
