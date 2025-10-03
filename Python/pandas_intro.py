import pandas as pd

# dictionary with list object in values
details = {
    'Name' : ['Anna', 'Jan', 'Joe', 'Mark', 'Mark'],
    'Age' : [23, 21, 22, 25, 25],
    'University' : ['CVUT', 'CVUT', 'MIT', 'BHU', 'BHU'],
}
 
# creating a Data Frame 
df = pd.DataFrame(details)

# Example for reading a CSV file into a DataFrame
#df = pd.read_csv('your_file.csv')

# Display the first few rows
df.head()

# Get information about the DataFrame
df.info()

# Print descriptive statistics
print ( df.describe() )

# Count of frequencies
print ( df['University'].value_counts() )

# Count of frequencies, relative
df['University'].value_counts(normalize=True)

# to remove duplicates: 
df.drop_duplicates()

# to drop missing values you could run: 
df.dropna() 

df['Name'] # returns a Series

print ( df[['Name', 'Age']] ) # returns a DataFrame

df[df['Age'] < 25]  # to filter data...

df['Age'] < 25  # this mask is used to filter the dataframe, actually

df[(df['Age'] < 25) & (df['University'] == 'CVUT')]  # to filter data, but using more conditions together...

# to aggregate data...
df.groupby('University').agg({'Age': 'mean'})

df.pivot_table(index='University', columns='Age', aggfunc=len, values='Name').fillna(0)