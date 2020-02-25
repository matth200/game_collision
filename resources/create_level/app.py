#!/usr/bin/python3
import time
import pygame

FPS = 30.0

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

#map de 50*50
map = list()
for i in range(int(width/square_w)):
    colonne = list()
    for a in range(int(height/square_h)):
        colonne.append(0)
    map.append(colonne)

k_mouseboutondown = 0
bouton = 1
bouton_a = 0
bouton_z = 0

while continuer:
    start = time.time()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            continuer = 0
        if event.type == pygame.MOUSEBUTTONDOWN:
            k_mouseboutondown = 1
            bouton = event.button
        if event.type == pygame.MOUSEBUTTONUP:
            k_mouseboutondown = 0
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_a:
                bouton_a = 1
            if event.key == pygame.K_z:
                bouton_z = 1
            if event.key == pygame.K_RETURN:
                with open("0.level","w") as file:
                    file.write(str(int(width/square_w))+" "+str(int(height/square_h))+"\n")
                    for a in range(len(map[0])):
                        for i in range(len(map)):
                            file.write(str(map[i][a]))
                        file.write("\n")
                    print("Sauvegarde dans un fichier...")
                    print("Okayyy")
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_a:
                bouton_a = 0
            if event.key == pygame.K_z:
                bouton_z = 0
    #control
    if k_mouseboutondown:
        x,y = pygame.mouse.get_pos()
        i,a = int(x/square_w),int(y/square_h)
        if y<height:
            if bouton == 1:
                map[i][a] = 1
            if bouton == 3:
                map[i][a] = 0
            if bouton_a:
                map[i][a] = 2
            if bouton_z:
                map[i][a] = 3

    screen.fill(background_color)
    #map
    for i in range(int(width/square_w)):
        for a in range(int(height/square_h)):
            if map[i][a]==0:
                color = (100,100,100)
            if map[i][a]==1:
                color = (250,100,100)
            if map[i][a]==2:
                color = (0,100,100)
            if map[i][a]==3:
                color = (100,250,100)
            pygame.draw.rect(screen,color,pygame.Rect(square_w*i,square_h*a,square_w,square_h))

    #grille
    for i in range(int(width/square_w)):
        pygame.draw.line(screen,(255,255,255),(square_w*(1+i),0),(square_w*(1+i),height),2)
    for i in range(int(height/square_h)):
        pygame.draw.line(screen,(255,255,255),(0,square_h*(1+i)),(width,square_h*(1+i)),2)

    #texte en bas
    pygame.draw.rect(screen,(250,100,100),pygame.Rect(250*1-100,height+20,square_w,square_h))
    texte = font.render("bloc normal(click gauche)",True,(0,0,0))#1
    pygame.Surface.blit(screen,texte,(250*1-50,height+30))

    pygame.draw.rect(screen,(0,0,0),pygame.Rect(250*2-100,height+20,square_w,square_h))
    texte = font.render("bloc vide(click droit)",True,(0,0,0))#0
    pygame.Surface.blit(screen,texte,(250*2-50,height+30))

    pygame.draw.rect(screen,(100,250,100),pygame.Rect(250*3-100,height+20,square_w,square_h))
    texte = font.render("bloc de fin(click gauche+z)",True,(0,0,0))#3
    pygame.Surface.blit(screen,texte,(250*3-50,height+30))

    pygame.draw.rect(screen,(0,100,100),pygame.Rect(250*4-100,height+20,square_w,square_h))
    texte = font.render("bloc de départ du joueur(click gauche+a)",True,(0,0,0))#2
    pygame.Surface.blit(screen,texte,(250*4-50,height+30))


    texte = font.render("Appuye sur ENTRER",True,(255,0,0))
    pygame.Surface.blit(screen,texte,(10,height+30))
    texte = font.render("pour enregistrer",True,(255,0,0))
    pygame.Surface.blit(screen,texte,(20,height+45))

    pygame.display.flip()

    ellapsed = time.time()-start
    if(ellapsed < 1.0/FPS):
        time.sleep(1.0/FPS-ellapsed)
    #print("FPS:",1.0/(time.time()-start))

pygame.font.quit()
pygame.quit()
