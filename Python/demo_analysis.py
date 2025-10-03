'''
import pandas as pd
import ssl
import certifi
ssl._create_default_https_context = ssl._create_unverified_context

# Live data analysis demo

url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/autos/imports-85.data'
column_names = [
    "symboling", "normalized-losses", "make", "fuel-type", "aspiration",
    "num-of-doors", "body-style", "drive-wheels", "engine-location",
    "wheel-base", "length", "width", "height", "curb-weight",
    "engine-type", "num-of-cylinders", "engine-size", "fuel-system",
    "bore", "stroke", "compression-ratio", "horsepower", "peak-rpm",
    "city-mpg", "highway-mpg", "price"
]
df = pd.read_csv(url, names=column_names, na_values='?')
df.head()  
df.info()  

from ydata_profiling import ProfileReport

from ydata_profiling.config import Settings  
config = Settings()
config.vars.num.chi_squared_threshold = 0.0  # Disable chi-squared test (generates a bug)

profile = ProfileReport(df, title="YData Cars Profiling Report", config=config, explorative=True)
profile.to_file("lecture_06b_report.html")
'''

# Custom visualizations
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
sns.set()  
df = pd.read_csv("your_dataset.csv")

# %matplotlib inline  

sns.histplot(data=df, x="price", bins=30, kde=True)
plt.title("Distribution of Car Prices")
plt.xlabel("Price")
plt.ylabel("Frequency")
plt.show()  

sns.boxplot(data=df, x="body-style", y="price")
plt.title("Car Price by Body Style")
plt.xticks(rotation=45)
plt.show()  

sns.violinplot(data=df, x="fuel-type", y="price")
plt.title("Price Distribution by Fuel Type")
plt.show()

sns.scatterplot(data=df, x="engine-size", y="price", hue="fuel-type")
plt.title("Engine Size vs Price")
plt.show()  

sns.pairplot(df[["price", "engine-size", "horsepower", "curb-weight"]])
plt.suptitle("Pairwise Relationships", y=1.02)
plt.show()  

corr = df.select_dtypes(include=[np.number]).corr()

plt.figure(figsize=(12, 8))
sns.heatmap(corr, annot=True, cmap="coolwarm")
plt.title("Correlation Heatmap")
plt.show()  
sns.countplot(data=df, x="make", order=df["make"].value_counts().index)
plt.xticks(rotation=90)
plt.title("Car Count by Make")
plt.show()  
g = sns.FacetGrid(df, col="fuel-type", row="aspiration", margin_titles=True)
g.map(sns.histplot, "price", bins=20)
plt.show()