/*
 *  Main header file for percolation code.
 */

/*
 *  System size L
 */


/*
 *  Although overall system is square, i.e. size L x L, we will define
 *  different variables for the first and second dimensions. This is
 *  because, in the parallel code, the local arrays will not be
 *  square. For example, using a simple 1D decomposition over P
 *  processes, then M = L/P and N = L
 */

#define ZERO_DIM 0
#define FIRST_DIM 1
#define MASTER 0
#define N_DIMS 2
#define PRINT_FREQ 100
#define SHALLOW_HALO 4

typedef struct
{
    /*start width boundary of process */
    int sW;
    /*end width boundary of process */
    int eW;
    /*start height boundary of process */
    int sH;
    /*end height boundary of process */
    int eH;

    int deltaH;
    int deltaW;

} bounds;


void rinit(int ijkl);
float uni(void);

