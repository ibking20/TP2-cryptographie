from random import randrange

alphabet = "abcdefghijklmnopqrstuvwxyz"
def cypher(mot,key,mode):
  k=0
  print("La cle est : {}".format(key))
  motCypher = []
  for elt in mot:
    num = alphabet.find(elt)
    if num != -1:
      if mode == 1:
        num += alphabet.find(key[k])
      elif mode == 2:
        num -= alphabet.find(key[k])
      num %= len(alphabet)
      motCypher.append(alphabet[num])
      k+=1
      if k == len(key):
        k=0
    else:
        motCypher.append(elt)
  return ''.join(motCypher)

if __name__ == "__main__":
  mot = input("Donnez le mot a chiffrer:")
  mot = mot.lower()
  key = input("Quelle est la clé ? ")
  motCypher = cypher(mot,key,1)
  print("Le mot chiffre est: " + motCypher)
  motDecypher = cypher(motCypher,key,2)
  print("Le mot Dechiffre est: " + motDecypher)
