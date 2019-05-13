from .model.linear_regression import LinearReg
from .model.mine import Mine
from .model.mine_entropy import Mine_ent
from .model.mine_multitask import MineMultiTask
from .model.kraskov import Kraskov
from .model.cart_regression import cartReg
# from .model.jackknife import Jackknife

# from .model.ShannonKDE import ShanKDE
# from .model.hellingerDiv import hellingerDiv
# from .model.tsallisDiv import tsallisDiv
# from .model.chiSqDiv import chiSqDiv
# from .model.renyiDiv import renyiDiv
# from .model.klDiv import klDiv
# from .model.condShannonEntropy import condShanEnt


from .data.mix_gaussian import MixedGaussian
from .data.mix_uniform import MixedUniform
from .data.gaussian import Gaussian
from .data.uniform_mmi import UniformMMI
import math
import os
from datetime import datetime

cpu = 1
batch_size=64
patience=int(250)
iter_num=int(1e+4)
lr = 2e-3
moving_average_rate = 0.01
hidden_size = 100


time_now = datetime.now()
output_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "experiments")

# ground truth is plotted in red
model = {
    #  'Linear Regression': {  # model name, for plotting the legend
    #      'model': LinearReg(  # initialize the object
    #          cvFold=3
    #      ), 
    #      'color': 'blue'  # for plotting
    #  }, 
    #  'Kraskov': {
    #      'model': Kraskov(
    #          discrete_features='auto', 
    #          n_neighbors=3, 
    #          random_state=None
    #      ), 
    #      'color': 'green'
    #  }, 
    # 'LOO Shannon KDE': {
    #     'model': ShanKDE(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'magenta'
    # },
    # 'LOO hellingerDiv': {
    #     'model': hellingerDiv(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'cyan'
    # }, 
    # 'LOO tsallisDiv': {
    #     'model': tsallisDiv(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'yellow'
    # }, 
    # 'LOO chiSqDiv': {
    #     'model': chiSqDiv(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'black'
    # }, 
    # 'LOO renyiDiv': {
    #     'model': renyiDiv(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'green'
    # }, 
    # 'LOO klDiv': {
    #     'model': klDiv(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'orange'
    # }, 
    # 'LOO condShanEnt': {
    #     'model': condShanEnt(
    #         numPart='loo', 
    #         numAvgPart=1, 
    #         correctBound=False, 
    #         Low=1e-5, 
    #         Upp=math.inf, 
    #         doAsympAnalysis=False,
    #         alpha=0.5
    #     ), 
    #     'color': 'pink'
    # }, 
    # 'Cart Reg': {
    #     'model': cartReg(
    #         cvFold=3
    #     ), 
    #     'color': 'pink'
    # },
    'MINE_direct_hidden_X_2': {
        'model': Mine(
            lr=lr, 
            batch_size=batch_size, 
            patience=patience, 
            iter_num=iter_num, 
            log_freq=int(100), 
            avg_freq=int(10), 
            ma_rate=moving_average_rate, 
            verbose=False,
            log=True,
            sample_mode='marginal',
            earlyStop=False,
            hidden_size=hidden_size*2
        ), 
        'color': 'magenta'
    },
    'MINE_multi_task': {
        'model': MineMultiTask(
            lr=lr, 
            batch_size=batch_size, 
            patience=patience, 
            iter_num=iter_num, 
            log_freq=int(100), 
            avg_freq=int(10), 
            ma_rate=moving_average_rate, 
            verbose=False,
            log=True,
            sample_mode='unif',
            earlyStop=False,
            add_mar=True,
            hidden_size=hidden_size
        ), 
        'color': 'grey'
    },
    'MINE_entropy': {
        'model': MineMultiTask(
            lr=lr, 
            batch_size=batch_size, 
            patience=patience, 
            iter_num=iter_num, 
            log_freq=int(100), 
            avg_freq=int(10), 
            ma_rate=moving_average_rate, 
            verbose=False,
            log=True,
            sample_mode='unif',
            earlyStop=False,
            add_mar=False,
            hidden_size=hidden_size
        ), 
        'color': 'purple'
    },
    'MINE_direct': {
        'model': Mine(
            lr=lr, 
            batch_size=batch_size, 
            patience=patience, 
            iter_num=iter_num, 
            log_freq=int(100), 
            avg_freq=int(10), 
            ma_rate=moving_average_rate, 
            verbose=False,
            log=True,
            sample_mode='marginal',
            earlyStop=False,
            hidden_size=hidden_size
        ), 
        'color': 'orange'
    },
    # 'MINE_entropy': {
    #     'model': Mine_ent(
    #         lr=lr,  
    #         batch_size=batch_size, 
    #         patience=patience,
    #         iter_num=iter_num, 
    #         log_freq=int(100), 
    #         avg_freq=int(10), 
    #         ma_rate=moving_average_rate, 
    #         verbose=False,
    #         earlyStop=False
    #     ), 
    #     'color': 'purple'
    # },
    # 'Jackknife': {
    #     'model': Jackknife(
    #         n_sim=5
    #     ),
    #     'color': 'brown'
    # }
}

# sample_size = 6400
sample_size = batch_size * 20
rhos = [ 0.9, 0.9999, 1-1e-8, 1-1e-12 ]
# rhos = [0.999]
widths = list(range(2, 12, 4))


data = {
    # 'Mixed Gaussian': {
    #     'model': MixedGaussian,
    #     'kwargs': [  # list of params
    #         {
    #             'sample_size':sample_size, 
    #             'mean1':0, 
    #             'mean2':0, 
    #             'rho1': rho, 
    #             'rho2': -rho,
    #         } for rho in rhos
    #     ], 
    #     'varying_param_name': 'rho1', # the parameter name which denotes the x-axis of the plot
    #     'x_axis_name': 'correlation', 
    # }, 
    'Gaussian': {
        'model': Gaussian, 
        'kwargs': [
            {
                'sample_size':sample_size, 
                'mean1':0, 
                'mean2':0, 
                'rho': rho,
            } for rho in rhos
        ], 
        'varying_param_name': 'rho', 
        'x_axis_name': 'correlation', 
    },
    # 'Mixed Uniform': {
    #     'model': MixedUniform, 
    #     'kwargs': [
    #         {
    #             'sample_size':sample_size, 
    #             'width_a': width, 
    #             'width_b': width, 
    #             'mix': 0.5
    #         } for width in widths
    #     ], 
    #     'varying_param_name': 'width_a', 
    #     'x_axis_name': 'width'
    # }, 
    # {
    #     'name': 'Examples', 
    #     'model': XX(
    #         sample_size=XX
    #         rho=XX
    #     )
    # }, 
}


n_datasets = len(data)
# n_columns = max([len(rhos), len(widths)])
