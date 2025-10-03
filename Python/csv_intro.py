import csv
import io

fake_csv_file_for_illustrative_purposes = \
'''name,age,city,hobbies,is_studying
John Smith,25,London,"Tea, Hiking",Yes
Jan Novák,30,Prague,"Hiking, Reading, Music",No'''  # we need to quote the "real" comma - same as delimiter!

with io.StringIO(fake_csv_file_for_illustrative_purposes) as csv_file:
    csv_reader = csv.DictReader(csv_file)
    for row in csv_reader:
        print(row)

'''
{'name': 'John Smith', 'age': '25', 'city': 'London', 'hobbies': 'Tea, Hiking', 'is_studying': 'Yes'}
{'name': 'Jan Novák', 'age': '30', 'city': 'Prague', 'hobbies': 'Hiking, Reading, Music', 'is_studying': 'No'}
'''

with open('data.csv', 'w', newline='') as csvfile:
    fieldnames = ['name', 'age', 'city', 'hobbies' ,'is_studying']
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    writer.writeheader()
    writer.writerow({'name': 'John Smith', 'age': '25', 'city': 'London', 'hobbies': 'Tea, Hiking', 'is_studying': 'Yes'})
    writer.writerow({'name': 'Jan Novák', 'age': '30', 'city': 'Prague', 'hobbies': 'Hiking, Reading, Music', 'is_studying': 'No'})

with open("data.csv", "r") as file:
    print(file.read())

'''
name,age,city,hobbies,is_studying

John Smith,25,London,"Tea, Hiking",Yes

Jan Novák,30,Prague,"Hiking, Reading, Music",No
'''