# 🗺️ Smart Route Planner Using All-Pair Shortest Path Algorithm

A C++ program that calculates the shortest paths between all pairs of locations using the Floyd-Warshall algorithm.
The system supports dynamic updates such as adding or removing locations, and updating road distances, making it adaptable for route planning in small to medium-sized city networks.

# 📌 Features

✅ Compute shortest paths between all locations using Floyd-Warshall

✅ Dynamic Updates:
    
    1.Add a new location
    
    2.Remove a location
    
    3.Update an edge (distance between two locations)
    
✅ View Shortest Path Matrix

✅ Query Shortest Path between two locations

✅ Path Reconstruction showing the route taken

✅ Text-based User Interface

# 📊 Algorithm Overview

The Floyd-Warshall algorithm works by:

    Starting with a distance matrix for all location pairs.

    Iteratively checking whether a path through an intermediate location is shorter.

    Updating the matrix until all shortest paths are computed.

Time Complexity: O(n³)

Space Complexity: O(n²)

# 🏗️ System Design

Modules:

    Input Module – Accepts city names, distances, and commands

    Processing Module – Implements Floyd-Warshall for shortest paths

    Data Management Module – Stores and updates the graph

    Output Module – Displays matrices and reconstructed paths

Data Structures:

    dist[][] – Distance matrix (INF for no connection)

    next[][] – Stores next node for path reconstruction

    cityToIndex – Maps city names to matrix indices

    indexToCity – Reverse mapping for display

# 📂 Example Menu Interaction

   Menu:
   1. Display shortest path matrix
   2. Query shortest path between two locations
   3. Add a new location
   4. Remove a location
   5. Update an edge
   6. Exit
   Enter your choice:

# 💻 Example Output

 1️⃣ Shortest Path Query

    Enter the source and destination city names: A B
  
    Shortest path: A -> B
  
    Distance: 10

  2️⃣ Shortest Distance Matrix

     0        10       INF       30

     INF        0       50      INF

     INF       INF     0        20

     INF       INF     INF      0

# 🛠️ Installation & Usage
1️⃣ Compile the Program

g++ main.cpp -o route_planner

2️⃣ Run the Program

./route_planner

3️⃣ Follow the Menu Prompts

# 🔮 Future Improvements

  Integrate real-time traffic data

  Create a GUI or mobile app version

  Optimize for sparse graphs

  Support larger networks with advanced algorithms

# 📜 References

  Introduction to Algorithms – Cormen, Leiserson, Rivest, Stein

  GeeksforGeeks – Floyd-Warshall Algorithm

  
