import pandas as pd # data processing, CSV file I/O 
import numpy as np # linear algebra
from sklearn.preprocessing import StandardScaler
import sklearn as sk
import random 
import time 
from sklearn import preprocessing, model_selection
from keras.models import Sequential 
from keras.layers import Dense 
from keras.utils import np_utils
from sklearn.preprocessing import LabelEncoder
from keras.utils.np_utils import to_categorical
from sklearn.utils import shuffle
from keras.models import load_model



model = load_model('/home/TrainedModelH1.h5') # load trained model

data = pd.read_csv('/home/FeatureVectorsToCompare.csv', sep=',') # load feature vectors of two fingerprints

resultFileTxt = open("/home/results.txt","w") 

prediction = np.array(data)

predictions = model.predict_classes(prediction)

for i in predictions:
	file1.write('%d\n' % i)
	print("The Classifier classified fingerprint to class:", i)
	
resultFileTxt.close()
	
	
	
	
	
	
	
