struct MOVIECHARACTER { unsigned char unknown_0x0[4]; int kind; }; /* readers: DrawMovieCharacter, func_00215850 (kind 4) */
extern "C" {
void DrawMovieBitmapCharacter(void *, void *, void *, void *);
void DrawMovieShapeCharacter(void *, void *, void *, void *);
void DrawMovieTextCharacter(void *, void *, void *, void *);

void DrawMovieCharacter(MOVIECHARACTER *character, void *matrix, void *cxform, void *context) {
    switch (character->kind) {
    case 3:
        DrawMovieTextCharacter(character, matrix, cxform, context);
        break;
    case 1:
        DrawMovieShapeCharacter(character, matrix, cxform, context);
        break;
    case 6:
    case 7:
        DrawMovieBitmapCharacter(character, matrix, cxform, context);
        break;
    case 8:
        break;
    }
}
}
