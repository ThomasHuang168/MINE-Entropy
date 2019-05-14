import numpy as np


def getHeatMap(ax, xs, ys, z, sampleNum=0):
    """[summary]
    
    Arguments:
        ax {[type]} -- [description]
        xs {[type]} -- [description]
        ys {[type]} -- [description]
        z {function} -- [description]
    
    Keyword Arguments:
        sampleNum {int} -- [description] (default: {0})
    
    Returns:
        [type] -- [description]
    """
    # x_column_vector = xs.flatten()[:,None]
    # y_column_vector = ys.flatten()[:,None]
    # Z = z(x_column_vector, y_column_vector)
    # Z = self.mine_net(torch.FloatTensor(np.hstack((x_column_vector,y_column_vector)))).detach().numpy()
    # Z = [self.mine_net(torch.FloatTensor([[xs[i,j], ys[i,j]]])).item() for j in range(ys.shape[0]) for i in range(xs.shape[1])]
    # z = np.array(z).reshape(xs.shape[1], ys.shape[0])
    # z = z[:-1, :-1]
    z_min, z_max = -np.abs(z).max(), np.abs(z).max()
    c = ax.pcolormesh(xs, ys, z, cmap='RdBu', vmin=z_min, vmax=z_max)
    # set the limits of the plot to the limits of the data
    # ax.axis([xs.min(), xs.max(), ys.min(), ys.max()])
    return ax, c



def getResultPlot(ax, xs, z=None, sampleNum=0):
    """
    For 1-dimension MINE only
    """
    # T = [self.mine_net(torch.FloatTensor([xs[i]])).item() for i in range(xs.shape[0])]
    # z = np.array(T)
    z_min, z_max = -np.abs(z).max(), np.abs(z).max()
    ax.plot(xs, z, 'ro-')
    # set the limits of the plot to the limits of the data
    ax.axis([xs.min(), xs.max(),z_min, z_max])
    return ax


def getTrainCurve(train_loss, valid_loss, ax, show_min=True, ground_truth=[]):
    ax.plot(range(1,len(train_loss)+1),train_loss, label='Training')
    if len(valid_loss) > 0:
        ax.plot(range(1,len(valid_loss)+1),valid_loss,label='Validation')
    if type(ground_truth)==float or type(ground_truth)==np.float64:
        ax.plot(range(1,len(train_loss)+1), ground_truth*np.ones(len(train_loss)),label='ground truth')
    if show_min:
        # find position of lowest validation loss
        minposs = valid_loss.index(min(valid_loss))+1 
        ax.axvline(minposs, linestyle='--', color='r',label='Early Stopping Checkpoint')
    ax.grid(True)
    ax.legend()
    return ax