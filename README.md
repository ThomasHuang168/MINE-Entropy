[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/ccha23/MINE-Entropy/master?urlpath=lab/tree/load%20MINE_net-cchan.ipynb)

# MMI estimation


![MI](./img/MI.png)


## Dependencies
- pytorch
- joblib
- sklearn
- numpy
- scipy
- matplotlib
- tqdm

## Dependencies for if-estimators
- matlab (tested with 2018b)
```bash
#find 
cd <matlabroot>/extern/engines/python
python setup.py install
```

## How to run
```bash
cd ..
# check the configuration in settings.py
python -m MMI.main
```

## How to add new mi estimators
- go to ```model/``` 
- create a new class (see mine.py/linear_regression.py for example)
- must contain the predict function (given a N by 2 matrix, return the MI estimator (float))
- go to settings.py, add the corresponding configuration in the variable *model*

## How to add new synthetic data
- go to ```data/``` 
- create a new class (see bimodal.py for example)
- must contain the two property: *data* and *ground_truth* (see bimodal.py for example)
- go to settings.py, add the corresponding configuration in the variable *data*
