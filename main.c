#include "raylib/src/raylib.h"

int main(void) {
    // per aprire la finestra (Larghezza, Altezza, Titolo)
    InitWindow(800, 450, "Test");
    SetTargetFPS(60);

    //velocità del personaggio
    float speed= 3.0;
    //personaggio
    Rectangle pers={280, 300, 45.0,80.0};

    //prova personaggio
    Texture2D texFermo    = LoadTexture("/Users/wissal/Downloads/Frontale.png");

    Texture2D texDestra   = LoadTexture("/Users/wissal/Downloads/Laterale2.png");
    Texture2D texDestra1  = LoadTexture("/Users/wissal/Downloads/D1.png"); 
    Texture2D texDestra2  = LoadTexture("/Users/wissal/Downloads/D2.png"); 

    Texture2D texSinistra   = LoadTexture("/Users/wissal/Downloads/Laterale.png");
    Texture2D texSinistra1  = LoadTexture("/Users/wissal/Downloads/S1.png"); 
    Texture2D texSinistra2  = LoadTexture("/Users/wissal/Downloads/S2.png"); 

    Texture2D texSu       = LoadTexture("/Users/wissal/Downloads/Back.png");
    
    SetTextureFilter(texFermo, TEXTURE_FILTER_POINT); //per non sgranare
    SetTextureFilter(texDestra, TEXTURE_FILTER_POINT);
    SetTextureFilter(texDestra1, TEXTURE_FILTER_POINT);
    SetTextureFilter(texDestra2, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSinistra, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSinistra1, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSinistra2, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSu, TEXTURE_FILTER_POINT);  

    //il personaggio all'inzio deve sempre essere fermo 
    Texture2D *textureCorrente = &texFermo;

    //variabili per animare il personaggio
    int frameCounter = 0;
    int animazioneFrame = 0;
    int velocitaAnimazione = 10; // Cambia frame ogni 10 cicli 
    int direzioneSpecifica = 0;  // 0: Fronte, 1: Destra, 2: Sinistra, 3: Retro



    //prova sfondo 
    Texture2D sfondo = LoadTexture("/Users/wissal/Downloads/stanza1sfondo2.png");
    SetTextureFilter(sfondo, TEXTURE_FILTER_POINT);

    //inventario
    Rectangle inv={20, 400, 180.0 ,30.0};
    int inventario[6]={0, 0, 0, 0, 0, 0};
    //CONTROLLO PER LA PRIMA STANZA
    bool armadioControllato = false;
    bool cassettoneControllato = false; 
    bool stanzaCompletata= false; 

    //gabbia 
    Rectangle gabbia={685, 350, 80.0, 80.0};
    //impedire il passaggio a sinistra 
    Rectangle muro={40, 150, 30.0, 50.0};
    //armadio con pietra 
    Rectangle armadio={70, 50, 80.0, 50.0};
    //cassettone con lettera 
    Rectangle cassettone={650, 220, 100.0, 25.0};

    //box per il muro sopra
    Rectangle Tovale={160, 70, 600.0, 30.0};
    //prove per coprire specchio e lavagna 
    Rectangle specchio= {545.0,350.0, 66.0,100.0};
    Rectangle lavagna= {190.0, 350.0, 70.0, 50.0};

    //array per gli ostacoli 
    Rectangle ostacoli[]={
        //banco centrale e i suoi laterali 
        {375, 205, 50.0, 20.0},   
        {255, 205, 50.0, 20.0},   
        {505, 205, 50.0, 20.0},   
    
        // Fila in basso
        {375, 260, 50.0, 30.0},
        {255, 260, 50.0, 30.0},   
        {505, 260, 50.0, 30.0},   
    
        //cattedra 
        {345, 390, 120.0, 50.0},
        //libreria 
        {0, 200, 168.0, 135.0},
        //cassettone 
        {760, 0, 40.0, 450.0}
    };
    int numOstacoli = sizeof(ostacoli) /sizeof(ostacoli[0]);
    // Ciclo di gioco 
    while (!WindowShouldClose()) {
        //di base il personaggio è fermo 
        textureCorrente = &texFermo;

        //controllo se sto muovendo il personaggio 
        bool inMovimento = false;
       //movimento su X 
        if (IsKeyDown(KEY_D)) {
            pers.x += speed; 
            direzioneSpecifica = 1; 
            inMovimento = true;
        }
        //movimento su Y
        else if (IsKeyDown(KEY_A)) {
            pers.x -= speed; 
            direzioneSpecifica = 2; 
            inMovimento = true;
        }

        else if (IsKeyDown(KEY_S)) {
            pers.y += speed; 
            direzioneSpecifica = 0; 
            inMovimento = true;
        }
        else if (IsKeyDown(KEY_W)) {
            pers.y -= speed; 
            direzioneSpecifica = 3; 
            inMovimento = true;
        }

        // animazione 
        if (inMovimento) {
            frameCounter++;
            if (frameCounter >= velocitaAnimazione) {
                frameCounter = 0;
                // Alterna il frame 
                animazioneFrame = (animazioneFrame == 0) ? 1 : 0; 
            }
        } else {
            // Se fermo, resetta il timer e mostra la posa base
            frameCounter = 0;
            animazioneFrame = 0; 
        }

        
        if (direzioneSpecifica == 1) { // destra
            if (inMovimento) {
                textureCorrente = (animazioneFrame == 0) ? &texDestra1 : &texDestra2;
            } else {
                textureCorrente = &texDestra;
            }
        }
        else if (direzioneSpecifica == 2) { // sinistra
            if (inMovimento) {
                textureCorrente = (animazioneFrame == 0) ? &texSinistra1 : &texSinistra2;
            } else {
                textureCorrente = &texSinistra;
            }
        }
        else if (direzioneSpecifica == 3) { // back 
            textureCorrente = &texSu; // Espandibile se avrai passi per il retro
        }
        else { // FRONTE
            textureCorrente = &texFermo; // Espandibile se avrai passi per il fronte
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
       //collisione con la gabbia
       if(CheckCollisionRecs(pers, gabbia)){
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

       //collisione muro sinistro
       if(CheckCollisionRecs(pers, muro)){
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
            
    //personaggio 
    if (textureCorrente->width > 0 && textureCorrente->height > 0) {
    Rectangle sorgentePers = { 0.0f, 0.0f, (float)textureCorrente->width, (float)textureCorrente->height };
    Rectangle destinazionePers = { pers.x, pers.y, pers.width, pers.height };
    Vector2 originePers = { 0.0f, 0.0f };
    DrawTexturePro(*textureCorrente, sorgentePers, destinazionePers, originePers, 0.0f, WHITE);
    }   else {
    DrawRectangleRec(pers, BLUE);
    }

            //blocco dell'inventario
            DrawRectangleRec(inv, (Color){ 44, 34, 31, 255 });
            //blocchi dell'inventario con 6 slot 
            for(int i=0; i<6; i++){
                float slot= 22.5 + (i* 30.0);
                DrawRectangleLines(slot, 402, 25, 25,GRAY);


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

    UnloadTexture(sfondo);
    UnloadTexture(texFermo);
    UnloadTexture(texDestra);
    UnloadTexture(texDestra1);
    UnloadTexture(texDestra2);
    UnloadTexture(texSinistra);
    UnloadTexture(texSinistra1);
    UnloadTexture(texSinistra2);
    UnloadTexture(texSu);
    // per chiudere la finestra
    CloseWindow();
    return 0;
}