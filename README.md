# CSE 030 Final Project: Airport Flight Planner

## Overview

This project is a team-based C++ application for planning air travel between airports. Users can select a starting airport, a destination, and a routing preference:

- **Cheapest cost**  
- **Shortest travel time**  
- **Fewest stops**  

The application computes an optimal flight path and displays a complete itinerary with all intermediate stops, total cost, total travel time, and number of stops.

Airports and flights are represented as a graph, where vertices are airports and edges are direct flights with associated weights for cost and travel time. Not all airports are directly connected, allowing for realistic travel scenarios. Depending on the selected preference, the application can recommend a multi-leg route if it is cheaper, faster, or requires fewer stops than a direct flight.

---

## Features

### Graph-Based Data Structure
- Vertices represent airports  
- Edges represent flights with weights for cost and travel time  
- Search algorithms implemented:
  - **Breadth-First Search (BFS):** find paths with the fewest stops  
  - **Uniform Cost Search (UCS):** find optimal cost or time paths  
  - **Depth-First Search (DFS):** additional exploration method  

### Interactive GUI with Bobcat UI
- FLTK-based window providing a **visible interface**  
- Dropdown menus for selecting starting and destination airports  
- Buttons for choosing routing preferences (**Cheapest**, **Shortest Time**, **Least Stops**)  
- Scrollable results area displaying itinerary details  
- Text boxes for showing flight segments and summary information  

### Data-Driven Approach
- Airports and flight routes are loaded from **CSV files**  
- Files are easily modifiable to add more airports or flights  

### Memory Management
- Careful use of dynamic memory in graph implementation  
- Waypoints and edges are cleaned up to prevent memory leaks

## Data Files
The application uses two CSV files located in the `assets/` directory:
* `assets/vertices.csv`: Contains airport names.
* `assets/edges.csv`: Contains flight information (start index, destination index, travel time, and cost).

## Technologies Used
* **C++**: Core algorithms and object-oriented design.
* **Bobcat UI (FLTK-based)**: GUI development.
* **Graph Theory**: Vertex, Edge, and Waypoint classes.
* **Make**: Automated building and compilation.

---

## Contributors

* Rajer That
* Noblion
* 1nfernl
* Anish Kaushik

**All team members contributed to:**
* Graph implementation and search algorithms.
* Bobcat UI GUI interface.
* Data handling and memory management.

---

## Notes
* Demonstrates graph algorithms, GUI integration, and dynamic memory management.
* The CSV input structure makes it easy to extend the network of airports and routes.
* The GUI provides a user-friendly, interactive experience for exploring flight paths efficiently.
