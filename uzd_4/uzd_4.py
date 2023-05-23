class Node:
    cost = float("inf")
    visited = False
    previous = "-"

cities = set()
def get_flights_matrix(data_file_path):
    dict = {}
    f = open(data_file_path, "r")
    for line in f:
        elements = line.strip().split(" ")
        cities.add(elements[0])
        cities.add(elements[0])
        if not elements[0] in dict:
            dict[elements[0]] = {}
        if not elements[1] in dict[elements[0]] or int(elements[2]) < dict[elements[0]][elements[1]]:
            dict[elements[0]][elements[1]] = int(elements[2])    
    return dict

dict = get_flights_matrix("data.txt")
print(dict)

def dijsktra(city_1, city_2, dict):
    nodes = {}
    for city in cities:
        nodes[city] = Node()
    src_city = city_1
    nodes[src_city].cost = 0
    while src_city != city_2:
        for sec_city in dict[src_city].keys():
            if nodes[src_city].cost + dict[src_city][sec_city] < nodes[sec_city].cost:
                nodes[sec_city].cost = nodes[src_city].cost + dict[src_city][sec_city]
                nodes[sec_city].previous = src_city
        nodes[src_city].visited = True
        min_cost = float("inf")
        for city in cities:
            if not nodes[city].visited and nodes[city].cost < min_cost:
                min_cost = nodes[city].cost
                src_city = city
        if min_cost == float('inf'):
            return -1
    return nodes[city_2].cost

        
print(dijsktra("A", "E", dict))
        
            


    
    
