import numpy as np
from .model import mine
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import math
from scipy.stats import randint
import os
from .utils import save_train_curve
# from model import Mine, LinearReg, Kraskov
from joblib import Parallel, delayed
from . import settings
from tqdm import tqdm

def saveResultsFig(results_dict, experiment_path=""):
    """
    
    Arguments:
    # results_dict example: 
    # {
    #     'Ground Truth': {
    #         'Gaussian': [(0, 0), (0.2, 0.5), ..., (1,1)],  # [(rho, MI), (rho2, MI_2), ...]
    #         'Bimodal': [(0, 0), (0.2, 0.5), ..., (1,1)]
    #     }, 
    #     'Linear Regression': {
    #         'Gaussian': [(0, 0), (0.2, 0.5), ..., (1,1)],
    #         'Bimodal': [(0, 0), (0.2, 0.5), ..., (1,1)]
    #     }, 
    #     ...
    # }
    """
    # initialize ground truth color
    settings.model['Ground Truth'] = {'color': 'red'}
    
    n_datasets = settings.n_datasets
    # n_columns = settings.n_columns + 1  # 0 to N_Column for visualizing the data, last column for the MI estimate plot

    fig, axes = plt.subplots(nrows=n_datasets, ncols=1, figsize=(12,8))

    for _, (model_name, dataset_results) in enumerate(results_dict.items()):
        for row_id, (dataset_name, results) in enumerate(dataset_results.items()):
            color = settings.model[model_name]['color']
            xs = [x for x, y in results]
            ys = [y for x, y in results]
            if n_datasets > 1:
                axe = axes[row_id]
            else:
                axe = axes
            axe.scatter(xs, ys, edgecolors=color, facecolors='none', label=model_name)
            axe.set_xlabel(settings.data[dataset_name]['varying_param_name'])
            axe.set_ylabel('MI')
            axe.set_title(dataset_name)
            axe.legend()
    figName = os.path.join(experiment_path, "MI")
    fig.savefig(figName, bbox_inches='tight')
    plt.close()

def get_estimation(model_name, model, data_model, data_name, varying_param_name, varying_param_value, prefix_name_loop):
    """
    Returns: mi estimate (float)
    """

    # results = dict()
    data = data_model.data
    ground_truth = data_model.ground_truth

    # prefix_name_loop = .path.join(experiment_path, "{}_{}={}/".format(data_name, varying_param_name, osvarying_param_value))
    # if not os.path.exists(prefix_name_loop):
    #     os.makedirs(prefix_name_loop)
        
    # #Plot Ground Truth MI
    # fig, ax = plt.subplots(figsize=(15, 15))
    # Xmax = max(data[:,0])
    # Xmin = min(data[:,0])
    # Ymax = max(data[:,1])
    # Ymin = min(data[:,1])
    # x = np.linspace(Xmin, Xmax, 300)
    # y = np.linspace(Ymin, Ymax, 300)
    # xs, ys = np.meshgrid(x,y)
    # ax, c = data_model.plot_i(ax, xs, ys)
    # fig.colorbar(c, ax=ax)
    # ax.set_title("i(X;Y)")
    # figName = os.path.join(prefix_name_loop, "i_XY")
    # fig.savefig(figName, bbox_inches='tight')
    # plt.close()


    # Fit Algorithm
    # For plotting extra figure inside the training
    model['model'].model_name = model_name
    model['model'].prefix = os.path.join(prefix_name_loop, model_name)
    os.makedirs(model['model'].prefix)
    model['model'].paramName = varying_param_name
    model['model'].paramValue = varying_param_value
    model['model'].ground_truth = ground_truth
    mi_estimation = model['model'].predict(data)

    # Save Results
    # results[model_name] = mi_estimation

    # Ground Truth
    # results['Ground Truth'] = ground_truth

    return mi_estimation, ground_truth, model_name, data_name, varying_param_value

