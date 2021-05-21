#!usr/bin/python

from random import randrange

alphabet = "abcdefghijklmnopqrstuvwxyz"
key= int()

def genKey():
  return randrange(1,25)

def decalage(key):
  i=0
  j=key
  t=str()
  while j < 26:
    t+= alphabet[j]
    j+=1
  while i < key:
    t+= alphabet[i]
    i+=1
  return t

def cypher(mot):
  key= genKey()
  print("La cle est : {}".format(key))
  motCypher=str()
  t = decalage(key)
  for elt in mot:
    num = alphabet.find(elt)
    if num != -1:
      motCypher+= t[num]
    else:
      motCypher+= elt
  return t,motCypher

def decypher(mot,t):
  motCypher=str() 
  for elt in mot:
    num = t.find(elt)
    if num != -1:
      motCypher+= alphabet[num]
    else:
      motCypher+= elt
  return motCypher

if __name__ == "__main__":
  mot = input("Donnez le mot a chiffrer:")
  mot =  mot.lower()
  t, motCypher = cypher(mot)
  print("Le mot chiffre est: " + motCypher)
  motDecypher = decypher(motCypher,t)
  print("Le mot Dechiffre est: " + motDecypher)

