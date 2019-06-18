import cv2

im = cv2.imread('maca_girada.jpg')
imgray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
ret,thresh = cv2.threshold(imgray,127,255,0)
edges = cv2.Canny(imgray,100,300)
edgest = edges.copy()
ret,thresh = cv2.threshold(edges,127,255,0)
contours, hierarchy = cv2.findContours(thresh,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)

maior = 0 #descobrir qual conjunto de contornos tem mais pontos
for sizet in range(len(contours)):
	if (len(contours[sizet])>maior):
		maior = sizet
print ("indice com maior quantidade de pontos = ",maior)

#cv2.drawContours(im, contours, -1, (0,255,0), 3)
for contour in contours[maior]:#acessando cada lista(cooordenadas) da lista contorno
	#print(contour)
	#print("contour = " ,contour[0])
	cv2.circle(edges, (contour[0][0],contour[0][1]),2,(255,255,0),-1) #acessando as coordenadas de cada ponto e desenhar um circulo

cv2.imshow('image',edges)
cv2.imshow('original',edgest)
cv2.waitKey()
cv2.destroyAllWindows()
print("Quantidade de pontos =",len(contours[maior]))

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
	for i in range(len(ListOfPoints) - 1): 
		a = ListOfPoints[i][0]
		print("valor de A = ",a[0],a[1])
		b = ListOfPoints[i + 1][0]
		print("valor de B = ",b[0],b[1])
		chainCode.append(getChainCode(a[0], a[1], b[0], b[1])) 
	return chainCode 

chainCode = generateChainCode(contours[maior])

print("chain code = ", chainCode)
print("sum = ",sum(chainCode))

