/*********************************************************************
 * 
 *  Main file for modplayer sample for PSP
 *  adresd 2005
 */
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdlib.h>
#include <string.h>
#include <pspiofilemgr_fcntl.h>
#include <pspctrl.h>
#include <pspaudio.h>
#include <pspaudiolib.h>

#include "modplayer.h"
#include "modplayeri.h"

#include "lib-gfx.c"

#include "homebutton.c"

#include "rire.c"
#include "fucktro_logo.c"
#include "ps2nfo_tcb.c"
#include "boxe.c"
#include "boxe_ressort.c"
#include "xecuter.c"
#include "robot.c"
#include "affiche.c"
#include "wab_union.c"

#include "mongolia.c"
#include "level.c"
#include "levelmask.c"
#include "weareback.c"

#include "font8x8.c"
#include "scrolltxtintro.c"
#include "sinscrintro.c"

#include "perso.c"
#include "wearesin.c"


#define printf	pspDebugScreenPrintf
PSP_MODULE_INFO("SDKTEST", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);


void fadetxt(int nb,const char *str){
	long fade;
	
	for(fade=0;fade<=255;fade+=4){
		WaitVbl();
		pgPrint(((480-(8*nb))/2)/8,((272-8)/2)/8,0xffff,str,0,fade);
	}
	PauseVbl(60);
	for(fade=255;fade>=0;fade-=4){
		WaitVbl();
		pgPrint(((480-(8*nb))/2)/8,((272-8)/2)/8,0xffff,str,0,fade);
	}
} 


