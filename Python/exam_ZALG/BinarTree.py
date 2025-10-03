# Python program to insert element in binary tree 
class newNode(): 
    def __init__(self, data): 
        self.key = data
        self.left = None
        self.right = None
 
 
"""function to insert element in binary tree """
def insert(temp,key):
    if not temp:
        root = newNode(key)
        return
    q = [] 
    q.append(temp) 
    # Do level order traversal until we find 
    # an empty place. 
    while (len(q)): 
        temp = q[0] 
        q.pop(0) 
        if (not temp.left):
            temp.left = newNode(key) 
            break
        else:
            q.append(temp.left) 
        if (not temp.right):
            temp.right = newNode(key) 
            break
        else:
            q.append(temp.right)



# implement Tree Sort 
# Class containing left and 
# right child of current  
# node and key value 
class Node: 
  def __init__(self,item = 0): 
    self.key = item 
    self.left, self.right = None,None
  
# Root of BST 
root = Node() 
root = None
  
# A recursive function to  
# insert a new key in BST 
def insertRec(root, key):  
  # If the tree is empty, 
  # return a new node 
  if (root == None): 
    root = Node(key) 
    return root 
  # Otherwise, recur 
  # down the tree  
  if (key < root.key): 
    root.left = insertRec(root.left, key) 
  elif (key > root.key): 
    root.right = insertRec(root.right, key) 
  # return the root 
  return root 

def inorderRec(root): 
  if (root != None): 
    inorderRec(root.left) 
    print(root.key ,end = " ") 
    inorderRec(root.right) 
