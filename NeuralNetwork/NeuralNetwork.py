
import numpy as np # linear algebra
import pandas as pd # data processing, CSV file I/O 
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler

import scipy as sp 
import sklearn
import random 
import time 
from sklearn import preprocessing, model_selection
from keras.models import Sequential 
from keras.layers import Dense 
from keras.utils import np_utils
from sklearn.preprocessing import LabelEncoder
from keras.utils.np_utils import to_categorical
from keras.utils.vis_utils import plot_model
from sklearn.utils import shuffle
from keras.layers import Dropout


#Reading dataset
data = pd.read_csv("/home/filip/anaconda3/NeuralNetwork/FeatureVectorsToTrain.csv", sep=',', header=0)
data2 = data
data = shuffle(data)


#Select 10 test featureVector from whole shuffled dataset.
i = 10
data_to_predict = data[:i].reset_index(drop = True)
predict_species = data_to_predict.Class
predict_species = np.array(predict_species)

prediction = np.array(data_to_predict.drop(['Class'],axis= 1)) # Drop first column as a target classes


data = data2[i:].reset_index(drop = True)

X = data2.drop(['Class'], axis = 1) # set X -> All columns except first Column.
X = np.array(X)
Y = data2['Class'] # set first  column "Class" as Y.


# Transform Y to Categorical values
encoder = LabelEncoder()
encoder.fit(Y)
Y = encoder.transform(Y)
Y = np_utils.to_categorical(Y)


train_x, test_x, train_y, test_y = model_selection.train_test_split(X,Y,test_size = 0.1, random_state = 0)
train_x, val_x, train_y, val_y = model_selection.train_test_split(train_x, train_y, test_size=0.2, random_state=0)


input_dim = len(data.columns) - 1

#Model
model = Sequential()
model.add(Dense(4096, input_dim = input_dim , activation = 'relu'))
#model.add(Dropout(0.2))
model.add(Dense(5000, activation = 'relu'))
#model.add(Dropout(0.2))
model.add(Dense(5000, activation = 'relu'))
#model.add(Dropout(0.2))
model.add(Dense(100, activation = 'softmax'))
print(model.summary())
plot_model(model, to_file='model_plot.png', show_shapes=True, show_layer_names=True)

model.compile(loss = 'categorical_crossentropy' , optimizer = 'adam' , metrics = ['accuracy'] )
print("Training...")
history = model.fit(train_x, train_y, epochs =50, batch_size = 32)


scores = model.evaluate(X, Y, verbose=0)
print("Accuracy on train set: %.2f%%" % (scores[1]*100))

scores = model.evaluate(test_x, test_y, verbose=0)
print("Accuracy on test set: %.2f%%" % (scores[1]*100))

scores = model.evaluate(val_x, val_y, verbose=0)
print("Accuracy on validation set: %.2f%%" % (scores[1]*100))

print("Predicting...")
predictions = model.predict_classes(prediction)

prediction_ = np.argmax(to_categorical(predictions), axis = 1)

prediction_ = encoder.inverse_transform(prediction_)

for i, j in zip(prediction_ , predict_species):
    print( "The NeuralNetwork predict class {}, expected class is {}".format(i,j))

model.save('/home/TrainedModel.h5')

print(history.history.keys())

train_loss = history.history['loss']
val_loss   = history.history['val_loss']
train_acc  = history.history['accuracy']
val_acc    = history.history['val_accuracy']
xc         = range(1)

plt.plot(train_acc)
plt.plot(val_acc)
plt.title('Model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'val'], loc='upper left')
plt.show()

plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train', 'val'], loc='upper left')
plt.show()
