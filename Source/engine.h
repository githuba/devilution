/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

//offset 0
//pCelBuff->pFrameTable[0]

//engine
extern int engine_cpp_init_value; // weak
extern char byte_52B96C; // automap pixel color 8-bit (palette entry)
extern int dword_52B970; // bool flip - if y < x
extern int orgseed; // weak
extern int sgnWidth;
extern int sglGameSeed; // weak
extern int SeedCount; // weak
extern int dword_52B99C; // bool valid - if x/y are in bounds

void __cdecl engine_cpp_init_1();
void __fastcall CelDrawDatOnly(char *pDecodeTo, char *pRLEBytes, int dwRLESize, int dwRLEWdt);
void __fastcall CelDecodeOnly(int screen_x, int screen_y, void *pCelBuff, int frame, int frame_width);
void __fastcall CelDecDatOnly(char *pBuff, char *pCelBuff, int frame, int frame_width);
void __fastcall CelDrawHdrOnly(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int always_0, int direction);
void __fastcall CelDecodeHdrOnly(char *pBuff, char *pCelBuff, int frame, int frame_width, int always_0, int direction);
void __fastcall CelDecDatLightOnly(char *pDecodeTo, char *pRLEBytes, int frame_content_size, int frame_width);
void __fastcall CelDecDatLightEntry(int a1, char *a2, char *a3, char *v6);
void __fastcall CelDecDatLightTrans(char *pDecodeTo, char *pRLEBytes, int frame_content_size, int frame_width);
void __fastcall CelDecodeLightOnly(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width);
void __fastcall CelDecodeHdrLightOnly(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int always_0, int direction);
void __fastcall CelDecodeHdrLightTrans(char *pBuff, char *pCelBuff, int frame, int frame_width, int always_0, int direction);
void __fastcall CelDrawHdrLightRed(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int always_0, int direction, char always_1);
void __fastcall Cel2DecDatOnly(char *pDecodeTo, char *pRLEBytes, int frame_content_size, int frame_width);
void __fastcall Cel2DrawHdrOnly(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int a6, int direction);
void __fastcall Cel2DecodeHdrOnly(char *pBuff, char *pCelBuff, int frame, int frame_width, int a5, int direction);
void __fastcall Cel2DecDatLightOnly(char *pDecodeTo, char *pRLEBytes, int frame_content_size, int frame_width);
void __fastcall Cel2DecDatLightEntry(int a1, int a2);
void __fastcall Cel2DecDatLightTrans(char *pDecodeTo, char *pRLEBytes, int frame_content_size, int frame_width);
void __fastcall Cel2DecodeHdrLight(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int a6, int direction);
void __fastcall Cel2DecodeLightTrans(char *dst_buf, char *pCelBuff, int frame, int frame_width, int a5, int direction);
void __fastcall Cel2DrawHdrLightRed(int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int always_0, int direction, char always_1);
void __fastcall CelDecodeRect(char *pBuff, int always_0, int dst_height, int dst_width, char *pCelBuff, int frame, int frame_width);
void __fastcall CelDecodeClr(char colour, int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int a7, int direction);
void __fastcall CelDrawHdrClrHL(char colour, int screen_x, int screen_y, char *pCelBuff, int frame, int frame_width, int a7, int direction);
void __fastcall ENG_set_pixel(int screen_x, int screen_y, char pixel);
void __fastcall engine_draw_pixel(int x, int y);
void __fastcall engine_draw_automap_pixels(int x1, int y1, int x2, int y2, char a5);
int __fastcall GetDirection(int x1, int y1, int x2, int y2);
void __fastcall SetRndSeed(int s);
int __cdecl GetRndSeed();
int __fastcall random(int idx, int v);
void __cdecl engine_cpp_init_2();
void __cdecl mem_init_mutex();
void __cdecl mem_atexit_mutex();
void __cdecl mem_free_mutex();
void *__fastcall DiabloAllocPtr(int dwBytes);
void __fastcall mem_free_dbg(void *ptr);
unsigned char *__fastcall LoadFileInMem(char *pszName, int *pdwFileLen);
void __fastcall LoadFileWithMem(char *pszName, void *buf);
void __fastcall Cl2ApplyTrans(char *p, char *ttbl, int last_frame);
void __fastcall Cl2DecodeFrm1(int x, int y, char *pCelBuff, int nCel, int width, int dir1, int dir2);
void __fastcall Cl2DecDatFrm1(char *buffer, char *frame_content, int a3, int width);
void __fastcall Cl2DecodeFrm2(char colour, int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a7, int a8);
void __fastcall Cl2DecDatFrm2(char *buffer, char *a2, int a3, int a4, char a5);
void __fastcall Cl2DecodeFrm3(int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a6, int a7, char a8);
void __fastcall Cl2DecDatLightTbl1(char *a1, char *a2, int a3, int a4, char *unused_lindex);
void __fastcall Cl2DecodeLightTbl(int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a6, int a7);
void __fastcall Cl2DecodeFrm4(int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a6, int a7);
void __fastcall Cl2DecDatFrm4(char *buffer, char *a2, int a3, int frame_width);
void __fastcall Cl2DecodeClrHL(char colour, int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a7, int a8);
void __fastcall Cl2DecDatClrHL(char *dst_buf, char *frame_content, int a3, int frame_width, char colour);
void __fastcall Cl2DecodeFrm5(int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a6, int a7, char a8);
void __fastcall Cl2DecDatLightTbl2(char *dst_buf, char *a2, int a3, int frame_width, char *a5);
void __fastcall Cl2DecodeFrm6(int screen_x, int screen_y, char *pCelBuff, int nCel, int frame_width, int a6, int a7);
void __fastcall PlayInGameMovie(char *pszMovie);

/* data */

extern int engine_inf; // weak
