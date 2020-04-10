

frequences = [9.42,1.02,2.64,3.39,15.87,0.95,1.04,0.77,8.41,0.89,0.00,5.34,3.24,7.15,5.14,2.86,1.06,6.46,7.90,7.26,6.24,2.15,0.00,0.30,0.24,0.32]
lettres = "EAISTNRULODMPCVQGBFJHZXYKW"
def count(texte):
  alphabet = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
  ltr = []
  maxltr = len(texte) - texte.count(' ') - texte.count('\'') - texte.count('.') - texte.count(',') - texte.count("\"") - texte.count("É") - texte.count("È") - texte.count("Ê") - texte.count("Ù") - texte.count("Œ") - texte.count("Û")
  occurences = []
  for elt in alphabet:
    occurences.append((texte.count(elt)*100)/maxltr)
    print(elt + "= {}".format((texte.count(elt)*100)/maxltr))
  i,j=0,0
  max = 0
  while i < len(occurences)-1:
    max = i
    j=i+1
    while j < len(occurences):
      if occurences[j] > occurences[i]:
        max=j
        occurences[max],occurences[i]=occurences[i],occurences[max]
        alphabet[max],alphabet[i] =alphabet[i],alphabet[max]
      j+=1
    i+=1

  alphabet = ''.join(alphabet)
  print(alphabet)
  print(lettres)
  Decrypt = []
  for elt in texte:
    num = alphabet.find(elt)
    if num != -1:
      Decrypt.append(lettres[num])
    else:
      Decrypt.append(elt)
  return ''.join(Decrypt)

if __name__ == "__main__":
  texte = input("Entrez le texte: ")
  texte =  texte.upper()
  print(count(texte))
