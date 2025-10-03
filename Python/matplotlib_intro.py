''' 
Matplotlib is designed to be as usable as MATLAB, 
with the ability to use Python, 
and the advantage of being free and open-source. 
'''


import matplotlib.pyplot as plt
import numpy as np
'''
# Generate random data
x = np.random.rand(100)
y = np.random.rand(100)
sizes = np.random.randint(10, 100, 100)  # Random sizes for each point

# Create scatter plot
plt.figure(figsize=(8, 6))
plt.scatter(x, y, s=sizes, alpha=0.5, c='blue', label='Random Data')

# Add labels and title
plt.title('Scatter Plot with Matplotlib')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.legend()

# Show plot
plt.show() 
'''


import pandas as pd
# creating dataframe 
df = pd.DataFrame({ 
    'X': [1, 2, 3, 4, 5], 
    'Y': [2, 4, 6, 10, 15] 
}) 
# plotting a scatter plot
df.plot(kind='scatter', x='X', y='Y', title='Scatter plot');  # notice the semicolon


# creating another dataframe 
df = pd.DataFrame({ 
    'X': [1, 2, 3, 4, 5], 
    'Y1': [2, 4, 6, 10, 15],
    'Y2': [4, 3, 8, 12, 6] 
}) 
# plotting a line plot
df.set_index('X').plot(style='.-', title='Sample line plot');  # notice the set_index()


# if you would like to save the figure in this case, you can use the get_figure() method: 
fig = df.set_index('X').plot(style='.-', title='Sample line plot').get_figure()
fig.savefig('line_plot.png')


#Firstly, even just by using it, the matplotlib plots have improved ergonomics: 
import seaborn as sns
sns.set()
df.set_index('X').plot(style='.-', title='Sample line plot');  # notice the set_index()