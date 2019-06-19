import cv2
import argparse

ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required = True, help = "Path to the image")
args = vars(ap.parse_args())

font = cv2.FONT_HERSHEY_SIMPLEX

im = cv2.imread(args["image"])
#im = cv2.imread('feed-me.jpeg')
imgray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
ret,thresh = cv2.threshold(imgray,127,255,0)
canny = cv2.Canny(imgray,100,300)
edges = canny.copy()
edges_cp = edges.copy()
edges_poly = edges.copy()
ret,thresh = cv2.threshold(edges,127,255,0)
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

maior = 0 #descobrir qual conjunto de contornos tem mais pontos
for sizet in range(len(contours)):
	if (len(contours[sizet])>maior):
		maior = sizet
print ("indice com maior quantidade de pontos = ",maior)
print("indices de contorno = ",len(contours))


#Pegando a cadeia de freeman

def getChainCode(x1, y1, x2, y2): 
	dx = x2 - x1 
	dy = y2 - y1 
	
	if dx>0: #Significa que as posições podem ser (5,4,3)
		if dy <0 :
			code = 5
		elif dy==0:
			code = 4
		else:
			code = 3

	elif dx==0: # Significa que as posicoes podem ser (6,2)
		if dy<0:
			code = 6
		elif dy>0:
			code = 2
		else:
			code=8

	else: #Significa que as posicoes podem ser (7,0,1)
		if dy<0:
			code = 7
		elif dy==0:
			code = 0
		else:
			code = 1

	return code 

def generateChainCode(ListOfPoints): 
	chainCode = [] 
	textChain = " "
	for i in range(len(ListOfPoints)):
		a = ListOfPoints[i][0]
		#print("valor de A = ",a[0],a[1]) 
		if i != len(ListOfPoints)-1:
			b = ListOfPoints[i + 1][0]
			#print("valor de B = ",b[0],b[1])
		else :
			b = ListOfPoints[0][0] 
		chainCode.append(getChainCode(a[0], a[1], b[0], b[1]))
		textChain = textChain + str(getChainCode(a[0], a[1], b[0], b[1]))
		textChainT = str(getChainCode(a[0], a[1], b[0], b[1]))
		#DESCOMENTAR A LINHA ABAIXO PARA MOSTRAR O CODIGO DE CADA PONTO
		#cv2.putText(edges,textChainT, (a[0],a[1]), cv2.FONT_HERSHEY_SIMPLEX, 0.3,(255,255,255),1,cv2.LINE_AA)
	return chainCode,textChain 

for ind_contour in range(len(contours)):
	for contour in contours[ind_contour]:#acessando cada lista(cooordenadas) da lista contorno
	#print(contour)
	#print("contour = " ,contour[0])
		cv2.circle(edges, (contour[0][0],contour[0][1]),2,(255,255,0),-1) #acessando as coordenadas de cada ponto e desenhar um circulo
	edges_poly = cv2.polylines(edges_poly,contours,True,(122,255,255),3)#desenhando o poligono de acordo com os pontos
	chainCode,tsx = generateChainCode(contours[ind_contour])
	cv2.putText(edges,str(ind_contour), (((contours[ind_contour])[0][0])[0],((contours[ind_contour])[0][0])[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5,(255,255,255),1,cv2.LINE_AA)
	print("chain code ",ind_contour," = ", tsx)
	print("sum ",ind_contour," = ",sum(chainCode))
	print("Quantidade de pontos =",len(contours[ind_contour]))




cv2.imshow('original',im)
cv2.imshow('canny',canny)
cv2.imshow('Pontos',edges)
cv2.imshow('poligono',edges_poly)
cv2.waitKey()
cv2.destroyAllWindows()




