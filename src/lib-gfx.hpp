#pragma once
#include <pspdisplay.h>
#include "font.hpp"

#define RGB5( r, g, b )	( ( ( b ) << 10 ) + ( ( g ) << 5 ) + ( ( r ) << 0 ) + 0x8000 )
#define R5( c )			( ( ( c ) >> 0 ) & 31 )
#define G5( c )			( ( ( c ) >> 5 ) & 31 )
#define B5( c )			( ( ( c ) >> 10 ) & 31 )

char *vramtop=(char *)0x44000000;

//-------------------------------------------------------------------------------------------------
char *GetVramAddr(unsigned long x,unsigned long y)
{
	return vramtop+x*2+y*512*2;
}
//-------------------------------------------------------------------------------------------------
void WaitVbl()
{
	sceDisplayWaitVblankStart();
}
//-------------------------------------------------------------------------------------------------
void InitScreen()
{
	sceDisplaySetMode(0,480,272);
	sceDisplaySetFrameBuf(vramtop,512,1,1);
}
//-------------------------------------------------------------------------------------------------
void ClearScreen(unsigned long color)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned long i;

	vptr0=(unsigned char*)GetVramAddr(0,0);
	for (i=0; i<0x44000/2; i++) {
		*(unsigned short *)vptr0=color;
		vptr0+=2;
	}
}
//-------------------------------------------------------------------------------------------------
void PutPixel(long x, long y, unsigned short color)
{
	unsigned char *vptr;		//pointer to vram
    
    if(x>479)
      x=480;
    if(x<0)
      x=-1;
    if(y<0)
      y=0;
      
	vptr=(unsigned char*)GetVramAddr(x,y);
	*(unsigned short *)vptr=color;
}
//-------------------------------------------------------------------------------------------------
inline u16	BlendRGB( u16 rgb1, u16 rgb2, u8 t )
{
	const s32	r1 = R5( rgb1 );
	const s32	g1 = G5( rgb1 );
	const s32	b1 = B5( rgb1 );
	const s32	r2 = R5( rgb2 );
	const s32	g2 = G5( rgb2 );
	const s32	b2 = B5( rgb2 );

	const s32	rd = ( r2 - r1 ) * t;
	const s32	gd = ( g2 - g1 ) * t;
	const s32	bd = ( b2 - b1 ) * t;

	const s32	r = r1 + ( rd >> 8 );
	const s32	g = g1 + ( gd >> 8 );
	const s32	b = b1 + ( bd >> 8 );

	return RGB5( r, g, b );
}
//-------------------------------------------------------------------------------------------------
void PutGfxNoFade(unsigned long x,unsigned long y,unsigned long w,unsigned long h,const unsigned short *d, int centerx, int centery)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	unsigned long xx,yy;
	const unsigned short *dd;
	
	
	if(centerx!=0){
		x=240-(w/2);
	}


	if(centery!=0){
		y=136-(h/2);
	}
	
	vptr0=(unsigned char*)GetVramAddr(x,y);
	for (yy=0; yy<h; yy++) {
		vptr=vptr0;
		dd=d;
		for (xx=0; xx<w; xx++) {
			*(unsigned short *)vptr=*dd;
			vptr+=2;
			dd++;
		}
		vptr0+=512*2;
		d+=w;
	}
	
}
//-------------------------------------------------------------------------------------------------
void PutGfx(unsigned long x,unsigned long y,unsigned long w,unsigned long h,const unsigned short *d, int centerx, int centery, unsigned fadefrom, int fadevalue)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	unsigned long xx,yy;
	const unsigned short *dd;
	
	
	if(centerx!=0){
		x=240-(w/2);
	}


	if(centery!=0){
		y=136-(h/2);
	}
	
	vptr0=(unsigned char*)GetVramAddr(x,y);
	for (yy=0; yy<h; yy++) {
		vptr=vptr0;
		dd=d;
		for (xx=0; xx<w; xx++) {
			*(unsigned short *)vptr=BlendRGB(fadefrom,*dd,fadevalue);
			vptr+=2;
			dd++;
		}
		vptr0+=512*2;
		d+=w;
	}
	
}
//-------------------------------------------------------------------------------------------------
void PutGfxTrans(unsigned long transcol, unsigned long x,unsigned long y,unsigned long w,unsigned long h,const unsigned short *d, int centerx, int centery, unsigned fadefrom, int fadevalue)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	unsigned long xx,yy;
	const unsigned short *dd;
	
	
	if(centerx!=0){
		x=240-(w/2);
	}


	if(centery!=0){
		y=136-(h/2);
	}
	
	vptr0=(unsigned char*)GetVramAddr(x,y);
	for (yy=0; yy<h; yy++) {
		vptr=vptr0;
		dd=d;
		for (xx=0; xx<w; xx++) {
			if(*dd!= transcol){
				*(unsigned short *)vptr=BlendRGB(fadefrom,*dd,fadevalue);
			}
			vptr+=2;
			dd++;
		}
		vptr0+=512*2;
		d+=w;
	}
	
}
//-------------------------------------------------------------------------------------------------
void PutSprite(unsigned long x,unsigned long y,unsigned long w,unsigned long h,unsigned long numspr,const unsigned short *d)
{
 unsigned long xx,yy,index;
 const unsigned short *dd;
    
    
    
	dd=d;
	dd=dd+w*h*numspr;
	for(xx=0;xx<w;xx++){
	      for(yy=0;yy<h;yy++){
	        PutPixel(x+xx,y+yy,*dd);
            dd++;
          } 
     }
}
//-------------------------------------------------------------------------------------------------
void PutSpriteTrans(unsigned long transcol,unsigned long x,unsigned long y,unsigned long w,unsigned long h,unsigned long numspr,const unsigned short *d)
{
 unsigned long xx,yy,index;
 const unsigned short *dd;
    
    
    
	dd=d;
	dd=dd+w*h*numspr;
	for(xx=0;xx<w;xx++){
	      for(yy=0;yy<h;yy++){
	        if(*dd!=transcol){
               PutPixel(x+xx,y+yy,*dd);
            }
			dd++;
          } 
     }
}
//-------------------------------------------------------------------------------------------------
void Putbg(unsigned long x,unsigned long y,unsigned long w,unsigned long h,unsigned long mag,const unsigned short *d)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	unsigned long xx,yy,mx,my;
	const unsigned short *dd;
	
	vptr0=(unsigned char*)GetVramAddr(x,y);
	for (yy=0; yy<h; yy++) {
		for (my=0; my<mag; my++) {
			vptr=vptr0;
			dd=d;
			for (xx=0; xx<w; xx++) {
				for (mx=0; mx<mag; mx++) {
					*(unsigned short *)vptr=*dd;
					vptr+=2;
				}
				dd++;
			}
			vptr0+=512*2;
		}
		d+=480;
	}
	
}
//-------------------------------------------------------------------------------------------------
void Rectangle(unsigned long x,unsigned long y,unsigned long w,unsigned long h,unsigned long col)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	unsigned long xx,yy;
	
	vptr0=(unsigned char *)GetVramAddr(x,y);
	for (yy=0; yy<h; yy++) {
		vptr=vptr0;
		for (xx=0; xx<w; xx++) {
			*(unsigned short *)vptr=col;
			vptr+=2;
		}
		vptr0+=512*2;
	}
	
}
//-------------------------------------------------------------------------------------------------
void PauseVbl(unsigned int tempo){
	unsigned int i;

	for(i=0;i<=tempo;i++){
		sceDisplayWaitVblankStart();
    }
}
//**-------------------
void pgPutChar(unsigned long x,unsigned long y,unsigned long color,unsigned long bgcolor,unsigned char ch,char drawfg,char drawbg,char mag,unsigned fadefrom, int fadevalue)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	const unsigned char *cfont;		//pointer to font
	unsigned long cx,cy;
	unsigned long b;
	char mx,my;

	if (ch>255) return;
	cfont=font+ch*8;
	vptr0=(unsigned char *)GetVramAddr(x,y);
	for (cy=0; cy<8; cy++) {
		for (my=0; my<mag; my++) {
			vptr=vptr0;
			b=0x80;
			for (cx=0; cx<8; cx++) {
				for (mx=0; mx<mag; mx++) {
					if ((*cfont&b)!=0) {
						if (drawfg) *(unsigned short *)vptr=BlendRGB(fadefrom,color,fadevalue);
					} else {
						if (drawbg) *(unsigned short *)vptr=BlendRGB(fadefrom,bgcolor,fadevalue);
					}
					vptr+=1*2;
				}
				b=b>>1;
			}
			vptr0+=512*2;
		}
		cfont++;
	}
}
void pgPrint(unsigned long x,unsigned long y,unsigned long color,const char *str,unsigned fadefrom, int fadevalue)
{
	while (*str!=0 && x<60 && y<38) {
		pgPutChar(x*8,y*8,color,0,*str,1,0,1,fadefrom,fadevalue);
		str++;
		x++;
		if (x>=60) {
			x=0;
			y++;
		}
	}
}

