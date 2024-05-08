"""
To create ADT that implement the "set" concept. a. Add (new Element) -Place a value
into the set , b. Remove (element) Remove the value c. Contains (element) Return true
if element is in collection, d. Size () Return number of values in collection Iterator ()
Return an iterator used to loop over collection, e. Intersection of two sets , f. Union of
two sets, g. Difference between two sets, h. Subset
"""
from ctypes import sizeof

print ("Program of Sets ") 

a = set([])
num = int(input("Enter The Total Number of Elements In Set A: "))
for i in range(num):
    m = int(input("Enter Elements: "))
    a.add(m);
    
b = set([])
no = int(input("Enter The Total Number of Elements In Set B: "))
for i in range(no):
    m = int(input("Enter Elements: "))
    b.add(m);
print("Set A : ",a)
print("Set B : ",b)

while True:
    print("\n\n\n *****  MENU ****** \n")
    print("1 : Union")
    print("2 : Intersection")
    print("3 : Set Difference")
    print("4 : Subset")
    print("5 : Is Empty")
    print("6 : Len of A")
    print("7 : Len of B")
    print("8 : size of A and B ")
    print("9 : searching ")
    print("10: add Element ")
    print("11: Remove Element")

    ch=int(input("\n***** Enter your Choice ****** \n"))
    if ch==1:
        print("\n Union of A and B as",a.union(b))
    if ch==2:
        print("\n Intersection of A and B",a.intersection(b))
    if ch==3:
        print("\n Set difference A-B as",a-b)
    if ch==4:
        if a.issubset(b):
            print("\nIs subset")
        else:
            print("\n Not a subset")
    if ch==5:
        if len(a)==0:
            print("\n Set A is Empty")
        else:
            print("\n Set A is not empty")
    if ch==6:
        print("Len A=",len(a))
    if ch==7:
        print("Len B=",len(b))
    if ch== 8 :
        print("\n size of a is :",sizeof(a)) 
        print("\n size of a is :",sizeof(b)) 
    if ch== 9 :
        num = int(input(" \n Enter Element to Be Searched "))
        if num in a :
            print(" \n Number is Found In Set A  ")
        elif num in b:
            print(" \n Number Is Found In Set B  ")
        else :
            print("\n\n Sorry ! Number Not Found ")
    if ch==10 :
        ad = int(input(" Enter Number To be Added In Set  A "))
        a.add(ad)
        print(" \n number Added In Set A ")
        print("\n  Updated Set :  ",a)
    if ch==11 :
        rm = int(input(" Enter Numbber To Delete "))
        a.remove(rm)
        print("\n  Number Removed ")
        print(" \n  Updated Set Set ", a)