def plot(experiment_path, rootID, googleDrive):
    # Initialize the results dictionary

    # results example: 
    # {
    #     'Ground Truth': {
    #         'Gaussian': [(0, 0), (0.2, 0.5), ..., (1,1)],  # [(rho, MI), (rho2, MI_2), ...]
    #         'Bimodal': [(0, 0), (0.2, 0.5), ..., (1,1)]
    #     }, 
    #     'Linear Regression': {
    #         'Gaussian': [(0, 0), (0.2, 0.5), ..., (1,1)],
    #         'Bimodal': [(0, 0), (0.2, 0.5), ..., (1,1)]
    #     }, 
    #     ...
    # }


    results = dict()
    results['Ground Truth'] = dict()
    for model_name in settings.model.keys():
        results[model_name] = dict()
        for data_name in settings.data.keys():
            results[model_name][data_name] = []
            results['Ground Truth'][data_name] = []

    for data_name, data in settings.data.items():
        for kwargs in data['kwargs']:
            varying_param_name = data['varying_param_name']
            varying_param_value = kwargs[varying_param_name]
            prefix_name_loop = os.path.join(experiment_path, "{}_{}={}/".format(data_name, varying_param_name, varying_param_value))
            if not os.path.exists(prefix_name_loop):
                os.makedirs(prefix_name_loop)
    
    # # Main Loop
    r = Parallel(n_jobs=settings.cpu)(delayed(get_estimation)(model_name, 
                                                              model, 
                                                              data['model'](**kwargs), 
                                                              data_name, 
                                                              data['varying_param_name'], 
                                                              kwargs[data['varying_param_name']], 
                                                              experiment_path) 
                                                                    for model_name, model in tqdm(settings.model.items())
                                                                    for data_name, data in tqdm(settings.data.items())
                                                                    for kwargs in tqdm(data['kwargs']))
    for (mi_estimate, ground_truth, model_name, data_name, varying_param_value) in r:
        results[model_name][data_name].append((varying_param_value, mi_estimate))
        results['Ground Truth'][data_name].append((varying_param_value, ground_truth))
    # Plot and save
    saveResultsFig(results, experiment_path=experiment_path)

    return 0

def run_experiment():
    # prompt
    experiment_name = input('Please enter the experiment name: ')
    experiment_path = os.path.join(settings.output_path, experiment_name)
    if not os.path.exists(experiment_path):
        os.makedirs(experiment_path)
        print('Output will be saved into {}'.format(experiment_path))
    # save the settings
    settings_dest_path = os.path.join(experiment_path, 'settings.py')
    if not os.path.isfile(settings_dest_path):
        from shutil import copyfile
        mmi_dir_path = os.path.dirname(os.path.abspath(__file__))
        settings_path = os.path.join(mmi_dir_path, 'settings.py')
        copyfile(settings_path, settings_dest_path)
    plot(experiment_path)

def run_experiment_batch_pop_ir(pop_, bat_):
    # batch = [int(8), int(32), int(128), int(2)]
    # # batch = [int(2), int(8), int(256), int(512)]
    # pop = [int(2048), int(512), int(8192)]
    iterNum_ = int(1e6)
    # iterNum_ = int(312500)
    # snapshot = [int(iterNum_/1028), int(iterNum_/512), int(iterNum_/256), int(iterNum_/128), int(iterNum_/64), int(iterNum_/32), int(iterNum_/16), int(iterNum_/8), int(iterNum_/4), int(iterNum_/2)]
    snapshot = [int(math.exp(i)) for i in range(math.floor(math.log(iterNum_)))]
    experiment_name = "gaus_pop={}_batch={}".format(pop_, bat_)
    experiment_path = os.path.join(settings.output_path, experiment_name)

    settings.model['MINE_direct']['model'].batch_size = bat_
    settings.model['MINE_entropy']['model'].batch_size = bat_
    settings.model['MINE_multi_task']['model'].batch_size = bat_
    settings.model['MINE_direct_hidden_X_2']['model'].batch_size = bat_

    settings.model['MINE_direct']['model'].iter_num = iterNum_
    settings.model['MINE_entropy']['model'].iter_num = iterNum_
    settings.model['MINE_multi_task']['model'].iter_num = iterNum_
    settings.model['MINE_direct_hidden_X_2']['model'].iter_num = iterNum_

    settings.model['MINE_direct']['model'].iter_snapshot = snapshot
    settings.model['MINE_entropy']['model'].iter_snapshot = snapshot
    settings.model['MINE_multi_task']['model'].iter_snapshot = snapshot
    settings.model['MINE_direct_hidden_X_2']['model'].iter_snapshot = snapshot
    # settings.data['Mixed Gaussian']['kwargs'] =  [  # list of params
    #                                                 {
    #                                                     'sample_size': pop_, 
    #                                                     'mean1':[0.5, 0.5], 
    #                                                     'mean2':[-0.5, -0.5], 
    #                                                     'rho1': rho, 
    #                                                     'rho2': -rho,
    #                                                 } for rho in settings.rhos
    #                                             ]
    settings.data['Gaussian']['kwargs'] = [
                                            {
                                                'sample_size':pop_, 
                                                'mean1':[0.5, 0.5], 
                                                'mean2':[-0.5, -0.5], 
                                                'rho': rho,
                                            } for rho in settings.rhos
                                        ]
    # settings.data['Mixed Uniform']['kwargs'] = [
    #                                             {
    #                                                 'sample_size':pop_, 
    #                                                 'width_a': width, 
    #                                                 'width_b': width, 
    #                                                 'mix': 0.5
    #                                             } for width in settings.widths
    #                                         ]
    if not os.path.exists(experiment_path):
        os.makedirs(experiment_path)
        print('Output will be saved into {}'.format(experiment_path))
    # save the settings
    settings_dest_path = os.path.join(experiment_path, 'settings.py')
    if not os.path.isfile(settings_dest_path):
        from shutil import copyfile
        mmi_dir_path = os.path.dirname(os.path.abspath(__file__))
        settings_path = os.path.join(mmi_dir_path, 'settings.py')
        copyfile(settings_path, settings_dest_path)
    plot(experiment_path)

