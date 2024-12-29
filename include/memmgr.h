#ifndef MEMMGR_H
#define MEMMGR_H

    #include "8ball.h"

    /* High-Level allocation USE THIS FUNCTION */
    #define ALLOC(sz) \
        (my_malloc(sz))

    /* Retrieve core method */
    #define CORE_ACCESSION(x) \
        ((t_memPage **)(&core_memory_pointer))

    /* High-Level de-allocation USE THIS FUNCTION */
    #define FREE(ptr) \
        (my_free(ptr))

    /*******************************************/

    /* Low-Level allocation */
    #define PAGE_ALLOC(sInfo) \
        ((t_memPage *)malloc(sizeof(struct s_memPage) + \
                             (sInfo.szCell * sInfo.sz)))
    #define PAGE_FREE(src) \
        (free(src))

    #define CELL_ALLOC(sz) \
        ((t_memHeader *)malloc(sizeof(struct s_memHeader) + sz))

    #define CELL_FREE(src) \
        (free(src))

    typedef struct s_memHeader
    {
        int         cellType; /** 0 by default **/
        void        *srcCell; /** t_memCell **/
        size_t      sz; /** Record Length **/
    }              t_memHeader;

    typedef struct s_memCell
    {
        t_memHeader     *ptr;
        uint            lid;
    }               t_memCell;

    typedef struct s_memPointer
    {
        struct s_memPage     *next;
        struct s_memPage     *prev;
    }              t_memPointer;

    typedef struct s_memPageDim
    {
        size_t      sz;
        size_t      szCell;
        uint        pitch;
    }              t_memPageDim;

    typedef struct s_memDatatype
    {
        uint        datatype;  /// cells data type
        double      identy[4]; /// mem_getPointer use these matrices.
        double      transf[4];
    }              t_memDatatype;

    typedef struct s_memPage
    {
        struct s_memPointer     chain; /** Must be the first structure **/
        struct s_memPageDim     info;
        struct s_memDatatype    def;
        uchar                   isFull;
    }              t_memPage;

    t_memPage       *mem_getRoot(void);
    struct s_memPageDim          default_page_dim(void);

    void            page_set_empty_cells(t_memPage *page);
    t_memPage       *mem_getRoot(void);
    t_memPage       *mem_newPage(struct s_memPageDim dim);
    void            mem_removePage(t_memPage *page);
    void            mem_cleanPage(t_memPage *page); /** For cell type = 0 **/
    void            mem_releasePage(t_memPage *page);
    void            *mem_setCell(t_memPage *page, t_memCell *cell, size_t sz);
    void            *mem_setCell_force(t_memPage *page, t_memCell *cell, size_t sz);

    t_memPage        *page_getAvailable(t_memPage **prev, uint datatype);

    t_memCell       *mem_getEmptyCell(t_memPage *page);
    t_memCell       *mem_getPageCell(t_memPage *page);
    t_memPage       *mem_getCellPage(t_memCell *cell);
    t_memCell       *mem_getDataCell(void *ptr);

    uint            mem_pageCount(t_memPage *root);
    void            my_free(void *ptr);
    void            *my_malloc(size_t sz);
    int             memMgr_init(void);
    int             memMgr_release(void);

    //#ifndef GLOBAL_MEM_POINTER
    // #define GLOBAL_MEM_POINTER
    static t_memPage       *core_memory_pointer;
    //#endif // GLOBAL_MEM_POINTER

    void     		mem_cellDisplay(t_memCell *cell);
    void     		mem_pageDisplay(t_memPage *page);
    void     		mem_display(void);

#endif // MEMMGR_H
