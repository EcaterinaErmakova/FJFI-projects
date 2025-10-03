import pyarrow.parquet as pq
from pyarrow import Table


import json

json_data = json.loads('''[
    {
        "name": "John Smith",
        "age": 25,
        "city": "London",
        "hobbies": [
            "Tea",
            "Hiking"
        ],
        "is_studying": true
    },
    {
        "name": "Jan Novák",
        "age": 30,
        "city": "Prague",
        "hobbies": [
            "Hiking",
            "Reading",
            "Music"
        ],
        "is_studying": false
    }
]''')

json_data

table = Table.from_pylist(json_data)
table

pq.write_table(table, 'data.parquet')

import pandas as pd
pd.read_parquet('data.parquet')