from sklearn.neighbors import KNeighborsClassifier
from pathlib import Path
import cv2
import numpy as np

path = Path().absolute().parent.parent.parent

#K-NN calcula os vizinhos mais proximos para designar qual classificação dar para o objeto

# Lista de caracteristicas que são os momentos de Hu de 12 imagens diferentes
caracteristicas = [
[3.10,  11.98,  14.68,  16.86, -32.64,  22.85,  33.25],
[3.11,  12.36,  14.63,  17.06,  32.99,  23.34,  33.16],
[3.07,  12.26,  14.62,  15.32,  31.40, -22.69, -30.30],
[3.10,  11.98,  14.68,  16.86, -32.64,  22.85,  33.25],
[3.11,  12.36,  14.63,  17.06,  32.99,  23.34,  33.16],
[3.07,  12.26,  14.62,  15.32,  31.40, -22.69, -30.30],
[3.12,  11.72,  14.76,  15.33,  32.08,  21.40,  30.37],
[3.14,  11.78,  14.83,  15.59, -34.29,  21.71,  30.81],
[3.13,  10.43,  14.77,  15.44,  31.55,  20.75,  30.54],
[3.12,  11.72,  14.76,  15.33,  32.08,  21.40,  30.37],
[3.14,  11.78,  14.83,  15.59, -34.29,  21.71,  30.81],
[3.13,  10.43,  14.77,  15.44,  31.55,  20.75,  30.54]
]

# Classificações para os momentos que seguem a mesma ordem que as características
classificacoes = [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]

# Gerando o classificador com o número de vizinhos que o algoritmo deve considerar:
knn = KNeighborsClassifier(3)

# Fazendo o treinamento do classificador:
knn.fit(caracteristicas, classificacoes)

# Validando o classificador: 0 ... 1;
print ("Validação do treinamento: ", knn.score(caracteristicas, classificacoes))

# Classificando objeto desconhecido:
objetos = [[3.17, 11.84, 14.91, 16.22, -33.21, 22.38, 31.78],
[3.17, 11.82, 14.91, 16.21, -33.38, 22.33, 31.77]]

print(knn.predict(objetos))

knn1 = cv2.imread(f"{path}/Images/KNN/knn1.bmp",0)
knn2 = cv2.imread(f"{path}/Images/KNN/knn2.bmp",0)

momentos = cv2.moments(knn1, True)

hu = cv2.HuMoments(momentos)
hu = -np.sign(hu) * np.log10(np.abs(hu))

hugo = list()

for i in range (0,7):
    hugo.append(hu[i][0])

hugo = [hugo]

print(knn.predict(hugo))

