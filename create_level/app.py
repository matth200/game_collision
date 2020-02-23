#!/usr/bin/python3
import time
import pygame

FPS = 30.0

pygame.init()

size = width, height = 1200,600
square_w, square_h = 40,40

screen = pygame.display.set_mode(size)
pygame.display.set_caption("Creation de niveau:")
background_color = (100,100,100)

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
            if event.key == pygame.K_RETURN:
                with open("0.level","w") as file:
                    for a in range(len(map[0])):
                        for i in range(len(map)):
                            file.write(str(map[i][a]))
                        file.write("\n")
                    print("Sauvegarde dans un fichier...")
                    print("Okayyy")
    #control
    if k_mouseboutondown:
        x,y = pygame.mouse.get_pos()
        i,a = int(x/square_w),int(y/square_h)
        if bouton == 1:
            map[i][a] = 1
        if bouton == 3:
            map[i][a] = 0

    screen.fill(background_color)
    #map
    for i in range(int(width/square_w)):
        for a in range(int(height/square_h)):
            if map[i][a]==0:
                color = (100,100,100)
            if map[i][a]==1:
                color = (250,100,100)
            pygame.draw.rect(screen,color,pygame.Rect(square_w*i,square_h*a,square_w,square_h))

    #grille
    for i in range(int(width/square_w)):
        pygame.draw.line(screen,(255,255,255),(square_w*(1+i),0),(square_w*(1+i),height),2)
    for i in range(int(height/square_h)):
        pygame.draw.line(screen,(255,255,255),(0,square_h*(1+i)),(width,square_h*(1+i)),2)

    pygame.display.flip()

    ellapsed = time.time()-start
    if(ellapsed < 1.0/FPS):
        time.sleep(1.0/FPS-ellapsed)
    #print("FPS:",1.0/(time.time()-start))

pygame.quit()
