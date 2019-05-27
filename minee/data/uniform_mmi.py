import numpy as np
random_seed = 2
np.random.seed(seed=random_seed)
from numpy.random import uniform as unif

class UniformMMI():
    def __init__(self, sample_size, n_variables=3, low=0.0, high=1.0, varValue=0):
        self.n_variables = int(n_variables)
        self.sample_size = int(sample_size)
        self.low = low
        self.high = high

    @property
    def data(self):
        """[summary]
        
        Raises:
            ValueError -- [if number of variable is less than 3, insuffieint to test MMI]
        
        Returns:
            [np array] -- [n_sample by n_variables matrix]
        """

        if self.n_variables < 2 or self.sample_size < 1:
            raise ValueError
        else:
            x = unif(self.low, self.high, self.sample_size*(self.n_variables-1)).reshape(self.sample_size, self.n_variables-1)
            x = np.append(x, np.remainder(np.sum(x, axis=1),1)[:,None],axis=1)
            return x
            
    @property
    def ground_truth(self):
        return np.log(self.high-self.low)

