#ifndef dwc
#define dwc

typedef struct
{
    const uint16_t InitTypestruct_elem1;
    const uint16_t InitTypestruct_elem2;
    
}InitType;

typedef struct
{
    InitType BoardTypestruct_elem1;
}BoardType;
enum { W = 0xffff, B = 0x0000};
static const BoardType cfg = {
    /* pbgc cfg */
    .BoardTypestruct_elem1 =
    {
        .InitTypestruct_elem1 = W,
        .InitTypestruct_elem2 = B

    } };