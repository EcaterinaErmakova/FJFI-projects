from typing import DefaultDict
INT_MAX = 2147483647
# Function to find the minimum
# cost path for all the paths
def findMinRoute(tsp):
    sum, counter, i, j = 0
    min = INT_MAX
    visitedRouteList = DefaultDict(int)
    # Starting from the 0th indexed
    # city i.e., the first city
    visitedRouteList[0] = 1
    route = [0] * len(tsp)
    # Traverse the adjacency
    # matrix tsp[][]
    while i < len(tsp) and j < len(tsp[i]):
        # Corner of the Matrix
        if counter >= len(tsp[i]) - 1:
            break
        # If this path is unvisited then
        # and if the cost is less then
        # update the cost
        if j != i and (visitedRouteList[j] == 0):
            if tsp[i][j] < min:
                min = tsp[i][j]
                route[counter] = j + 1
        j += 1
        # Check all paths from the
        # ith indexed city
        if j == len(tsp[i]):
            sum += min
            min = INT_MAX
            visitedRouteList[route[counter] - 1] = 1
            j = 0
            i = route[counter] - 1
            counter += 1
    # Update the ending city in array
    # from city which was last visited
    i = route[counter - 1] - 1
    for j in range(len(tsp)):
        if (i != j) and tsp[i][j] < min:
            min = tsp[i][j]
            route[counter] = j + 1
    sum += min
    # Started from the node where
    # we finished as well.
    print("Minimum Cost is :", sum)


class ShortestPathSolver:
    
    def __init_table(self):
        self.processed = [False]*self.__n
        self.parent = [-1] * self.__n
        self.distance = [10e6] * self.__n

    def solve(self, starting_index, graph):
        self.__n = len(graph)
        self.__init_table()
        self.processed[starting_index] = True
        self.distance[starting_index] = 0
        current_node_index = starting_index

        while current_node_index is not None:
            self.__process_node(graph, current_node_index)
            current_node_index = self.__find_next_node()
        print(f"Parent: {self.parent}")
        print(f"Distance: {self.distance}")

    def __find_next_node(self):
        min_distance=float('inf')
        index = None
        for value in range(self.__n):
            if not self.processed[value] and self.distance[value]<min_distance:
                min_distance = self.distance[value]
                index = value
        return index
                
    def __process_node(self, graph, index):
        self.processed[index] = True
        for value in range(self.__n):
            if self.processed[value]: continue
            edge = graph[index][value]
            if self.distance[value] > self.distance[index] + edge:
                self.parent[value] = index
                self.distance[value] = self.distance[index] + edge

