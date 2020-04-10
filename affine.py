from random import randrange
lettres = "abcdefghijklmnopqrstuvwxyz"

def pgcd(a,b):
  while b != 0:
    r = a%b
    a,b = b,r
  return a

def genKey(alphabet):
  a,b=0,0
  while (a == 0 and b == 0) or pgcd(a,len(alphabet)) != 1:
    a = randrange(1,25)
    b = randrange(1,25)
  return a,b

def euclide(a,b):
  r=a
  r1=b
  u=1
  v=0
  u1=0
  v1=1
  while r1 != 0:
    q = int(r/r1)
    rs = r
    us = u
    vs = v
    r = r1
    u = u1
    v = v1
    r1 = rs - q*r1
    u1 = us - q*u1
    v1 = vs - q*v1
  return v

def cypher(mot,a,b,mode):
  print("a = {} et b = {}".format(a,b))
  motCypher = []
  if mode == 2:
    c = euclide(len(lettres),a)
    print("c = {}".format(c))
  for elt in mot:
    num = lettres.find(elt)
    if num != -1:
      if mode == 1:
        num = (num*a + b)%len(lettres)
      if mode == 2:
        num = (c*(num-b))%len(lettres)
      motCypher.append(lettres[num]) 
    else:
      motCypher.append(elt)
  return ''.join(motCypher)

if __name__ == "__main__":
  mot = input("Donnez le mot a chiffrer: ")
  mot.lower()
  a,b = genKey(lettres)
  motCypher = cypher(mot,a,b,1)
  print("Le mot chiffre est : " + motCypher)
  motDecrypt = cypher(motCypher,a,b,2)
  print("Le mot dechiffre est : " + motDecrypt)

