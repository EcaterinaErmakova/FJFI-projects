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

''' 
print(json.dumps(json_data, indent=2, ensure_ascii=False)) 
# very similar to a dictionary
'''

# to export into file:
with open('data.json', 'w', encoding='utf-8') as f:
    json.dump(json_data, f, ensure_ascii=False, indent=2)

#!cat data.json
with open("data.json", "r") as file:
    print(file.read())