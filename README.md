# Village Navigation and Insight System Using Graph Algorithms in C++

## Overview
This project leverages graph algorithms to create an advanced navigation and insight system tailored for a village setting. By utilizing a dataset comprising 300 nodes and over 700 edges, the system demonstrates practical applications of various algorithms and data structures in real-world scenarios.

## Dataset
- **Nodes:** 300 nodes representing specific places in the village, each with unique identifiers, types, and names.
- **Edges:** Over 700 edges representing road segments, with properties including start and end points, length, and accessibility flags for walking, biking, and driving. Edges are also categorized by road type (main road, highway, etc.).

## Algorithms and Data Structures
The project employs several key algorithms and data structures:
- **Graph Traversal Algorithms:** Breadth-First Search (BFS) and Depth-First Search (DFS) for exploring the village layout.
- **Shortest Path Algorithms:** Dijkstra's algorithm for finding the minimum distance between nodes.
- **Backtracking:** Used for exploring all possible paths in specific scenarios.
- **Custom Functions:** Implemented to handle various queries and provide detailed insights.

## Key Functionalities

### Connectivity and Essential Services
- **Functionality:** Allows new users to determine the connectivity of places and the distance to essential services.
- **Benefit:** Helps users assess the accessibility of different areas within the village.

### Shortest Path Calculation
- **Functionality:** Enables users to find the shortest path between two places, considering different modes of transportation and road types.
- **Benefit:** Provides efficient navigation tailored to the user's preferences.

### Optimal Route Planning
- **Functionality:** Given a list of places to visit, the system provides an optimal sequence and route that minimizes total travel distance.
- **Benefit:** Ideal for planning daily activities or tours, saving time and effort.

### Time Estimation
- **Functionality:** Estimates travel time based on the mode of transportation (walking, biking, driving) and provides specific routes accordingly.
- **Benefit:** Ensures accurate travel planning by considering the accessibility of each road segment for different transportation modes.

## Edge Class Definition
The `Edge` class includes the following attributes:
- **Start and End Points:** Nodes representing the start and end of the road segment.
- **Length:** Distance of the road segment.
- **Accessibility:** Boolean flags indicating if walking, biking, or driving is possible on the segment.
- **Road Type:** Classification of the road (main road, highway, etc.).

## Practical Application
The system aims to offer detailed and practical navigation and insights for a village or city, providing:
- The shortest and most efficient routes to various destinations.
- Travel time estimates based on the chosen mode of transportation.
- Recommendations for the best sequence of places to visit, minimizing travel distance and time.

## Conclusion
This project highlights the powerful capabilities of graph algorithms and data structures in solving real-world navigation problems. By simulating a village's road network and providing essential insights, the system serves as a valuable tool for residents and visitors alike, offering a seamless and efficient way to navigate and explore the area.

## File Structure and Functions

### DataSetUp.h
- **DataExtract():** Function to extract and set up the dataset.
- **addEdge():** Function to add an edge to the graph.

### FindingMinmumDistance
- **NearServiceFromHome():** Function to find the nearest service from a given home location.

### MultiplePlace
- **Multipleinput():** Function to handle multiple inputs for places to visit.

### PathBYMode
- **NearServiceFromHomeBYmode():** Function to find the nearest service from home based on the mode of transportation.

### TimeAsPerMode
- **NearServiceFromHomeB():** Function to find the nearest service from home considering the travel time per mode.
- **PlaceTime():** Function to estimate travel time to a place based on the mode of transportation.

### CheckTheConnectivityOfPlace
- **TellMeTheOverallConnectivityOfMyPlace():** Function to determine the overall connectivity of a place.