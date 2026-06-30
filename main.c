#include "raylib/src/raylib.h"

int main(void) {
    // per aprire la finestra (Larghezza, Altezza, Titolo)
    InitWindow(800, 450, "Test");

    // Ciclo di gioco vuoto
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(DARKGRAY); // Colore di sfondo
        //PRIMA STANZA 
            //banco al centro
            DrawRectangle(360, 210, 80, 30, BROWN);   
            //fila centrale 
            DrawRectangle(210, 210, 80, 30, BROWN);   
            DrawRectangle(510, 210, 80, 30, BROWN);   
            //fila in basso
            DrawRectangle(360, 290, 80, 30, BROWN);
            DrawRectangle(210, 290, 80, 30, BROWN);   
            DrawRectangle(510, 290, 80, 30, BROWN); 
            //fila in alto 
            DrawRectangle(360, 130, 80, 30, BROWN);
            DrawRectangle(210, 130, 80, 30, BROWN);   
            DrawRectangle(510, 130, 80, 30, BROWN); 
            //cattedra 
            DrawRectangle(340, 380, 120, 50, BROWN);

        EndDrawing();
    }

    // per chiudere la finestra
    CloseWindow();
    return 0;
}