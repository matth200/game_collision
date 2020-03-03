#!/usr/bin/python3
import time
import pygame

FPS = 30.0

#function
def drawGrille(screen,width,height,square_w,square_h):
    #grille
    for i in range(int(width/square_w)):
        pygame.draw.line(screen,(255,255,255),(square_w*(1+i),0),(square_w*(1+i),height),2)
    for i in range(int(height/square_h)):
        pygame.draw.line(screen,(255,255,255),(0,square_h*(1+i)),(width,square_h*(1+i)),2)

def setText(screen,font,texte,x,y,color=(0,0,0)):
    surface = font.render(texte,True,color)
    pygame.Surface.blit(screen,surface,(x,y))

def displayText(screen,font):
    global width,height,square_w,square_h
    pygame.draw.rect(screen,(250,100,100),pygame.Rect(250*1-100,height+20,square_w,square_h))
    setText(screen,font,"bloc normal(click gauche)",250*1-50,height+30)

    pygame.draw.rect(screen,(0,0,0),pygame.Rect(250*2-100,height+20,square_w,square_h))
    texte = font.render("bloc vide(click droit)",True,(0,0,0))#0
    pygame.Surface.blit(screen,texte,(250*2-50,height+30))

    pygame.draw.rect(screen,(100,250,100),pygame.Rect(250*3-100,height+20,square_w,square_h))
    texte = font.render("bloc de fin(click gauche+z)",True,(0,0,0))#3
    pygame.Surface.blit(screen,texte,(250*3-50,height+30))

    pygame.draw.rect(screen,(0,100,100),pygame.Rect(250*4-100,height+20,square_w,square_h))
    texte = font.render("bloc de départ du joueur(click gauche+a)",True,(0,0,0))#2
    pygame.Surface.blit(screen,texte,(250*4-50,height+30))

#class
class Map:
    def __init__(self,width,height,square_w,square_h):
        self.width = width
        self.height = height
        self.square_w = square_w
        self.square_h = square_h

        self.bigMap = list()
        self.addNewMap()

        self.actualPage = 0
    def nextPage(self):
        self.actualPage+=1
        if self.actualPage>len(self.bigMap)-1:
            self.actualPage = len(self.bigMap)-1
    def precPage(self):
        self.actualPage-=1
        if self.actualPage < 0:
            self.actualPage = 0
    def saveFile(self,filename):
        print("Sauvegarde dans un fichier...")
        try:
            with open("0.level","w") as file:
                file.write(str(int(width/square_w))+" "+str(int(height/square_h))+" "+str(len(self.bigMap))+"\n")
                for imap, map in enumerate(self.bigMap):
                    file.write(str(imap)+"\n")    
                    for a in range(len(map[0])):
                        for i in range(len(map)):
                            t = map[i][a]
                            try:
                                file.write(str(t[0]))
                            except TypeError:
                                file.write(str(t))
                        file.write("\n")
        except:
            print("Erreur de fichier")
        finally:
            print("Okayyy!")
    def returnMap(self):
        return self.bigMap[self.actualPage]
    def draw(self,screen):
        map = self.returnMap()
        for i in range(int(self.width/self.square_w)):
            for a in range(int(self.height/self.square_h)):
                t = map[i][a]
                if t==0:
                    color = (100,100,100)
                if t==1:
                    color = (250,100,100)
                #si ajouté avec l'inventaire
                try:
                    color = t[1]
                except TypeError:
                    pass
                pygame.draw.rect(screen,color,pygame.Rect(self.square_w*i,self.square_h*a,self.square_w,self.square_h))
    def addNewMap(self):
        #map de 50*50
        map = list()
        for i in range(int(width/square_w)):
            colonne = list()
            for a in range(int(height/square_h)):
                colonne.append(0)
            map.append(colonne)
        self.bigMap.append(map)

class Inventaire:
    def __init__(self,font,keys):
        self.objects = list()
        self.font = font
        self.keys = keys
    def addIcon(self,color,key,texte):
        self.keys[key] = 0
        self.objects.append((color,key,texte,len(self.objects)+2))
    def applyKeys(self,map,x,y):
        for objectt in self.objects:
            key = objectt[1]
            try:
                if self.keys[key]:
                    map[x][y] = (objectt[3],objectt[0])
            except KeyError:
                pass
    def draw(self,screen):
        global width,height,square_w,square_h

        color = (255,0,0)
        setText(screen,font,"Appuye sur ENTRER",10,height+30,color)
        setText(screen,font,"pour enregistrer",20,height+45,color)
        
        for i,objectt in enumerate(self.objects):
            texte = objectt[2]
            color = objectt[0]
            pygame.draw.rect(screen,color,pygame.Rect(150*(i+1),height+20,square_w,square_h))
            setText(screen,font,texte,150*(i+1)+50,height+30)



#main program
pygame.init()
pygame.font.init()

width, height = 1280,720
size = width, height+70
square_w, square_h = 40,40

screen = pygame.display.set_mode(size)
pygame.display.set_caption("Creation de niveau")
background_color = (100,100,100)

font = pygame.font.Font(pygame.font.get_default_font(),12)

continuer = 1

#map
cleverMap = Map(width,height,square_w,square_h)

#button used
keys_activation = {}
keys_activation[pygame.MOUSEBUTTONDOWN] = 0

#inventaire
tools = Inventaire(font,keys_activation)
tools.addIcon((255,0,0),pygame.K_a,"Start(a)")
tools.addIcon((0,255,0),pygame.K_z,"End(z)")
tools.addIcon((0,255,255),pygame.K_w,"Bloc(w)")

while continuer:
    start = time.time()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            continuer = 0
        if event.type == pygame.MOUSEBUTTONDOWN:
            keys_activation[pygame.MOUSEBUTTONDOWN] = 1
            bouton = event.button
        if event.type == pygame.MOUSEBUTTONUP:
            keys_activation[pygame.MOUSEBUTTONDOWN] = 0
        if event.type == pygame.KEYDOWN:
            for key in keys_activation.keys():
                if event.key == key:
                    keys_activation[key] = 1
            if event.key == pygame.K_RETURN:
                cleverMap.saveFile("0.level")
        if event.type == pygame.KEYUP:
            for key in keys_activation.keys():
                if event.key == key:
                    keys_activation[key] = 0
    #control
    if keys_activation[pygame.MOUSEBUTTONDOWN]:
        x,y = pygame.mouse.get_pos()
        i,a = int(x/square_w),int(y/square_h)
        map = cleverMap.returnMap()
        if y<height:
            if bouton == 1:
                map[i][a] = 1
                tools.applyKeys(map,i,a)
            if bouton == 3:
                map[i][a] = 0

    screen.fill(background_color)
    cleverMap.draw(screen)

    drawGrille(screen,width,height,square_w,square_h)

    #texte en bas
    #displayText(screen,font)
    tools.draw(screen)

    pygame.display.flip()

    ellapsed = time.time()-start
    if(ellapsed < 1.0/FPS):
        time.sleep(1.0/FPS-ellapsed)
    #print("FPS:",1.0/(time.time()-start))

pygame.font.quit()
pygame.quit()