int main(int argc,char *argv[])
{
	int go=1;
	long fade,i;
	float xx,robotspr=0;
	long level_pos=544;
	long sprx=50,spry=104;
	float spr=0;
	unsigned long ofsetspr=0,was=0;
	unsigned long trux1=0,shit1=0,trux2=0,x,y=0;
	unsigned long sinscr=0,sinscrold=0;
	unsigned long j;
	unsigned long scrptr=0;
	ctrl_data_t pad;

	SetupCallbacks();
	
	pspAudioInit();
	ModPlay_Init(0,rire);
	
	InitScreen();
	ClearScreen(0);
	
    fadetxt(30,"Welcome to this little fucktro");
	fadetxt(25,"quicky coded by alonetrio");
	fadetxt(27,"Graph by Kernet-pdx and TLB");
	fadetxt(22,"for ps2nfo and xecuter");
	fadetxt(36,"ps2nfo : plz stop say shit to reuter");
	
	for(fade=0;fade<=255;fade+=4){
		WaitVbl();
		PutGfx(0,10,fucktro_logo_width,fucktro_logo_high,fucktro_logo_img,1,0,0,fade);
	}

	for(fade=0;fade<=255;fade+=2){
		WaitVbl();
		PutGfx(150,0,ps2nfo_tcb_width,ps2nfo_tcb_high,ps2nfo_tcb_img,0,1,0,fade);
	}
	
	PauseVbl(1);
	
	for(fade=0;fade<=255;fade+=2){
		WaitVbl();
		PutGfx(479-boxe_width,0,boxe_width,boxe_high,boxe_img,0,1,0,fade);
	}
	
	for(i=479-boxe_width;i>=(479/2)-(boxe_width/2)-30;i-=16){
		WaitVbl();
		Rectangle(i+32,136-(boxe_high/2),boxe_width-16,boxe_high,0x0000);
		PutGfxTrans(0x8000,i,0,boxe_width,boxe_high,boxe_img,0,1,0,255);
		PutGfx(i+boxe_width,0,boxe_ressort_width,boxe_ressort_high,boxe_ressort_img,0,1,0,255);
	}
	
	ModPlay_Play();

    PauseVbl(60*7);    
    ModPlay_Stop();
    PauseVbl(60*3);    
    ClearScreen(0);
    
    fadetxt(27,"The second little fx is for");
    fadetxt(12,"TEAM Xecuter");
    
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high,xecuter_char_width,xecuter_char_high,0,xecuter_sprite);
    
    for(xx=-42;xx<=((479/2)-(xecuter_char_width/2)-40);xx+=0.008){
		WaitVbl;
		PutSprite(xx,272-robot_char_high,robot_char_width,robot_char_high,robotspr,robot_sprite);
		robotspr+=0.008;
		if(robotspr>7)
			robotspr=0;
    }
    
    for(i=8;i<=27;i++){
		PauseVbl(5); 
		PutSprite(((479/2)-(xecuter_char_width/2)-40),272-robot_char_high,robot_char_width,robot_char_high,i,robot_sprite);   
    }
    
    for(i=37;i>=28;i--){
		PauseVbl(5);    
		PutSprite(((479/2)-(xecuter_char_width/2)-40),272-robot_char_high,robot_char_width,robot_char_high,i,robot_sprite);
    }
    
    for(i=0;i<=2;i++){
		PauseVbl(5);    
		PutSprite(((479/2)-(xecuter_char_width/2)-40),272-robot_char_high,robot_char_width,robot_char_high,38,robot_sprite);
		PauseVbl(5);    
		PutSprite(((479/2)-(xecuter_char_width/2)-40),272-robot_char_high,robot_char_width,robot_char_high,28,robot_sprite);
    }
    
    for(i=0;i<=14;i++){
		PauseVbl(2);    
		PutSprite((479-affiche_char_width),272-affiche_char_high-15,affiche_char_width,affiche_char_high,i,affiche_sprite);
    }
    
    for(i=0;i<=2;i++){
		PauseVbl(5);    
		PutSprite(((479/2)-(xecuter_char_width/2)-40),272-robot_char_high,robot_char_width,robot_char_high,38,robot_sprite);
		PauseVbl(5);    
		PutSprite(((479/2)-(xecuter_char_width/2)-40),272-robot_char_high,robot_char_width,robot_char_high,28,robot_sprite);
    }
    
    for(fade=0;fade<=255;fade+=2){
		WaitVbl();
		PutGfx(0,0,wab_union_width,wab_union_high,wab_union_img,1,0,0,fade);
	}
	
	WaitVbl();
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+1,xecuter_char_width,xecuter_char_high,1,xecuter_sprite);
	PutGfx(0,1,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+1,xecuter_char_width,xecuter_char_high,2,xecuter_sprite);
	PutGfx(0,1,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+3,xecuter_char_width,xecuter_char_high,3,xecuter_sprite);
    PutGfx(0,3,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+5,xecuter_char_width,xecuter_char_high,4,xecuter_sprite);
	PutGfx(0,5,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+7,xecuter_char_width,xecuter_char_high,5,xecuter_sprite);
	PutGfx(0,7,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+9,xecuter_char_width,xecuter_char_high,6,xecuter_sprite);
	PutGfx(0,9,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+11,xecuter_char_width,xecuter_char_high,7,xecuter_sprite);
	PutGfx(0,11,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+13,xecuter_char_width,xecuter_char_high,8,xecuter_sprite);
	PutGfx(0,13,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+15,xecuter_char_width,xecuter_char_high,9,xecuter_sprite);
	PutGfx(0,15,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(3); 
	PutSprite((479/2)-(xecuter_char_width/2),272-xecuter_char_high+17,xecuter_char_width,xecuter_char_high,10,xecuter_sprite);
	PutGfx(0,17,wab_union_width,wab_union_high,wab_union_img,1,0,0,255);
	PauseVbl(60*3);
	
	ClearScreen(0);
	fadetxt(30,"and now, here is the last part"); 
	fadetxt(28,"wab will release a demo soon"); 
    fadetxt(33,"and here is the main menu preview"); 
    fadetxt(28,"remember you can participate"); 
    fadetxt(24,"by sending your intro to"); 
    fadetxt(24,"alonetrio at wab dot com");
    fadetxt(8,"let's go");
    
    ModPlay_Init(0,mongolia);
    ClearScreen(0);
    sceDisplaySetFrameBuf(vramtop+level_pos*2*512,512,1,1);

	PutGfxNoFade(0,0,480,816,level_img,0,0);
	PutSpriteTrans(0x8000,sprx,level_pos+spry,32,32,0,perso_img);		
		
	ModPlay_Play();
    
	while(go){
		WaitVbl();
		Putbg(sprx,level_pos+spry,32,32,1,level_img+sprx+(level_pos+spry)*480);
		
		Putbg(152+16*0,level_pos+SinTab1[was+0],16,14,1,level_img+152+16*0+(level_pos+SinTab1[was+0])*480);
		Putbg(152+16*1,level_pos+SinTab1[was+5],16,14,1,level_img+152+16*1+(level_pos+SinTab1[was+5])*480);
		Putbg(152+16*3,level_pos+SinTab1[was+10],16,14,1,level_img+152+16*3+(level_pos+SinTab1[was+10])*480);
		Putbg(152+16*4,level_pos+SinTab1[was+15],16,14,1,level_img+152+16*4+(level_pos+SinTab1[was+15])*480);
		Putbg(152+16*5,level_pos+SinTab1[was+20],16,14,1,level_img+152+16*5+(level_pos+SinTab1[was+20])*480);
		Putbg(152+16*7,level_pos+SinTab1[was+25],16,14,1,level_img+152+16*7+(level_pos+SinTab1[was+25])*480);
		Putbg(152+16*8,level_pos+SinTab1[was+30],16,14,1,level_img+152+16*8+(level_pos+SinTab1[was+30])*480);
		Putbg(152+16*9,level_pos+SinTab1[was+35],16,14,1,level_img+152+16*9+(level_pos+SinTab1[was+35])*480);
		Putbg(152+16*10,level_pos+SinTab1[was+40],16,14,1,level_img+152+16*10+(level_pos+SinTab1[was+40])*480);
		
		Putbg(0,level_pos+251,480,20,1,level_img+(level_pos+251)*480);
		
	    sceCtrlReadBufferPositive(&pad, 1);
    
		if(pad.buttons & CTRL_RIGHT)
		{
			ofsetspr=1;
		    spr=spr+0.2f;
		    if(spr>7.0f) spr=1.0f;
			sprx+=1;
			if(sprx>448) sprx=448;
      	}
      	
      	if(pad.buttons==CTRL_LEFT){
			ofsetspr=8;
			spr=spr+0.2f;
			if(spr>7.0f) spr=1.0f;
			sprx-=1;
			if(sprx<0) sprx=0;
		}


		if(pad.buttons==CTRL_UP){
		if((levelmask_img[(int)sprx+(level_pos+spry)*480+32*480+16]) != 0xffff){
			ofsetspr=16;
			spr=spr+0.2f;
			if(spr>7.0f) spr=1.0f;
			level_pos--;
			if(level_pos<0) level_pos=0;
		}
		}

		if(pad.buttons==CTRL_DOWN){
		  if((levelmask_img[(int)sprx+(level_pos+spry)*480+33*480+16]) != 0xffff){
			ofsetspr=16;
			spr=spr+0.2f;
			if(spr>7.0f) spr=1.0f;
			level_pos++;
			if(level_pos>544) level_pos=544;
		  }
		  else{
		     spr=0;
		     ofsetspr=0;	
		  }
		}
		
		if(pad.buttons==0){
			spr=0;
			ofsetspr=0;	
			if((levelmask_img[(int)sprx+(level_pos+spry)*480+33*480+16]) != 0xffff){
				spr=0;
				ofsetspr=15;		
			}
		}
		
		if((levelmask_img[(int)sprx+(level_pos+spry)*480+32*480+16]) == 0xffff){
		 level_pos+=1;
		 spr=0;
		 ofsetspr=23;
		}
		
		sceDisplaySetFrameBuf(vramtop+level_pos*2*512,512,1,1);
		
		PutSpriteTrans(0x8000,sprx,level_pos+spry,32,32,spr+ofsetspr,perso_img);
		
	    was++;
	    if(was==150) was=0;

		PutSpriteTrans(0x8000,152+16*0,level_pos+SinTab1[was+0],16,14,0,weareback_img);  //W
	    PutSprite(152+16*1,level_pos+SinTab1[was+5],16,14,1,weareback_img);  //E
	    
	    PutSpriteTrans(0x8000,152+16*3,level_pos+SinTab1[was+10],16,14,3,weareback_img);  //A
	    PutSpriteTrans(0x8000,152+16*4,level_pos+SinTab1[was+15],16,14,4,weareback_img);  //R
	    PutSpriteTrans(0x8000,152+16*5,level_pos+SinTab1[was+20],16,14,5,weareback_img);  //E
	    
	    PutSpriteTrans(0x8000,152+16*7,level_pos+SinTab1[was+25],16,14,7,weareback_img);  //B
	    PutSpriteTrans(0x8000,152+16*8,level_pos+SinTab1[was+30],16,14,8,weareback_img);  //A
	    PutSpriteTrans(0x8000,152+16*9,level_pos+SinTab1[was+35],16,14,9,weareback_img);  //C
	    PutSpriteTrans(0x8000,152+16*10,level_pos+SinTab1[was+40],16,14,10,weareback_img);//K
	    
	    //---------------------------- Scroll ------------------------------
	   sinscr=sinscrold;
       i=0-trux1;
       for(j=1;j<=61;j++){
	    scrptr=scrolltxtintro_txt[shit1+j];
	    for(x=0;x<font8x8_char_width;x++){
	      for(y=0;y<font8x8_char_high;y++){
	        if(font8x8_font[scrptr]==0) trux2=0;
	        else{
	          trux2=0x1fb;

	        }
	        if(trux2!=0){
	        PutPixel(i,level_pos+y+SinTabscr[sinscr],trux2);
	        }
			scrptr++;
          } 
          i=i+1;
          
        }
        sinscr++;
       }
     trux1+=1;
     if(trux1>=font8x8_char_width){
       trux1=0;
       shit1++;
       if(shit1>scrolltxtintro_lenght-60){
         shit1=0;
       }
      }
	  sinscrold++;
	if(	sinscrold==60) sinscrold=0;  
	    
      	
      	
	}
    

    return 0;
}
