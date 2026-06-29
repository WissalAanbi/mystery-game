#include "raylib/src/raylib.h"

int main(void) {
    // Apri la finestra (Larghezza, Altezza, Titolo)
    InitWindow(800, 450, "Test");

    // Ciclo di gioco vuoto
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(DARKGRAY); // Colore di sfondo
        EndDrawing();
    }

    // Chiudi la finestra
    CloseWindow();
    return 0;
}