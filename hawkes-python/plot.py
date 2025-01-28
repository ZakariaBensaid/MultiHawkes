import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

def hex_to_rgb(value):
    value = value.strip("#") # removes hash symbol if present
    lv = len(value)
    return tuple(int(value[i:i + lv // 3], 16) for i in range(0, lv, lv // 3))


def rgb_to_dec(value):
    return [v/256 for v in value]


def get_continuous_cmap(hex_list, float_list=None):
    rgb_list = [rgb_to_dec(hex_to_rgb(i)) for i in hex_list]
    if float_list:
        pass
    else:
        float_list = list(np.linspace(0, 1, len(rgb_list)))

    cdict = dict()
    for num, col in enumerate(['red', 'green', 'blue']):
        col_list = [[float_list[i], rgb_list[i][num], rgb_list[i][num]] for i in range(len(float_list))]
        cdict[col] = col_list
    cmp = mcolors.LinearSegmentedColormap('my_cmp', segmentdata=cdict, N=256)
    return cmp

# Plot excitation map
def plotHeatmap(alpha, beta, ax=None):


    if ax is None:
        fig, ax = plt.subplots()
    else:
        ax = ax
    beta_heat = np.copy(beta)
    beta_heat[beta_heat == 0] = 1
    heat_matrix = alpha/beta_heat

    hex_list = ['#FF3333', '#FFFFFF', '#33FF49']

    ax = sns.heatmap(heat_matrix, cmap=get_continuous_cmap(hex_list), center=0, ax=ax, annot=True)
    plt.show()

def plotIntensity(hawkesProcess, intensity, jumpTimes, dim, simulation, interval):
    fig, axs = plt.subplots(2, figsize=(10, 5))
    
    # Plot intensity
    axs[0].plot(interval, intensity, 'b-')
    axs[0].set_title(f'$\\lambda_{{{dim}}}(t)$')
    axs[0].set_xlabel('$t$')
    axs[0].grid(True)
    
    # Plot vertical lines for jumps
    for jump_time in jumpTimes[simulation][dim]:
        axs[0].axvline(x=jump_time, color='r', linestyle='--', alpha=0.6)
        axs[0].text(jump_time, axs[0].get_ylim()[0]  - 0.15 * (axs[0].get_ylim()[1] - axs[0].get_ylim()[0]), f'{jump_time:.2f}', ha='center', va='top', fontsize=8, color='r')
    
    
    # Plot Hawkes process as a step function
    axs[1].plot(interval, hawkesProcess, drawstyle='steps-post', color='b')
    axs[1].set_title(f'$N^{{{dim}}}_t$')
    axs[1].set_xlabel('$t$')
    axs[1].grid(True)
    
    # Plot vertical lines for jumps
    for jump_time in jumpTimes[simulation][dim]:
        axs[1].axvline(x=jump_time, color='r', linestyle='--', alpha=0.6)
        axs[1].text(jump_time, axs[1].get_ylim()[0] - 0.15 * (axs[1].get_ylim()[1] - axs[1].get_ylim()[0]), f'{jump_time:.2f}', ha='center', va='top', fontsize=8, color='r')
       
    plt.tight_layout()
    plt.show()