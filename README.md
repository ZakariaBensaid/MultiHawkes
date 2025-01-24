# MultiHawkes

MultiHawkes is a project for simulating Hawkes processes using C++ and Python.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/MultiHawkes.git
   cd MultiHawkes

2. Build the project using CMake:
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Import the C++ class in Python:
   ```python
   import hawkes

   mu = [0.1, 0.2]
   alpha = [[0.5, 0.1], [0.1, 0.5]]
   beta = [[1.0, 1.0], [1.0, 1.0]]
   T = 10.0
   nbSimulations = 100
   nbThreads = 4

   results, jump_times = hawkes.simulate_hawkes(nbSimulations, nbThreads, mu, alpha, beta, T)
   print(results)
   print(jump_times)
   ```

   Contributing
Contributions are welcome! Please open an issue or submit a pull request.

License
This project is licensed under the MIT License.