%module so2048

/* type maps */
%typemap(in) int{
    $1 = (int)PyLong_AsLong($input);    
    printf("an integer entered\n");
}


/* methods and variables export */
%{
    #define SWIG_FILE_WITH_INIT

    extern void initGame();
    extern int currentScore;
    extern int bestScore;
    extern int **  fields;

 %}

    void initGame();
    int currentScore;
    int bestScore;
    int fields;

