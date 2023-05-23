import random

cities = ["Vilnius", "London", "Paris", "Tokyo", "Sydney", "Rome", "Dubai", "Moscow", "Toronto", "Berlin"]
num_flights = 50
f = open("data.txt", "w")

for _ in range(num_flights):
    city1 = random.choice(cities)
    city2 = random.choice(cities)
    
    # Ensure city1 and city2 are different
    while city1 == city2:
        city2 = random.choice(cities)
    
    cost = random.randint(100, 1000)
    f.write(f"{city1} {city2} {cost}\n")

f.close()