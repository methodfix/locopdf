/***************************************************************************
 *   Copyright (C) 2008 by Marc Lajoie                                     *
 *   quickhand@openinkpot.org                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "dialogs.h"
#include "choicebox.h"
#include "entrybox.h"
#include "locopdf.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

Evas_Object *preferenceschoicebox,*zoomentrybox,*hpanentrybox,*vpanentrybox,*trimmingchoicebox,*lefttrimentrybox,*righttrimentrybox,*toptrimentrybox,*bottomtrimentrybox;
//hpan entrybox
void hpan_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_hpan_inc(((double)numval)/100.0);
        reset_cur_panning();
        update_label(e,preferenceschoicebox,0,value);
        free(value);
    }
}

void HPanEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    hpanentrybox=init_entrybox(e,"Hor. Panning Inc.",startval,3,hpan_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(hpanentrybox,&x,&y,&w,&h);
    evas_object_move(hpanentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
//vpan entrybox
void vpan_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_vpan_inc(((double)numval)/100.0);
        reset_cur_panning();
        update_label(e,preferenceschoicebox,1,value);
        free(value);
    }
}

void VPanEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    vpanentrybox=init_entrybox(e,"Ver. Panning Inc.",startval,3,vpan_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(vpanentrybox,&x,&y,&w,&h);
    evas_object_move(vpanentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
//zoom entry box
void zoom_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_zoom_inc(((double)numval)/100.0);
        update_label(e,preferenceschoicebox,3,value);
        free(value);
    }
}

void ZoomEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    zoomentrybox=init_entrybox(e,"Zoom Inc.",startval,3,zoom_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(zoomentrybox,&x,&y,&w,&h);
    evas_object_move(zoomentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}

//left trimming entrybox
void lefttrim_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_lefttrim((int)numval);
        update_label(e,trimmingchoicebox,0,value);
        free(value);
        render_cur_page();
        prerender_next_page();
    }
}

void LeftTrimEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    lefttrimentrybox=init_entrybox(e,"Left Trimming.",startval,3,lefttrim_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(lefttrimentrybox,&x,&y,&w,&h);
    evas_object_move(lefttrimentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
//right trimming entrybox
void righttrim_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_righttrim((int)numval);
        update_label(e,trimmingchoicebox,1,value);
        free(value);
        render_cur_page();
        prerender_next_page();
    }
}

void RightTrimEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    righttrimentrybox=init_entrybox(e,"Right Trimming.",startval,3,righttrim_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(righttrimentrybox,&x,&y,&w,&h);
    evas_object_move(righttrimentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
//top trimming entrybox
void toptrim_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_toptrim((int)numval);
        update_label(e,trimmingchoicebox,2,value);
        free(value);
        render_cur_page();
        prerender_next_page();
    }
}

void TopTrimEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    toptrimentrybox=init_entrybox(e,"Top Trimming.",startval,3,toptrim_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(toptrimentrybox,&x,&y,&w,&h);
    evas_object_move(toptrimentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
//bottom trimming entrybox
void bottomtrim_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        set_bottomtrim((int)numval);
        update_label(e,trimmingchoicebox,3,value);
        free(value);
        render_cur_page();
        prerender_next_page();
    }
}

void BottomTrimEntry(Evas *e, Evas_Object *obj,const char *startval)
{
    bottomtrimentrybox=init_entrybox(e,"Bottom Trimming.",startval,3,bottomtrim_entryhandler,obj);
    int x,y,w,h;
    evas_object_geometry_get(bottomtrimentrybox,&x,&y,&w,&h);
    evas_object_move(bottomtrimentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
// trimming choicebox

void trimming_choicehandler(Evas *e, Evas_Object *parent,int choice, bool lp)
{
    if(choice==0)
    {
        char *startval;
        asprintf(&startval,"%d",get_lefttrim());
        LeftTrimEntry(e,parent,startval);    
        free(startval);
        
    }
    else if(choice==1)
    {
        char *startval;
        asprintf(&startval,"%d",get_righttrim());
        RightTrimEntry(e,parent,startval);    
        free(startval);
        
    }
    else if(choice==2)
    {
        char *startval;
        asprintf(&startval,"%d",get_toptrim());
        TopTrimEntry(e,parent,startval);    
        free(startval);
        
    }
    else if(choice==3)
    {
        char *startval;
        asprintf(&startval,"%d",get_bottomtrim());
        BottomTrimEntry(e,parent,startval);    
        free(startval);
        
    }
}

void TrimmingDialog(Evas *e, Evas_Object *obj)
{
	const char *initchoices[] = { 		
		"1. Left Trimming",
		"2. Right Trimming",
		"3. Top Trimming",
		"4. Bottom Trimming",
	};

    char *lefttrim,*righttrim,*toptrim,*bottomtrim;
    asprintf(&lefttrim,"%d",get_lefttrim());
    asprintf(&righttrim,"%d",get_righttrim());
    asprintf(&toptrim,"%d",get_toptrim());
    asprintf(&bottomtrim,"%d",get_bottomtrim());
	const char *values[] = {
		lefttrim,	
		righttrim,
		toptrim,
		bottomtrim,
	};
    
	trimmingchoicebox=init_choicebox(e,initchoices, values, 4, trimming_choicehandler, "Settings",obj, true);
    
    int x,y,w,h;
    evas_object_geometry_get(trimmingchoicebox,&x,&y,&w,&h);
    evas_object_move(trimmingchoicebox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    free(lefttrim);
    free(righttrim);
    free(toptrim);
    free(bottomtrim);
}
// Options dialogs



void preferences_choicehandler(Evas *e, Evas_Object *parent,int choice, bool lp)
{
    if(choice==0)
    {
        char *startval;
        asprintf(&startval,"%d",(int)(get_hpan_inc()*100));
        HPanEntry(e,parent,startval);    
        free(startval);
    }
    else if(choice==1)
    {
        char *startval;
        asprintf(&startval,"%d",(int)(get_vpan_inc()*100));
        VPanEntry(e,parent,startval);    
        free(startval);
    }
    else if(choice==2)
    {
        TrimmingDialog(e,parent);    
    }
	else if(choice==3)
    {
        char *startval;
        asprintf(&startval,"%d",(int)(get_zoom_inc()*100));
        ZoomEntry(e,parent,startval);    
        free(startval);
    }
}

void PreferencesDialog(Evas *e, Evas_Object *obj)
{
	const char *initchoices[] = { 		
		"1. Hor. Panning",
		"2. Ver. Panning",
		"3. Trimming",
		"4. Zoom Increment",
	};

    char *zoom;
    asprintf(&zoom,"%d",(int)(get_zoom_inc()*100));
    char *hpan;
    asprintf(&hpan,"%d",(int)(get_hpan_inc()*100));
    char *vpan;
    asprintf(&vpan,"%d",(int)(get_vpan_inc()*100));
	const char *values[] = {
		hpan,	
		vpan,
		"",
		zoom,
	};
    
	preferenceschoicebox=init_choicebox(e,initchoices, values, 4, preferences_choicehandler, "Settings",obj, true);
    int x,y,w,h;
    evas_object_geometry_get(preferenceschoicebox,&x,&y,&w,&h);
    evas_object_move(preferenceschoicebox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
    free(zoom);
    free(hpan);
    free(vpan);
}


