#include "raylib/src/raylib.h"

int main(void) {
    // per aprire la finestra (Larghezza, Altezza, Titolo)
    InitWindow(800, 450, "Test");
    SetTargetFPS(60);
    //velocità del personaggio
    float speed= 4.0;
    //personaggio
    Rectangle pers={750, 0, 20.0,20.0};



    //prova sfondo 
    Texture2D sfondo = LoadTexture("/Users/wissal/Downloads/stanza1.png");
    SetTextureFilter(sfondo, TEXTURE_FILTER_POINT);




    //inventario
    Rectangle inv={20, 400, 180.0 ,30.0};
    int inventario[6]={0, 0, 0, 0, 0, 0};
    //CONTROLLO PER LA PRIMA STANZA
    bool armadioControllato = false;
    bool cassettoneControllato = false; 
    bool stanzaCompletata= false; 

    //armadio con pietra 
    Rectangle armadio={0, 10, 40.0, 80.0};
    //cassettone con lettera 
    Rectangle cassettone={760, 230, 40.0, 80.0};

    //box per la lavagna 
    Rectangle lav={200.0, 395.0, 90.0, 20.0};
    //box per lo specchio
    Rectangle sp={620.0, 390.0, 35.0, 10.0};
    //box per il tavolo ovale
    Rectangle Tovale={330, 30, 140.0, 60.0};
    //prove per coprire specchio e lavagna 
    Rectangle specchio= {607.0,378.0, 35.0,22.0};
    Rectangle lavagna= {165.0, 370.0, 80.0, 50.0};

    //array per gli ostacoli 
    Rectangle ostacoli[]={
        //banco centrale e i suoi laterali 
        {360, 210, 80.0, 30.0},   
        {210, 210, 80.0, 30.0},   
        {510, 210, 80.0, 30.0},   
    
        // Fila in basso
        {360, 290, 80.0, 30.0},
        {210, 290, 80.0, 30.0},   
        {510, 290, 80.0, 30.0},   
    
        //cattedra 
        {340, 380, 120.0, 50.0},
        //libreria 
        {0, 110, 40.0, 200.0},
        //cassettoni 
        {760, 90, 40.0, 80.0}
    };
    int numOstacoli = sizeof(ostacoli) /sizeof(ostacoli[0]);
    // Ciclo di gioco 
    while (!WindowShouldClose()) {
        //controllo se sto muovendo il personaggio 
        //movimento su X
        if(IsKeyDown(KEY_D)){
            pers.x+=speed; 
        }
        if(IsKeyDown(KEY_A)){
            pers.x-=speed; 
        }
        //movimento su Y
        if(IsKeyDown(KEY_S)){
            pers.y+=speed; 
        }
        if(IsKeyDown(KEY_W)){
            pers.y-=speed; 
        }
        //controllo la collisione contro le pareti 
        //sinistra
        if(pers.x<0){
            pers.x=0;
        }
        //destra
        if(pers.x>800-pers.width){
            pers.x=800-pers.width;
        }
        //alto
        if(pers.y < 0) {
            pers.y = 0;
        }
        //basso
        if(pers.y > 450 - pers.height) {
            pers.y = 450 - pers.height;
        }
        //controllo la collisione con gli ostacoli
        for(int i=0; i<numOstacoli; i++){
            if(CheckCollisionRecs(pers, ostacoli[i])){
                //devo fare l'opposto di quello che fanno i movimenti 
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;

                break;
                }
       }
       //collisione con il tavolo ovale 
       if(CheckCollisionRecs(pers, Tovale)){
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
       } 

       //collisione con la specchio 
       if(CheckCollisionRecs(pers, specchio)){
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
       }
       //collisione con la lavagna 
       if(CheckCollisionRecs(pers, lavagna)){
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
       } 

       //collisione con l'inventario
       if(CheckCollisionRecs(pers, inv)){
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
       } 

       //collisione con l'armadio 
       if(CheckCollisionRecs(pers, armadio)){
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
       } 

       //collisione con il cassettone 
       if(CheckCollisionRecs(pers, cassettone)){
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
       }

       //zona armadio da dove si puo cliccare
       Rectangle zonaArmadio={armadio.x - 5, armadio.y -5, armadio.width + 10, armadio.height + 10};
       //zona cassettone 
       Rectangle zonaCassettone={cassettone.x - 5, cassettone.y -5, cassettone.width + 10, cassettone.height + 10};

       //gestione collisioni quando si guadagnano gli oggetti 
       if(CheckCollisionRecs(pers,zonaArmadio) && IsKeyPressed(KEY_R) && !armadioControllato){
            for(int i=0; i<6; i++){
                if(inventario[i]==0){
                    inventario[i]=1; //ci aggiungo la pietra 
                    armadioControllato=true; 
                    break;
                }
            }
       }
       if(CheckCollisionRecs(pers,zonaCassettone) && IsKeyPressed(KEY_R) && !cassettoneControllato){
            for(int i=0; i<6; i++){
                if(inventario[i]==0){
                    inventario[i]=2; //ci aggiungo la lettera 
                    cassettoneControllato=true; 
                    break;
                }
            }
       }

       //zona specchio 
       Rectangle zonaSpecchio={specchio.x - 5, specchio.y -5, specchio.width + 20, specchio.height + 20};
       //collisione e check per finire la stanza 1
       if(CheckCollisionRecs(pers,zonaSpecchio) && IsKeyPressed(KEY_R) && !stanzaCompletata){
            bool haPietra= false; 
            int slotPietra= -1; 

            for(int i=0; i<6; i++){
                if (inventario[i]==1){
                    haPietra= true;
                    slotPietra= i;
                    break;
                }
            }

            if(haPietra){
                stanzaCompletata= true; 
                inventario[slotPietra]= 0; 
            }
       }


        BeginDrawing();

    //prova sfondo
    Rectangle sorgente = { 0.0f, 0.0f, (float)sfondo.width, (float)sfondo.height };

    // 2. Forza l'immagine a rimpicciolirsi ed entrare esattamente in 800x450
    Rectangle destinazione = { 0.0, 0.0, 800.0, 450.0 }; 

    // 3. Punto di ancoraggio (in alto a sinistra)
    Vector2 origine = { 0.0, 0.0 };

    // 4. Disegna lo sfondo perfettamente adattato alla stanza
    DrawTexturePro(sfondo, sorgente, destinazione, origine, 0.0f, WHITE);


        //ClearBackground(DARKGRAY); // Colore di sfondo
        //PRIMA STANZA 
            //tavolo ovale alla finestra 
            DrawEllipse(400, 60, 70.0, 30.0, BROWN); 
            //creazione banchi
            for(int i=0; i<numOstacoli; i++){
                DrawRectangleRec(ostacoli[i], BROWN);
            }
            //lavagna 
            Vector2 Vlav={lav.width / 2.0, lav.height/ 2.0}; //ruota dal centro 
            DrawRectanglePro(lav, Vlav, 35, BLACK);
            //specchio
            Vector2 Vsp={sp.width / 2.0, sp.height/ 2.0}; //ruota dal centro
            DrawRectanglePro(sp, Vsp, -40, GOLD);
            //armadio 
            DrawRectangleRec(armadio, RED);
            //cassettone 
            DrawRectangleRec(cassettone, PURPLE);

            //personaggio
            DrawRectangleRec(pers, BLUE);
            
            //blocco dell'inventario
            DrawRectangleRec(inv, PINK);
            //blocchi dell'inventario con 6 slot 
            for(int i=0; i<6; i++){
                float slot= 22.5 + (i* 30.0);
                DrawRectangleLines(slot, 402, 25, 25,LIGHTGRAY);


                //gestione inventario per la pietra e la lettera
                if(inventario[i]==1){ //pietra
                    DrawRectangle(slot + 3, 405, 19.0,19.0, RED);
                }
                if(inventario[i]==2){ //lettera
                    DrawRectangle(slot + 3, 405, 19, 19, GOLD);
                }

                //messaggio se ho finito la prima stanza 
                if(stanzaCompletata){
                    DrawText("Stanza 1 completata!", 230, 200, 30, GOLD);
                }

            }

        EndDrawing();
    }

    // per chiudere la finestra
    CloseWindow();
    return 0;
}