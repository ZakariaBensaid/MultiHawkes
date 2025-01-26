#Set the path to the hawkes library
import os 
import sys

script_dir = os.path.dirname(os.path.realpath(__file__))
module_dir = os.path.join(script_dir, 'build') # path to the hawkes library and sometimes it's 'build/Debug' or 'build/Release' for windows    
sys.path.insert(0, 'build/')

# Import the hawkes library
import hawkes
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import matplotlib.colors as mcolors
import time
from mpl_toolkits.axes_grid1.inset_locator import zoomed_inset_axes, mark_inset


# Test the simulate_hawkes function
mu = np.array([2.0, 1.5, 0.01, 0.1, 0.8, 2.0, 0.3, 0.2, 0.5, 0.01])
alpha = np.array([
    [0.5, 0.1, 3.0, 2.0, 0.4, 2.4, 0.1, 1.5, 0.1, 0.1],
    [0.2, 0.6, 3.0, 0.1, 0.2, 0.1, 0.7, 1.2, 0.1, 0.5],
    [3.5, 3.0, 4.0, 3.0, 0.1, 2.0, 0.2, 1.3, 0.1, 2.0],
    [0.1, 0.2, 0.2, 0.5, 0.1, 0.1, 0.1, 0.2, 0.1, 2.0],
    [0.3, 0.1, 1.1, 1.0, 0.6, 0.8, 0.1, 1.5, 0.1, 0.1],
    [0.1, 0.2, 0.1, 0.1, 0.1, 0.4, 0.2, 0.1, 0.1, 3.],
    [0.1, 0.2, 2.0, 3.0, 0.5, 0.1, 0.3, 0.1, 0.5, 0.1],
    [3.0, 0.1, 0.3, 0.2, 0.4, 0.1, 0.1, 0.3, 0.6, 0.1],
    [0.1, 0.1, 0.1, 2.3, 0.1, 0.1, 3.0, 0.1, 0.1, 0.1],
    [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0]
])
beta = 2*np.array([
    [5.0, 5.0, 5.0, 7.5, 4.0, 5.0, 0.5, 5.0, 5.0, 5.0],
    [4.5, 6.0, 7.5, 4.0, 5.0, 5.5, 5.0, 3.0, 5.0, 5.0],
    [5.0, 5.5, 6.0, 4.5, 6.5, 7.0, 4.0, 2.0, 5.0, 5.0],
    [1.0, 5.0, 2.5, 3.0, 4.5, 1.5, 1.0, 3.0, 5.0, 5.0],
    [0.5, 5.0, 2.0, 1.5, 5.0, 1.0, 1.5, 2.0, 5.0, 5.0],
    [4.5, 7.0, 7.5, 3.0, 6.0, 5.0, 6.5, 0.5, 5.0, 5.0],
    [4.0, 6.5, 8.0, 3.5, 5.0, 6.0, 5.5, 0.5, 5.0, 5.0],
    [4.5, 6.0, 8.5, 4.0, 5.5, 6.5, 6.0, 0.5, 5.0, 5.0],
    [5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0],
    [5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0]
])
T = 1.0
nbThreads = 10
nbSimulations = 1000

result, jump_times = hawkes.SimulateHawkes(nbSimulations, nbThreads, mu, alpha, beta, T)