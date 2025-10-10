import xml.etree.ElementTree as ET

# Tutorial : https://docs.python.org/3/library/xml.etree.elementtree.html

xml_data = '''
<data>
   <person>
      <name>John Smith</name>
      <age>25</age>
      <city>London</city>
      <hobbies>
         <element>Tea</element>
         <element>Hiking</element>
      </hobbies>
      <is_studying>true</is_studying>
   </person>
   <person>
      <name>Jan Novák</name>
      <age>30</age>
      <city>Prague</city>
      <hobbies>
         <element>Hiking</element>
         <element>Reading</element>
         <element>Music</element>
      </hobbies>
      <is_studying>false</is_studying>
   </person>
</data>
'''
root = ET.fromstring(xml_data)
print(root.tag) 
# data

print(root[0][0].tag, root[0][0].text) 
# name John Smith

# to export the entire tree:
with open('data.xml', 'w') as f:
    ET.ElementTree(root).write(f, encoding='unicode')

# !cat data.xml
with open("data.xml", "r") as file:
    print(file.read())

