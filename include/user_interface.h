#ifndef USER_INTERFACE_H
    #define USER_INTERFACE_H

    #include "8ball.h"

    #define BOX_ITEM_BUTTON             1
    #define BOX_ITEM_DISPLAY            2
    #define BOX_ITEM_INPUT              3
    #define BOX_ITEM_ZONE               4


    #define UI_DATATYPE_UINT            0
    #define UI_DATATYPE_INT             1
    #define UI_DATATYPE_FLOAT           2
    #define UI_DATATYPE_DOUBLE          3

    #define UI_DATATYPE_POINTER         4
    #define UI_DATATYPE_CHAR            5
    #define UI_DATATYPE_UCHAR           6

    #define UI_DATATYPE_STRING          7


    #define UI_ITEMTYPE_EMPTY           0
    #define UI_ITEMTYPE_STRING          1
    #define UI_ITEMTYPE_SIMPLE_BUTTON   2
    #define UI_ITEMTYPE_PICTURE         3
    #define UI_ITEMTYPE_NUMERICCHOOSER  4

    #define BOX_CONTENT_EMPTY           0
    #define BOX_CONTENT_DISPLAY         1

    #define UI_EVENT_NONE                     0
    #define UI_EVENT_BOXKILL                  1
    #define UI_EVENT_BARGRAB                  2
    #define UI_EVENT_BOXRESIZE                3
    #define UI_EVENT_ITEMCLICK                4
    #define UI_EVENT_SCROLLBAR                5

    #define UI_UP_EDGE                        0
    #define UI_DOWN_EDGE                      1
    #define UI_LEFT_EDGE                      2
    #define UI_RIGHT_EDGE                     3
    #define UI_UPPER_LEFT_CORNER              4
    #define UI_UPPER_RIGHT_CORNER             5
    #define UI_LOWER_LEFT_CORNER              6
    #define UI_LOWER_RIGHT_CORNER             7

    #define UI_BOX_DEFAULT_TITLE 		"Empty Box"

    #define UI_ASSET_PATH               "rc/asset/button/"
    /*
    #define UI_BOX_COUNT                8
    #define UI_BOX_TITLE_STRLEN         32
    #define UI_BOX_CONTENT_MAX_ITEM     16
    */
    #define UI_BORDER_WIDTH             3

    #define UI_CURSOR_ARROW             0
    #define UI_CURSOR_CROSS             1
    #define UI_CURSOR_ARROW_VRT         2
    #define UI_CURSOR_ARROW_HRZ         3

    #define UI_CURSOR_CORNER_UL         4
    #define UI_CURSOR_CORNER_UR         5
    #define UI_CURSOR_CORNER_DL         6
    #define UI_CURSOR_CORNER_DR         7

    void                    ui_main(t_mega *mega, t_userInterface *ui);

    /*********************/
    #include "cursor.h"

    int             ui_initCursor(t_userInterface *ui);
    /*********************/

    uint 			ui_totalBox(t_userInterface *ui);
    /// DEFAULT ///
    struct s_box_item           set_default_box_item(void);
    t_box_content               *set_default_box_content(void);
    int                         set_default_box(t_ui_box *box);
    struct s_ui_assets          ui_setDefaultAssets(void);
    struct s_ui_scrollbar       ui_defaultScrollBar(uchar axis);

    int             ui_initAssets(t_userInterface *ui);


    /*** ScrollBar ***/
    struct s_ui_scrollbar       ui_newScrollBar(uchar axis);
    uint                        ui_getScrollBarLength(t_ui_box *box, uchar axis);
    void                        ui_getScrollButtonPos(t_ui_box *box, uchar axis, int *pos);
    void            ui_clampScrollBarFactor(t_ui_box *box);

    void            ui_releaseItem(t_box_item *item);
    void            ui_releaseBox(t_ui_box *box);
    void            ui_releaseAssets(t_ui_assets *assets);
    void                    ui_releaseFont(t_ui_font *ch);
    struct s_ui_font        ui_defaultFont(void);

    /// ENVDIM ///
    uint        ui_getBoxEnvWidth(t_ui_box *box);
    uint        ui_getBoxEnvHeight(t_userInterface *ui, t_ui_box *box);
    void        ui_getBoxEnvDim(t_userInterface *ui, t_ui_box *box);
    /** Height **/
    int             ui_getItemHeight_string(t_ui_box *box, t_box_item *item, int currentVerticalPos);
    int             ui_getItemHeight_simpleButton(t_box_item *item, int currentVerticalPos);
    int             ui_getItemHeight_numericChooser(t_box_item *item, int currentVerticalPos);

    /// CONTRUCTOR ///
    struct s_ui_font            ui_newFont(uchar *fg_color, uchar *bg_color, float fSz);
    struct s_ui_font            ui_newCharset(void);
    int                         ui_newBox(t_mega *mega, t_ui_box *box, uint index);
    struct s_box_item           ui_newItemText(t_mega *mega, t_ui_box *box, char *str, int *pos);
    struct s_box_item           ui_newItemSimpleButton(SDL_Surface *surf, const char *name, int (*fptr)(void *, int), int *pos, uint *dim);
    struct s_box_item           ui_newItemPicture(t_mega *mega, t_ui_box *box, SDL_Surface *picture, int *pos);
    struct s_box_item           ui_newItem_numericChooser(t_mega *mega, t_ui_box *box, uint digits, int *pos, void *data, float itemFactor, uchar datatype, struct s_ui_function ft);

    struct s_ui_event       ui_setDefaultEvent(void);
    struct s_ui_event       ui_setEvent(uchar type, uchar handle);

    uchar                       *ui_listActive(t_userInterface *ui, uchar printList);
    uchar                       *ui_listZindex(t_userInterface *ui, uchar printList, uchar *table);
    uchar                       ui_getFrontBoxHandle(t_userInterface *ui);
    int                         ui_getBoxHandle_byTitle(t_userInterface *ui, const char *boxTitle, uchar *handle);

    /// BOX DIMENSIONS ///
    void                        ui_setBoxSide(t_userInterface *ui, t_ui_box *box, uchar i, t_mouse *mouse);
    void                        ui_getBoxSide(t_ui_box *box, uchar i, uint *btnDim, int *btnPos);

    /// HANDLERS ///
    int                         ui_getBoxHandleAt(t_userInterface *ui, int *onClick, uchar *handle);
    int                         ui_getScrollBarHandle(t_ui_box *box, int *onClick);
    uchar                       ui_getItemHandleAt(t_userInterface *ui, t_ui_box *box, int *onClick, uchar *handle);
    int                         ui_isKill(t_ui_box *box, int *onClick);
    int                         ui_isGrabBar(t_ui_box *box, int *onClick);

    int                         ui_isResize(t_ui_box *box, int *onClick, uchar *sideGrab);
    /// BOX Z_INDEX ///
    void                        ui_foregroundAll(t_userInterface *ui, uchar handle);
    void                        ui_foreground(t_userInterface *ui, uchar handle, uchar active);
    void 			            ui_background(t_userInterface *ui, uchar handle, uchar active);

    /// DISPLAY ///
    int                         ui_displayItem_numericChooser(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item,
                                    uchar boxHandle, uint itemHandle, uint vrtOffset);
    int                         ui_displayItemPicture(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item, uchar boxHandle, uint itemHandle, uint vrtOffset);
    int                         ui_displayItemString(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item, uchar boxHandle, uint itemHandle, uint vrtOffset);
    int                         ui_displayItemButton(SDL_Surface *viewport, t_mega *mega, t_ui_box *box, t_box_item *item, uchar boxHandle, uint itemHandle, uint vrtOffset);
    void                    ui_displayItemScrollBar(SDL_Surface *viewport, t_userInterface *ui, t_ui_box *box);
    uint                    ui_displayItem(t_mega *mega, SDL_Surface *viewport, t_ui_box *box, t_box_item *item, uchar boxHandle, uchar itemHandle, uint vrtOffset);
    int                         ui_displayBox(t_mega *mega, SDL_Surface *viewport, uchar boxHandle);
    void 		            ui_displayCursorCaption(t_mega *mega, SDL_Surface *viewport);

    /// BOX FEATURES ///
    void                        ui_updateCursor(t_userInterface *ui, int *mousePos);
    void                        ui_swapBox(t_userInterface *ui, uchar handle, uchar active); /** Kill or Pop **/
    void                        ui_setPos(t_userInterface *ui, uchar handle, int *pos);
    void                        ui_setDim(t_userInterface *ui, uchar handle, uint *dim);

    /// EVENT onClick ///
    int             ui_eventBoxKill_onClick(t_mega *mega, uchar boxHandle);
    int             ui_eventBarGrab_onClick(t_mega *mega, uchar boxHandle);
    int             ui_eventScrollbar_onClick(t_mega *mega, uchar boxHandle, uchar scrollbarHandle);
    int             ui_eventBoxSide_onClick(t_mega *mega, uchar boxHandle, uchar sideGrab);
    int             ui_eventItem_onClick(t_mega *mega, t_ui_box *box, uchar boxHandle, uchar itemHandle, uchar itemType, int *onClick);
    void        ui_eventItem_string_onClick(t_mega *mega, t_ui_box *box, t_box_item *item, int *onClick);
    void        ui_eventItem_simpleButton_onClick(t_mega *mega, t_ui_box *box, uchar itemHandle, int *onClick);
    void        ui_eventItem_picture_onClick(void);
    void        ui_eventItem_numericChooser_onClick(t_mega *mega, t_ui_box *box, uchar itemHandle, int *onClick);

    /// EVENT motion ///
    void            ui_eventBoxKill_motion(t_mega *mega, t_userInterface *ui, t_ui_box *box, struct s_mouse mouse);
    void            ui_eventBarGrab_motion(t_userInterface *ui, t_ui_box *box,  int *mouseDrag);
    void            ui_eventScrollbar_motion(t_userInterface *ui, t_ui_box *box, struct s_mouse mouse);
    void            ui_eventBoxSide_motion(t_mega *mega, t_userInterface *ui, t_ui_box* box, struct s_mouse mouse);
    void            ui_eventItem_motion(t_mega *mega, t_userInterface *ui, t_ui_box *box, struct s_mouse mouse);
    void        ui_eventItem_string_motion(t_mega *mega, t_userInterface *ui, t_box_item *item, int *relClick);
    void        ui_eventItem_simpleButton_motion(void);
    void        ui_eventItem_picture_motion(void);
    /*void        ui_eventItem_numericChooser_motion(t_mega *mega, t_userInterface *ui, t_box_item *item, int *relClick);*/ // Old.
    void        ui_eventItem_numericChooser_motion(t_mega *mega, t_ui_box *box, t_box_item *item, int *mouseDrag);

    /// EVENT onRelease ///
    struct s_ui_event            ui_eventBoxKill_onRelease(t_mega *mega, t_ui_box *box);
    struct s_ui_event            ui_eventBarGrab_onRelease(t_mega *mega, t_ui_box *box);
    struct s_ui_event            ui_eventItem_onRelease(t_mega *mega, t_ui_box *box);
    struct s_ui_event            ui_eventBoxSide_onRelease(t_mega *mega, t_ui_box *box);
    struct s_ui_event            ui_eventScrollbar_onRelease(t_mega *mega, t_ui_box *box);
    struct s_ui_event            ui_eventItem_string_onRelease(t_mega *mega, t_ui_box *box, t_box_item *item, struct s_ui_event event, int *onClick);
    struct s_ui_event            ui_eventItem_simpleButton_onRelease(t_mega *mega, t_ui_box *box, t_box_item *item, int *onClick);
    struct s_ui_event            ui_eventItem_picture_onRelease(void);
    struct s_ui_event            ui_eventItem_numericChooser_onRelease(t_mega *mega, t_ui_box *box, t_box_item *item, int *onClick);

    /// EVENT MAIN ///
    int                          ui_interfaceOnClick(t_mega *mega, uchar handle, int *onClick);
    int                          ui_interfaceMotion(t_mega *mega, t_userInterface *ui, struct s_mouse mouse);
    struct s_ui_event            ui_interfaceOnRelease(t_mega *mega);

    /// DESTRUCTOR ///
    void            ui_releaseItem_string(t_box_item *item);
    void            ui_releaseItem_simpleButton(t_box_item *item);
    void            ui_releaseItem_picture(t_box_item *item);
    void            release_ui(t_userInterface *ui);

    /// DRAW ///
    void            ui_drawCameraOrientation(SDL_Surface *s, t_cam *c, int w, int h, SDL_Surface **tileset); /// ROGUE !
    void            ui_drawButton(SDL_Surface *s, t_ui_box *box, int *pos, uint *dim, uchar isPressed, uchar isItem, SDL_Surface *pic);
    void            ui_drawScrollBar(t_userInterface *ui, t_ui_box *box, struct s_ui_scrollbar sb, SDL_Surface *viewport);
    void            ui_drawBox(t_mega *mega, SDL_Surface *viewport, uchar boxHandle);
    void            ui_releaseItem_numericChooser(t_box_item *item);
    int             ui_stringGetPtrAt(t_mega *mega, t_userInterface *ui, t_box_item *item, int *relClick);


    int             ui_functionTest(void *pMega, int flag);
    int             ui_functionFall(void *pMega, int flag);
    int             ui_functionExportDXF(void *pMega, int flag);
    int             ui_functionExportOBJ(void *pMega, int flag);
    int             ui_functionImportOBJ(void *pMega, int flag);
    int             ui_functionBye(void *pMega, int flag);
    ///void            ui_functionInput(void *data, uchar datatype, struct s_ftData_zone zone);///int *pos, uint *dim, int *maxDim, int *minDim);
    void            ui_functionInput(void *data, uchar datatype, t_ftData_zone *zone, void *tabNext);
    int             ui_functionReleaseModel(void *pMega, int flg);

    /*************************PROCESSOR****************************/
    /*char            *valToStr(void *value, char *buf, uchar dataType); /// ITOA universal datatype
    void            addVal(void *pVar, void *val, uchar datatype, void (*ruleValue)(void *, void *, uchar));
    void            setVal(void *pVar, void *val, uchar datatype, void (*ruleValue)(void *, void *, uchar));
    */
    ///char            *valToStr(void *value, uchar dataType, char *buf); /** ITOA universal datatype **/
    void            valToStr(void *in, char *out, uchar dataType);
    void            strToVal(char *in, void *out, uchar dataType);
    void            addVal(char *pVar, uchar inputType, char *val, uchar valType, void (*ruleValue)(void *, void *, uchar));
    void            setVal(char *pVar, uchar inputType, char *val, uchar valType, void (*ruleValue)(void *, void *, uchar));
    #define TOTAL_DATATYPE_COUNT            4

    /// ;


    /// Filters
    #define TOTAL_FILTER_COUNT              6
    static void            (*filterTable[TOTAL_DATATYPE_COUNT][TOTAL_FILTER_COUNT])(void *, void *, uchar);
    void            *coreFilter(void *a, void *b, uchar datatype, uchar call);
    void            uintFilter_alfa(void *in, void *pmin, void *pmax);
    void            uintFilter_bravo(void *in, void *pmin, void *pmax);
    void            uintFilter_charlie(void *in, void *pmin, void *pmax);
    void            uintFilter_delta(void *in, void *pmin, void *pmax);
    void            uintFilter_echo(void *in, void *pmin, void *pmax);
    void            uintFilter_foxtrot(void *in, void *pmin, void *pmax);

    void            intFilter_alfa(void *in, void *pmin, void *pmax);
    void            intFilter_bravo(void *in, void *pmin, void *pmax);
    void            intFilter_charlie(void *in, void *pmin, void *pmax);
    void            intFilter_delta(void *in, void *pmin, void *pmax);
    void            intFilter_echo(void *in, void *pmin, void *pmax);
    void            intFilter_foxtrot(void *in, void *pmin, void *pmax);

    void            floatFilter_alfa(void *in, void *pmin, void *pmax);
    void            floatFilter_bravo(void *in, void *pmin, void *pmax);
    void            floatFilter_charlie(void *in, void *pmin, void *pmax);
    void            floatFilter_delta(void *in, void *pmin, void *pmax);
    void            floatFilter_echo(void *in, void *pmin, void *pmax);
    void            floatFilter_foxtrot(void *in, void *pmin, void *pmax);

    void            doubleFilter_alfa(void *in, void *pmin, void *pmax);
    void            doubleFilter_bravo(void *in, void *pmin, void *pmax);
    void            doubleFilter_charlie(void *in, void *pmin, void *pmax);
    void            doubleFilter_delta(void *in, void *pmin, void *pmax);
    void            doubleFilter_echo(void *in, void *pmin, void *pmax);
    void            doubleFilter_foxtrot(void *in, void *pmin, void *pmax);

    /// Instruction Set
    #define TOTAL_INSTRUCTION_COUNT     3
    static void            (*instructionTable[TOTAL_DATATYPE_COUNT][TOTAL_INSTRUCTION_COUNT])(void *, void *);
    void            coreInstruction(void *a, void *b, uchar datatype, uchar call);
    void            uint_add(void *in, void *out);
    void            uint_get(void *in, char *out);
    void            uint_copy(void *in, void *out);
    void            uint_set(char *in, void *out);
    void            int_add(void *in, void *out);
    void            int_get(void *in, char *out);
    void            int_copy(void *in, void *out);
    void            int_set(char *in, void *out);
    void            float_add(void *in, void *out);
    void            float_get(void *in, char *out);
    void            float_copy(void *in, void *out);
    void            float_set(char *in, void *out);
    void            double_add(void *in, void *out);
    void            double_get(void *in, char *out);
    void            double_copy(void *in, void *out);
    void            double_set(char *in, void *out);
    void            string_add(void *in, void *out);
    void            string_get(void *in, char *out);
    void            string_copy(void *in, void *out);
    void            string_set(char *in, void *out);
    /****************************PROCESSOR*************************/

    /****************************  SHELL  *************************/
    uint            strlento(char *str, char c);
    int             ui_ask_form(struct s_ftData_zone zone, const char *form, ...);
    /** int             ui_ask_call_form(struct s_ftData_zone zone, const char *form, ...); **/
    /****************************  SHELL  *************************/

    /** Misc. **/
    void            loading_bar(SDL_Surface *surface, float from_percent, float percent);

#endif // USER_INTERFACE_H
