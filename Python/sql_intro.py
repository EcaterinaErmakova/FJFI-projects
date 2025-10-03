from sqlalchemy import create_engine, Table, Column, Integer, String, MetaData, text

# Create an engine to connect to the SQLite database file
engine = create_engine('sqlite:///mydatabase.db', echo=True)  

# you will see the mydatabase.db file in 
# your directory

# Define a metadata object
metadata = MetaData()

# Define a table named 'users' with columns 'id', 'name', and 'age'
users = Table('users', metadata,
    Column('id', Integer, primary_key=True),
    Column('name', String),
    Column('age', Integer)
)

# Create the table in the database
metadata.create_all(engine)

# Insert some values
with engine.connect() as connection:
    connection.execute(text('insert into users (name, age) VALUES (:name, :age)'), {'name': 'John', 'age': 30})
    connection.commit()

from sqlalchemy import create_engine
engine = create_engine('sqlite:///mydatabase.db', echo=True)  

# how about loading the data to pandas?
import pandas as pd
df = pd.read_sql_query('select * from users', engine)

from sqlalchemy import text

# Update data in the 'users' table
with engine.connect() as connection:
    connection.execute(text('UPDATE users SET age = :age WHERE name = :name'), {'age': 35, 'name': 'John'})
    connection.commit()

df = pd.read_sql_query('select * from users', engine)
