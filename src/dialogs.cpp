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

const char *FIT_STRINGS[] = { 		
		"Fit Width",
		"Fit Height",
		"Best Fit",
		"Stretch Fit",
        "No Fit",
	};
const char *OFF_ON_STRINGS[] = {
        "Off",
        "On",
    };
        
    
Evas_Object *preferenceschoicebox,*zoomentrybox,*hpanentrybox,*vpanentrybox,*trimmingchoicebox,*lefttrimentrybox,*righttrimentrybox,*toptrimentrybox,*bottomtrimentrybox,*fitmodechoicebox,*gotopageentrybox;
//hpan entrybox
void goto_page_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        int numval=(int)strtol(value,NULL,10);
        if(numval>0 && numval<=get_num_pages())
        {
            goto_page(numval-1);
        }
        free(value);
    }
}

void GotoPageEntry(Evas *e, Evas_Object *obj)
{
    char *tempstr;
    asprintf(&tempstr,"Page? (%d/%d)",get_cur_page()+1,get_num_pages());
    gotopageentrybox=init_entrybox(e,tempstr,"",4,goto_page_entryhandler,obj);
    free(tempstr);
    int x,y,w,h;
    evas_object_geometry_get(gotopageentrybox,&x,&y,&w,&h);
    evas_object_move(gotopageentrybox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
}
//hpan entrybox
void hpan_entryhandler(Evas *e, Evas_Object *obj,char *value)
{
    if(value)
    {
        long numval=strtol(value,NULL,10);
        if(numval>0 && numval<=100)
        {
            set_hpan_inc(((double)numval)/100.0);
            reset_cur_panning();
            char *tempo;
            asprintf(&tempo,"%s%%",value);
            update_label(e,preferenceschoicebox,0,tempo);
            free(tempo);
        }
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
        if(numval>0 && numval<=100)
        {
            set_vpan_inc(((double)numval)/100.0);
            reset_cur_panning();
            char *tempo;
            asprintf(&tempo,"%s%%",value);
            update_label(e,preferenceschoicebox,1,tempo);
            free(tempo);
        }
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
        if(numval>0 && numval<=100)
        {
            set_zoom_inc(((double)numval)/100.0);
            char *tempo;
            asprintf(&tempo,"%s%%",value);
            update_label(e,preferenceschoicebox,3,tempo);
            free(tempo);
        }
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
        char *tempo;
        asprintf(&tempo,"%spx",value);
        update_label(e,trimmingchoicebox,0,tempo);
        free(tempo);
        free(value);
        render_cur_page();
        prerender_next_page();
        update_statusbar();
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
        char *tempo;
        asprintf(&tempo,"%spx",value);
        update_label(e,trimmingchoicebox,1,tempo);
        free(tempo);
        free(value);
        render_cur_page();
        prerender_next_page();
        update_statusbar();
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
        char *tempo;
        asprintf(&tempo,"%spx",value);
        update_label(e,trimmingchoicebox,2,tempo);
        free(tempo);
        free(value);
        render_cur_page();
        prerender_next_page();
        update_statusbar();
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
        char *tempo;
        asprintf(&tempo,"%spx",value);
        update_label(e,trimmingchoicebox,3,tempo);
        free(tempo);
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
// fitmode choicebox

void fitmode_choicehandler(Evas *e, Evas_Object *parent,int choice, bool lp)
{
    if(get_fit_mode()!=choice)
    {
        set_fit_mode(choice);
        update_label(e,preferenceschoicebox,4,FIT_STRINGS[choice]);
        
        evas_object_focus_set(choicebox_get_parent(e,parent),1);
        fini_choicebox(e,parent,false);
        render_cur_page();
        prerender_next_page();
        update_statusbar();
    }
}

void FitModeDialog(Evas *e, Evas_Object *obj)
{
	const char *initchoices[] = { 		
		"1. Fit Width",
		"2. Fit Height",
		"3. Best Fit",
		"4. Stretch Fit",
        "5. No Fit",
	};

    
	const char *values[] = {
		"",	
		"",
		"",
		"",
        "",
	};
    
	fitmodechoicebox=init_choicebox(e,initchoices, values, 5, fitmode_choicehandler, "Fit Mode Settings",obj,NULL, true);
    
    int x,y,w,h;
    evas_object_geometry_get(fitmodechoicebox,&x,&y,&w,&h);
    evas_object_move(fitmodechoicebox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
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
    asprintf(&lefttrim,"%dpx",get_lefttrim());
    asprintf(&righttrim,"%dpx",get_righttrim());
    asprintf(&toptrim,"%dpx",get_toptrim());
    asprintf(&bottomtrim,"%dpx",get_bottomtrim());
	const char *values[] = {
		lefttrim,	
		righttrim,
		toptrim,
		bottomtrim,
	};
    
	trimmingchoicebox=init_choicebox(e,initchoices, values, 4, trimming_choicehandler, "Trimming Settings",obj, NULL,true);
    
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
    else if(choice==4)
    {
        FitModeDialog(e,parent);    
        
    }
    else if(choice==5)
    {
        set_antialias_mode(!get_antialias_mode());
        update_label(e,preferenceschoicebox,5,OFF_ON_STRINGS[get_antialias_mode()]);
        render_cur_page();
        prerender_next_page();
    }
    else if(choice==6)
    {
        set_reader_mode(!get_reader_mode());
        update_label(e,preferenceschoicebox,6,OFF_ON_STRINGS[get_reader_mode()]);
    }
    else if(choice==7)
    {
        set_statusbar_visible(!get_statusbar_visible());
        update_label(e,preferenceschoicebox,7,OFF_ON_STRINGS[get_statusbar_visible()]);
    }
}

void PreferencesDialog(Evas *e, Evas_Object *obj)
{
	const char *initchoices[] = { 		
		"1. Hor. Panning",
		"2. Ver. Panning",
		"3. Trimming",
		"4. Zoom Increment",
        "5. Fit Mode",
        "6. Antialias",
        "7. Reader Mode",
        "8. Status Bar",
	};
    
    
    

    char *zoom;
    asprintf(&zoom,"%d%%",(int)(get_zoom_inc()*100));
    char *hpan;
    asprintf(&hpan,"%d%%",(int)(get_hpan_inc()*100));
    char *vpan;
    asprintf(&vpan,"%d%%",(int)(get_vpan_inc()*100));
    
	const char *values[] = {
		hpan,	
		vpan,
		"",
		zoom,
        FIT_STRINGS[get_fit_mode()],
        OFF_ON_STRINGS[get_antialias_mode()],
        OFF_ON_STRINGS[get_reader_mode()],
        OFF_ON_STRINGS[get_statusbar_visible()],
	};
    
	preferenceschoicebox=init_choicebox(e,initchoices, values, 8, preferences_choicehandler, "LoCoPDF Settings",obj, NULL,true);
    int x,y,w,h;
    evas_object_geometry_get(preferenceschoicebox,&x,&y,&w,&h);
    evas_object_move(preferenceschoicebox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    
    free(zoom);
    free(hpan);
    free(vpan);
}
//TOC Choicebox
void TOCDialog(Evas *e, Evas_Object *obj,Ecore_List *list);
void toc_choicehandler(Evas *e, Evas_Object *parent,int choice, bool lp)
{
    Ecore_List *list=(Ecore_List *)choicebox_get_userdata(e,parent);
    Epdf_Index_Item *curitem=(Epdf_Index_Item *)ecore_list_index_goto(list,choice);
    Ecore_List *childlist=epdf_index_item_children_get (curitem);
    if(!childlist)
    {
        Evas_Object *curcb=parent;
        Evas_Object *nextcb;
        while((nextcb=choicebox_get_parent(e,curcb)))
        {
            fini_choicebox(e,curcb,false);   
            curcb=nextcb;
        }
        evas_object_focus_set(curcb,1);
        goto_page(epdf_index_item_page_get(get_document(),curitem));
    }
    else
    {
        TOCDialog(e,parent,childlist);    
        
    }
}
void TOCDialog(Evas *e, Evas_Object *obj,Ecore_List *list)
{
    int numchoices=ecore_list_count(list);
	char **initchoices;
    //char **values;
    initchoices=(char **)malloc(sizeof(char*)*numchoices);
    //values=(char **)malloc(sizeof(char*)*numchoices);
    ecore_list_first_goto(list);
    int i;
    for(i=0;i<numchoices;i++)
    {
        asprintf(&(initchoices[i]),"%d. %s",(i%8+1),epdf_index_item_title_get((Epdf_Index_Item *)ecore_list_next(list)));
        
    }
    
	Evas_Object *tocchoicebox=init_choicebox(e,(const char**)initchoices,NULL, numchoices, toc_choicehandler, "Table of Contents",obj,(void *)list, true);
    for(i=0;i<numchoices;i++)
    {

        free(initchoices[i]);
    }
    //free(values);
    free(initchoices);
    
    int x,y,w,h;
    evas_object_geometry_get(tocchoicebox,&x,&y,&w,&h);
    evas_object_move(tocchoicebox,(int)(((double)get_win_width()-w)/2.0),(int)(((double)get_win_height()-h)/2.0));
    

}