if __name__ == "__main__":
    # run_experiment()
    import sys
    # run_experiment_batch_pop_ir(int(sys.argv[1]), int(sys.argv[2]))
    index = int(sys.argv[1])
    print("index={}".format(index))

    batch = [int(8), int(32), int(128), int(2)]
    bat_i = index % len(batch)
    batch_ = batch[bat_i]
    index = index // len(batch)
    print("batch={}".format(batch_))

    pop = [int(2048), int(512), int(8192)]
    pop_i = index % len(pop)
    pop_ = pop[pop_i]
    index = index // len(pop)
    print("pop={}".format(pop_))
    
    model_names = []
    for model_name in settings.model.keys():
        model_names.append(model_name)
    model_names_i = index % len(model_names)
    model_names_ = model_names[model_names_i]
    index = index // len(model_names)
    print("model_name={}".format(model_names_))

    # settings.data['Mixed Gaussian']['kwargs'] =  [  # list of params
    #                                                 {
    #                                                     'sample_size': pop_, 
    #                                                     'mean1':[0.5, 0.5], 
    #                                                     'mean2':[-0.5, -0.5], 
    #                                                     'rho1': rho, 
    #                                                     'rho2': -rho,
    #                                                 } for rho in settings.rhos
    #                                             ]
    settings.data['Gaussian']['kwargs'] = [
                                            {
                                                'sample_size':pop_, 
                                                'mean1':[0.5, 0.5], 
                                                'mean2':[-0.5, -0.5], 
                                                'rho': rho,
                                            } for rho in settings.rhos
                                        ]
    # settings.data['Mixed Uniform']['kwargs'] = [
    #                                             {
    #                                                 'sample_size':pop_, 
    #                                                 'width_a': width, 
    #                                                 'width_b': width, 
    #                                                 'mix': 0.5
    #                                             } for width in settings.widths
    #                                         ]

    numData = 0
    for data_name, data in settings.data.items():
        numData += len(data['kwargs'])
        if index < numData:
            arg_i = index + len(data['kwargs']) - numData
            data_name_ = data_name
            data_model = data['model'](**data['kwargs'][arg_i])
            print("data_name={}".format(data_name_))
            print("data({})".format(data['kwargs'][arg_i]))
            break

    
    iterNum_ = int(1e8)
    snapshot = [int(math.exp(i)) for i in range(math.floor(math.log(iterNum_)))]
    experiment_name = "gaus_pop={}_batch={}".format(pop_, batch_)
    experiment_path = os.path.join(settings.output_path, experiment_name)

    model_ = settings.model[model_names_]['model']
    model_.batch_size = batch_
    model_.iter_num = iterNum_
    model_.iter_snapshot = snapshot
    
    if not os.path.exists(experiment_path):
        os.makedirs(experiment_path)
        print('Output will be saved into {}'.format(experiment_path))
    # save the settings
    settings_dest_path = os.path.join(experiment_path, 'settings.py')
    if not os.path.isfile(settings_dest_path):
        from shutil import copyfile
        mmi_dir_path = os.path.dirname(os.path.abspath(__file__))
        settings_path = os.path.join(mmi_dir_path, 'settings.py')
        copyfile(settings_path, settings_dest_path)

    varying_param_name = data['varying_param_name']
    varying_param_value = data['kwargs'][arg_i][varying_param_name]
    prefix_name_loop = os.path.join(experiment_path, "{}_{}={}/".format(data_name_, varying_param_name, varying_param_value))
    if not os.path.exists(prefix_name_loop):
        os.makedirs(prefix_name_loop)

    get_estimation(model_names_, settings.model[model_names_], data_model, data_name_, varying_param_name, varying_param_value, prefix_name_loop)
        
