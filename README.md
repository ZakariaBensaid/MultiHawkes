# MultiHawkes

MultiHawkes is a project for simulating Hawkes processes using C++ and Python 3.10.14.

## Installation in Windows

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/MultiHawkes.git
    cd MultiHawkes
    ```
2. Download and install Visual Studio for C++ and CMake:
    - Download and install [Visual Studio](https://visualstudio.microsoft.com/) with the "Desktop development with C++" workload.
    - Download and install [CMake](https://cmake.org/download/).


3. Install requirements: (numpy, matplotlib, pandas, tensorflow==2.10.0, cudatoolkit==11.2.2, cudnn==8.1.0.77)
    ```sh
    pip install -r requirements.txt
    ```

4. Build the project using CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
   ```

5. Import the C++ class in Python:
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

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

## License

This project is licensed under the MIT License.
