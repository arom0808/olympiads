import numpy as np
import random
from IPython.display import clear_output
from collections import deque
import progressbar

import gymnasium as gym

from keras import Model, Sequential
from keras.layers import Dense, Embedding, Reshape
from keras.optimizers import Adam

environment = gym.make("Taxi-v3")
environment.render()

print('Number of states: {}'.format(environment.observation_space.))
print('Number of actions: {}'.format(environment.action_space.n))
