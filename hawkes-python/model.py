import numpy as np

class hawkesModel:
    def __init__(self, mu, alpha, beta, jump_times):
        """
        Initialize the Hawkes process model for plotting.. not optimized.. we can send all of this from C++
        """
        self.mu = np.array(mu)
        self.alpha = np.array(alpha)
        self.beta = np.array(beta)
        self.jump_times = jump_times
        self.num_simulations = len(jump_times)
        self.M = self.mu.shape[0]

    def get_intensity(self, interval, dim, simulation):
        event_times = np.asarray(self.jump_times[simulation][dim])
        mu_dim = self.mu[dim]
        alpha_dim = self.alpha[dim]
        beta_dim = self.beta[dim]
        
        intensity = []
        for t in interval:
            past_events = event_times[event_times < t]
            if past_events.size == 0:
                intensity.append(mu_dim)
                continue
                
            # Handle array dimensions correctly
            time_diff = t - past_events[:, np.newaxis]  # Create 2D array for broadcasting
            decay = alpha_dim * np.exp(-beta_dim * time_diff)
            intensity.append(mu_dim + decay.sum())
            
        return np.array(intensity)

    def get_hawkesProcess(self, interval, dim, simulation):
        event_times = np.sort(self.jump_times[simulation][dim])
        return np.searchsorted(event_times, interval, side='right')