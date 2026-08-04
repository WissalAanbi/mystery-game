#include "raylib/src/raylib.h"

int main(void) {
    // Aprire la finestra (Larghezza, Altezza, Titolo)
    InitWindow(800, 450, "Test");
    SetTargetFPS(60);

    // Velocità del personaggio
    float speed = 3.0;
    // Personaggio
    Rectangle pers = {280, 300, 45.0, 80.0};

    // Caricamento Texture Personaggio
    Texture2D texFermo      = LoadTexture("/Users/wissal/Downloads/Frontale.png");
    Texture2D texDestra     = LoadTexture("/Users/wissal/Downloads/Laterale2.png");
    Texture2D texDestra1    = LoadTexture("/Users/wissal/Downloads/D1.png"); 
    Texture2D texDestra2    = LoadTexture("/Users/wissal/Downloads/D2.png"); 
    Texture2D texSinistra   = LoadTexture("/Users/wissal/Downloads/Laterale.png");
    Texture2D texSinistra1  = LoadTexture("/Users/wissal/Downloads/S1.png"); 
    Texture2D texSinistra2  = LoadTexture("/Users/wissal/Downloads/S2.png"); 
    Texture2D texSu         = LoadTexture("/Users/wissal/Downloads/Back.png");
    
    // Filtri per non sgranare (Pixel Art)
    SetTextureFilter(texFermo, TEXTURE_FILTER_POINT);
    SetTextureFilter(texDestra, TEXTURE_FILTER_POINT);
    SetTextureFilter(texDestra1, TEXTURE_FILTER_POINT);
    SetTextureFilter(texDestra2, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSinistra, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSinistra1, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSinistra2, TEXTURE_FILTER_POINT);
    SetTextureFilter(texSu, TEXTURE_FILTER_POINT);  

    Texture2D *textureCorrente = &texFermo;

    // Variabili per animazione
    int frameCounter = 0;
    int animazioneFrame = 0;
    int velocitaAnimazione = 10; 
    int direzioneSpecifica = 0;  // 0: Fronte, 1: Destra, 2: Sinistra, 3: Retro

    // Gestione Stanze 
    int stanzaCorrente = 0;

    // Sfondi stanze
    Texture2D sfondo = LoadTexture("/Users/wissal/Downloads/stanza1sfondo2.png");
    SetTextureFilter(sfondo, TEXTURE_FILTER_POINT);

    Texture2D sfondo2 = LoadTexture("/Users/wissal/Downloads/stanza2.png");
    SetTextureFilter(sfondo2, TEXTURE_FILTER_POINT);

    // Schermate 
    Texture2D schermata1 = LoadTexture("/Users/wissal/Downloads/schermata1.png");
    SetTextureFilter(schermata1, TEXTURE_FILTER_POINT);

    Texture2D schermata2 = LoadTexture("/Users/wissal/Downloads/schermata2.png");
    SetTextureFilter(schermata2, TEXTURE_FILTER_POINT);

    Texture2D schermata3 = LoadTexture("/Users/wissal/Downloads/schermata3.png");
    SetTextureFilter(schermata3, TEXTURE_FILTER_POINT);

    // Logo
    Texture2D logo = LoadTexture("/Users/wissal/Downloads/logo.png");
    SetTextureFilter(logo, TEXTURE_FILTER_POINT);

    // Inventario
    Rectangle inv = {20, 400, 180.0, 30.0};
    int inventario[6] = {0, 0, 0, 0, 0, 0};

    // Stato di gioco stanza 1
    bool armadioControllato = false;
    bool cassettoneControllato = false; 
    bool stanzaCompletata = false; 

    // Ostacoli specifici stanza 1
    Rectangle gabbia = {685, 350, 80.0, 80.0};
    Rectangle muro = {40, 150, 30.0, 50.0};
    Rectangle armadio = {70, 50, 80.0, 50.0};
    Rectangle cassettone = {650, 220, 100.0, 25.0};
    Rectangle Tovale = {160, 70, 600.0, 30.0};
    Rectangle specchio = {545.0, 350.0, 66.0, 100.0};
    Rectangle lavagna = {190.0, 350.0, 70.0, 50.0};

    Rectangle ostacoli[] = {
        {375, 205, 50.0, 20.0}, {255, 205, 50.0, 20.0}, {505, 205, 50.0, 20.0},   
        {375, 260, 50.0, 30.0}, {255, 260, 50.0, 30.0}, {505, 260, 50.0, 30.0},   
        {345, 390, 120.0, 50.0}, {0, 200, 168.0, 135.0}, {760, 0, 40.0, 450.0}
    };
    int numOstacoli = sizeof(ostacoli) / sizeof(ostacoli[0]);

    // Stati di interazione nella stanza 3
    bool uovoControllato = false;
    bool stanzaCompletata2 = false; 

    // Oggetti in collisione nella stanza 3
    Rectangle piscina = {250, 220, 350.0, 90.0};
    Rectangle parete = {160, 70, 600.0, 30.0};
    Rectangle sinistra =  {0, 0, 100.0, 450.0};
    Rectangle destra = {710, 0, 50.0, 450.0};
    Rectangle sinistra2 = {0, 0, 170.0, 170.0};
    Rectangle uovo = {297, 99, 30.0, 80.0};
    Rectangle basso = {0, 400, 800.0, 30.0};
    Rectangle coppa = {477, 99, 30.0, 80.0};

    // Ciclo di gioco 
    while(!WindowShouldClose()) {
        
        bool inMovimento = false;

        // Input di movimento
        if (IsKeyDown(KEY_D)) {
            pers.x += speed; 
            direzioneSpecifica = 1; 
            inMovimento = true;
        }
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

        // Calcolo frame animazione
        if (inMovimento) {
            frameCounter++;
            if (frameCounter >= velocitaAnimazione) {
                frameCounter = 0;
                animazioneFrame = (animazioneFrame == 0) ? 1 : 0; 
            }
        } else {
            frameCounter = 0;
            animazioneFrame = 0; 
        }

        // Assegnazione texture in base alla direzione
        if (direzioneSpecifica == 1) {
            textureCorrente = inMovimento ? ((animazioneFrame == 0) ? &texDestra1 : &texDestra2) : &texDestra;
        }
        else if (direzioneSpecifica == 2) {
            textureCorrente = inMovimento ? ((animazioneFrame == 0) ? &texSinistra1 : &texSinistra2) : &texSinistra;
        }
        else if (direzioneSpecifica == 3) {
            textureCorrente = &texSu;
        }
        else {
            textureCorrente = &texFermo;
        }

        // Limiti dei bordi della finestra
        if (pers.x < 0) pers.x = 0;
        if (pers.x > 800 - pers.width) pers.x = 800 - pers.width;
        if (pers.y < 0) pers.y = 0;
        if (pers.y > 450 - pers.height) pers.y = 450 - pers.height;

        // Schermata di base
        if (stanzaCorrente == 0){
            if (IsKeyPressed(KEY_SPACE)) {
                stanzaCorrente = 1;
                pers.x = 600;
                pers.y = 200;
            } 
        }
        // LOGICA SPECIFICA STANZA 1
        else if (stanzaCorrente == 1) {
            
            for (int i = 0; i < numOstacoli; i++) {
                if (CheckCollisionRecs(pers, ostacoli[i])) {
                    if (IsKeyDown(KEY_D)) pers.x -= speed;
                    if (IsKeyDown(KEY_A)) pers.x += speed;
                    if (IsKeyDown(KEY_S)) pers.y -= speed;
                    if (IsKeyDown(KEY_W)) pers.y += speed;
                    break;
                }
            }
            
            if (CheckCollisionRecs(pers, Tovale) || CheckCollisionRecs(pers, gabbia) || 
                CheckCollisionRecs(pers, specchio) || CheckCollisionRecs(pers, lavagna) || 
                CheckCollisionRecs(pers, inv) || CheckCollisionRecs(pers, armadio) || 
                CheckCollisionRecs(pers, cassettone) || CheckCollisionRecs(pers, muro)) {
                
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
            }

            Rectangle zonaArmadio = {armadio.x - 5, armadio.y - 5, armadio.width + 10, armadio.height + 10};
            Rectangle zonaCassettone = {cassettone.x - 5, cassettone.y - 5, cassettone.width + 10, cassettone.height + 10};
            Rectangle zonaSpecchio = {specchio.x - 5, specchio.y - 5, specchio.width + 20, specchio.height + 20};

            if (CheckCollisionRecs(pers, zonaArmadio) && IsKeyPressed(KEY_R) && !armadioControllato) {
                for (int i = 0; i < 6; i++) {
                    if (inventario[i] == 0) {
                        inventario[i] = 1; // Pietra
                        armadioControllato = true; 
                        break;
                    }
                }
            }
            if (CheckCollisionRecs(pers, zonaCassettone) && IsKeyPressed(KEY_R) && !cassettoneControllato) {
                for (int i = 0; i < 6; i++) {
                    if (inventario[i] == 0) {
                        inventario[i] = 2; // Lettera
                        cassettoneControllato = true; 
                        break;
                    }
                }
            }

            if (CheckCollisionRecs(pers, zonaSpecchio) && IsKeyPressed(KEY_R) && !stanzaCompletata) {
                int slotPietra = -1; 
                for (int i = 0; i < 6; i++) {
                    if (inventario[i] == 1) {
                        slotPietra = i;
                        break;
                    }
                }
                if (slotPietra != -1) {
                    stanzaCompletata = true; 
                    inventario[slotPietra] = 0;
                }
            }

            if (stanzaCompletata && IsKeyPressed(KEY_SPACE)) {
                stanzaCorrente = 2;
            }
        }
        else if (stanzaCorrente == 2) {
            if (IsKeyPressed(KEY_SPACE)) {
                stanzaCorrente = 3;
                pers.x = 200;
                pers.y = 200;
            }
        }
        // --- LOGICA SPECIFICA STANZA 3 ---
        else if (stanzaCorrente == 3){
            
            // Collisioni ostacoli stanza 3
            if (CheckCollisionRecs(pers, piscina) || CheckCollisionRecs(pers, parete) || 
                CheckCollisionRecs(pers, sinistra) || CheckCollisionRecs(pers, destra) || 
                CheckCollisionRecs(pers, sinistra2) || CheckCollisionRecs(pers, uovo) || 
                CheckCollisionRecs(pers, basso) || CheckCollisionRecs(pers, coppa)) {
                
                if (IsKeyDown(KEY_D)) pers.x -= speed;
                if (IsKeyDown(KEY_A)) pers.x += speed;
                if (IsKeyDown(KEY_S)) pers.y -= speed;
                if (IsKeyDown(KEY_W)) pers.y += speed;
            }

            // Zone di interazione ampliati per facilitare il rilevamento
            Rectangle zonaUovo = {uovo.x - 15, uovo.y - 15, uovo.width + 30, uovo.height + 30};
            Rectangle zonaPiscina = {piscina.x - 15, piscina.y - 15, piscina.width + 30, piscina.height + 30};

            // 1. Interazione Uovo
            if (CheckCollisionRecs(pers, zonaUovo) && IsKeyPressed(KEY_R) && !uovoControllato) {
                for (int i = 0; i < 6; i++) {
                    if (inventario[i] == 0) {
                        inventario[i] = 3; // Oggetto uovo
                        uovoControllato = true;
                        break;
                    }
                }
            }

            // 2. Interazione Piscina
            if (CheckCollisionRecs(pers, zonaPiscina) && IsKeyPressed(KEY_R) && !stanzaCompletata2) {
                int slotOggettoUovo = -1;
                for (int i = 0; i < 6; i++) {
                    if (inventario[i] == 3) {
                        slotOggettoUovo = i;
                        break;
                    }
                }

                if (slotOggettoUovo != -1) {
                    stanzaCompletata2 = true;
                    inventario[slotOggettoUovo] = 0;
                }
            }

            // 3. Avanzamento (Funziona sia con BACKSPACE che con SPAZIO)
            if (stanzaCompletata2 && (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_SPACE))) {
                stanzaCorrente = 4;
                pers.x = 50;
                pers.y = 200;
            }
        }
        
        // =====================================================================
        // 2. DISEGNO GRAFICO (DRAW)
        // =====================================================================
        BeginDrawing();
        ClearBackground(BLACK);

        if (stanzaCorrente == 0){
            Rectangle sorgente0 = { 0.0f, 0.0f, (float)schermata1.width, (float)schermata1.height };
            Rectangle destinazione0 = { 0.0, 0.0, 800.0, 450.0 }; 
            Vector2 origine0 = { 0.0, 0.0 };
            DrawTexturePro(schermata1, sorgente0, destinazione0, origine0, 0.0f, WHITE);

            DrawText("Click space to start", 280, 160, 20, GOLD);
        }

        else if (stanzaCorrente == 1) {
            Rectangle sorgente = { 0.0f, 0.0f, (float)sfondo.width, (float)sfondo.height };
            Rectangle destinazione = { 0.0, 0.0, 800.0, 450.0 }; 
            Vector2 origine = { 0.0, 0.0 };
            DrawTexturePro(sfondo, sorgente, destinazione, origine, 0.0f, WHITE);

            if (textureCorrente->width > 0 && textureCorrente->height > 0) {
                Rectangle sorgentePers = { 0.0f, 0.0f, (float)textureCorrente->width, (float)textureCorrente->height };
                Rectangle destinazionePers = { pers.x, pers.y, pers.width, pers.height };
                Vector2 originePers = { 0.0f, 0.0f };
                DrawTexturePro(*textureCorrente, sorgentePers, destinazionePers, originePers, 0.0f, WHITE);
            } else {
                DrawRectangleRec(pers, BLUE);
            }

            DrawRectangleLinesEx(pers, 2.0, RED);

            // Interfaccia Inventario
            DrawRectangleRec(inv, (Color){ 44, 34, 31, 255 });
            for (int i = 0; i < 6; i++) {
                float slot = 22.5 + (i * 30.0);
                DrawRectangleLines(slot, 402, 25, 25, GRAY);

                if (inventario[i] == 1) DrawRectangle(slot + 3, 405, 19.0, 19.0, RED);
                if (inventario[i] == 2) DrawRectangle(slot + 3, 405, 19.0, 19.0, GOLD);
            }

            if (stanzaCompletata) {
                DrawText("Room 1 completed!", 230, 180, 30, GOLD);
                DrawText("Click space to go on", 260, 220, 20, WHITE);
            }
        } 
        else if (stanzaCorrente == 2){
            Rectangle sorgente01 = { 0.0f, 0.0f, (float)schermata2.width, (float)schermata2.height };
            Rectangle destinazione01 = { 0.0, 0.0, 800.0, 450.0 }; 
            Vector2 origine01 = { 0.0, 0.0 };
            DrawTexturePro(schermata2, sorgente01, destinazione01, origine01, 0.0f, WHITE);

            DrawText("Welcome to Room 2", 250, 160, 30, WHITE);
        }
        else if (stanzaCorrente == 3) {
            // Sfondo Stanza 2
            Rectangle sorgente2 = { 0.0f, 0.0f, (float)sfondo2.width, (float)sfondo2.height };
            Rectangle destinazione2 = { 0.0, 0.0, 800.0, 450.0 }; 
            Vector2 origine2 = { 0.0, 0.0 };
            DrawTexturePro(sfondo2, sorgente2, destinazione2, origine2, 0.0f, WHITE);

            if (textureCorrente->width > 0 && textureCorrente->height > 0) {
                Rectangle sorgentePers = { 0.0f, 0.0f, (float)textureCorrente->width, (float)textureCorrente->height };
                Rectangle destinazionePers = { pers.x, pers.y, pers.width, pers.height };
                Vector2 originePers = { 0.0f, 0.0f };
                DrawTexturePro(*textureCorrente, sorgentePers, destinazionePers, originePers, 0.0f, WHITE);
            }
            
            DrawRectangleLinesEx(pers, 2.0, RED);


            // Inventario
            DrawRectangleRec(inv, (Color){ 44, 34, 31, 255 });
            for (int i = 0; i < 6; i++) {
                float slot = 22.5 + (i * 30.0);
                DrawRectangleLines(slot, 402, 25, 25, GRAY);
                if (inventario[i] == 2) DrawRectangle(slot + 3, 405, 19.0, 19.0, GOLD);
                if (inventario[i] == 3) DrawRectangle(slot + 3, 405, 19.0, 19.0, GREEN);
            }

            // Messaggio completamento stanza
            if (stanzaCompletata2) {
                DrawText("Room 2 completed!", 230, 180, 30, GOLD);
                DrawText("click space to go on", 270, 220, 20, WHITE);
            }
        }
        else if (stanzaCorrente == 4){
            Rectangle sorgente02 = { 0.0f, 0.0f, (float)schermata3.width, (float)schermata3.height };
            Rectangle destinazione02 = { 0.0, 0.0, 800.0, 450.0 }; 
            Vector2 origine02 = { 0.0, 0.0 };
            DrawTexturePro(schermata3, sorgente02, destinazione02, origine02, 0.0f, WHITE);

            DrawText("To be continued", 220, 160, 50, BLACK);
        }

        // Logo costante in basso a destra
        Rectangle sorgente = { 0.0f, 0.0f, (float)logo.width, (float)logo.height };
        Rectangle destinazione = {700.0f, 360.0f, 60.0f, 60.0f};
        DrawTexturePro(logo, sorgente, destinazione, (Vector2){0,0}, 0.0f, WHITE);
        
        EndDrawing();
    }

    // Deallocazione risorse
    UnloadTexture(logo);
    UnloadTexture(sfondo);
    UnloadTexture(sfondo2);
    UnloadTexture(schermata1);
    UnloadTexture(schermata2);
    UnloadTexture(schermata3);
    UnloadTexture(texFermo);
    UnloadTexture(texDestra);
    UnloadTexture(texDestra1);
    UnloadTexture(texDestra2);
    UnloadTexture(texSinistra);
    UnloadTexture(texSinistra1);
    UnloadTexture(texSinistra2);
    UnloadTexture(texSu);

    CloseWindow();
    return 0;
}