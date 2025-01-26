# MultiHawkes

MultiHawkes is a project for simulating multivariate Hawkes processes using C++ and Python 3.10.14.

## Installation in Windows

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/MultiHawkes.git
    cd MultiHawkes
    ```
2. Download and install Visual Studio for C++ :
    - Download and install [Visual Studio](https://visualstudio.microsoft.com/) with the "Desktop development with C++" workload.

3. Install requirements: (cmake, pybind11, numpy, matplotlib, pandas, tensorflow==2.10.0, cudatoolkit==11.2.2, cudnn==8.1.0.77..)
    ```sh
    pip install -r requirements.txt
    ```

4. Build the project using CMake :
    ```sh
    mkdir build
    cd build
    cmake ..
    cmake --build .
   ```

## Installation in Linux/MacosX

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/MultiHawkes.git
    cd MultiHawkes
    ```

2. Install requirements: (cmake, pybind11, numpy, matplotlib, pandas, tensorflow==2.10.0, cudatoolkit==11.2.2, cudnn==8.1.0.77)
    ```sh
    pip install -r requirements.txt
    ```

4.  Build the project using Cmake :
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

## Test

1.  Run the following code : (Notice: if you don't have the build folder it won't run)

    ```python
    #Set the path to the hawkes library
    import os 
    import sys

    script_dir = os.path.dirname(os.path.realpath(__file__))
    module_dir = os.path.join(script_dir, 'build') # path to the hawkes library and sometimes it's 'build/Debug' or 'build/Release' for windows   (look for .pyd file) 
    sys.path.insert(0, 'build/')

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
