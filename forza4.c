/*********************************************************************************************************************
/	Autore: 	Carlo Ramponi
/	Data: 		26/11/2015
/	Consegna:	Gioco Forza 4
*********************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <gtk/gtk.h>

GtkWidget *table;
GtkWidget *window;
GtkWidget *dialog;
int mat[6][7];
int g=2,win=0;



static gboolean delete_event(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	return FALSE;
}

static void bottone(GtkWidget *widget, gpointer data)
{
	int i=(int)data;
	gtk_widget_destroy(table);
	crea_finestra(i);
}

static void riavvia(void)
{
	int i,j;
	g=2;
	win=0;
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
			mat[i][j]=0;
	}
	gtk_widget_destroy(table);
	crea_finestra(8);
}

static void bottone_dialogo(GtkWidget *widget, gchar* data)
{
	if(strcmp(data,"esci")==0)
	{
		delete_event(NULL,NULL,NULL);
	}
	if(strcmp(data,"rigioca")==0)
	{
		gtk_widget_destroy(dialog);
		riavvia();
	}
}

void controlla_vincitore()
{
	int i,j,v;
	for(v=1;v<=2;v++)
	{
		for(i=0;i<7;i++)
		{
			for(j=0;j<3;j++)
			{
				if(mat[j][i]==v && mat[j+1][i]==v && mat[j+2][i]==v && mat[j+3][i]==v)
					win=v;
			}
			for(j=0;j<4;j++)
			{
				if(i>=6)
					continue;
				if(mat[i][j]==v && mat[i][j+1]==v && mat[i][j+2]==v && mat[i][j+3]==v)
					win=v;
			}
			for(j=0;j<4;j++)
			{
				if(i>=6||i<3)
					continue;
				if(mat[i][j]==v && mat[i-1][j+1]==v && mat[i-2][j+2]==v && mat[i-3][j+3]==v)
					win=v;
			}
			for(j=0;j<4;j++)
			{
				if(i>=3)
					continue;
				if(mat[i][j]==v && mat[i+1][j+1]==v && mat[i+2][j+2]==v && mat[i+3][j+3]==v)
					win=v;
			}
		}
	}
}

void vincita()
{
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *table;
	dialog=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(dialog),"VITTORIA");
	g_signal_connect(dialog,"delete-event",G_CALLBACK(delete_event),NULL);
	gtk_window_set_position (dialog, GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width(GTK_WINDOW(dialog),10);
	if(win==1)
		label=gtk_label_new("Congratulazioni! Il giocatore rosso ha vinto!");
	if(win==2)
		label=gtk_label_new("Congratulazioni! Il giocatore giallo ha vinto!");
	gtk_label_set_justify(label,GTK_JUSTIFY_CENTER);
	gtk_misc_set_alignment(GTK_MISC (label),0,0);
	table=gtk_table_new(2,2,TRUE);
	gtk_container_add(GTK_WINDOW(dialog),table);
	gtk_table_attach_defaults(GTK_TABLE (table),label,0,2,0,1);
	button=gtk_button_new_with_label("Esci");
	g_signal_connect(button,"clicked",G_CALLBACK(bottone_dialogo),"esci");
	gtk_table_attach_defaults(GTK_TABLE (table),button,0,1,1,2);
	gtk_widget_show(button);
	button=gtk_button_new_with_label("Rigioca");
	g_signal_connect(button,"clicked",G_CALLBACK(bottone_dialogo),"rigioca");
	gtk_table_attach_defaults(GTK_TABLE (table),button,1,2,1,2);
	gtk_widget_show(button);
	gtk_window_set_default_size(dialog, 180, 40);
	gtk_widget_show(label);
	gtk_widget_show(table);
	gtk_widget_show(dialog);
}

void crea_dialogo()
{
	GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *table1;
	table1=gtk_table_new(1,1,TRUE);
	dialog=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(dialog),"ERRORE");
	gtk_container_set_border_width(GTK_WINDOW(dialog),10);
	gtk_container_add(GTK_CONTAINER(dialog),table1);
	gtk_window_set_position (dialog, GTK_WIN_POS_CENTER_ALWAYS);
	label=gtk_label_new("Colonna piena");
	gtk_misc_set_alignment(GTK_MISC (label),0,0);
	gtk_label_set_justify(label,GTK_JUSTIFY_CENTER);
	gtk_table_attach_defaults(table1,label,0,1,0,1);
	gtk_window_set_default_size(dialog, 180, 40);
	gtk_widget_show(label);
	gtk_widget_show(table1);
	gtk_widget_show(dialog);
}

void crea_dialogo2()
{
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *table;
	dialog=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(dialog),"Game Over");
	g_signal_connect(dialog,"delete-event",G_CALLBACK(delete_event),NULL);
	gtk_window_set_position (dialog, GTK_WIN_POS_CENTER_ALWAYS);
	gtk_container_set_border_width(GTK_WINDOW(dialog),10);
	label=gtk_label_new("Nessuno dei giocatori ha vinto...");
	gtk_label_set_justify(label,GTK_JUSTIFY_CENTER);
	gtk_misc_set_alignment(GTK_MISC (label),0,0);
	table=gtk_table_new(2,2,TRUE);
	gtk_container_add(GTK_WINDOW(dialog),table);
	gtk_table_attach_defaults(GTK_TABLE (table),label,0,2,0,1);
	button=gtk_button_new_with_label("Esci");
	g_signal_connect(button,"clicked",G_CALLBACK(bottone_dialogo),"esci");
	gtk_table_attach_defaults(GTK_TABLE (table),button,0,1,1,2);
	gtk_widget_show(button);
	button=gtk_button_new_with_label("Rigioca");
	g_signal_connect(button,"clicked",G_CALLBACK(bottone_dialogo),"rigioca");
	gtk_table_attach_defaults(GTK_TABLE (table),button,1,2,1,2);
	gtk_widget_show(button);
	gtk_window_set_default_size(dialog, 180, 40);
	gtk_widget_show(label);
	gtk_widget_show(table);
	gtk_widget_show(dialog);
}

void crea_finestra(int x)
{
	gint i,j,t,s=0;
	GtkWidget *button;
	GtkWidget *label;
	GtkWidget *image;
	
	table=gtk_table_new(9,7,TRUE);
	gtk_container_add(GTK_WINDOW (window),table);
	
	for(i=0;i<7;i++)
	{
		button=gtk_button_new_with_label("\\/");
		gtk_table_attach(GTK_TABLE (table),button,i,i+1,1,2,TRUE,FALSE,0,0);
		g_signal_connect(button, "clicked",G_CALLBACK(bottone), i);
		gtk_widget_show(button);
	}
	
	t=0;
	for(j=0;j<7;j++)
	{
		if(j==x)
		{
			if(t==0)
			{
				t=1;
				for(i=5;i>=0;i--)
					if(mat[i][j]==0)
						break;
				s=i;
				if(i>=0)
				{
					if(g==1)
						mat[i][j]=1;
					if(g==2)
						mat[i][j]=2;
				}
			}
		}
	}
	
	for(j=0;j<6;j++)
	{
		for(i=0;i<7;i++)
		{
			if(mat[j][i]==0)
			{
				//label=gtk_label_new("|________|");
				image = gtk_image_new_from_file ("images/vuoto.png");
			}
			if(mat[j][i]==1)
			{
				//label=gtk_label_new("|___G1___|");
				image = gtk_image_new_from_file ("images/rosso.png");
			}
			if(mat[j][i]==2)
			{
				//label=gtk_label_new("|___G2___|");
				image = gtk_image_new_from_file ("images/giallo.png");
			}
			//gtk_misc_set_alignment(GTK_MISC (label),0,0);
			//gtk_table_attach_defaults(GTK_TABLE (table),label,i,i+1,j+2,j+3);
			//gtk_widget_show(label);
			gtk_table_attach_defaults(GTK_TABLE (table),image,i,i+1,j+2,j+3);
			gtk_widget_show(image);
		}
	}
	
	if(s>=0)
	{
		if(g==1)
			g=2;
		else
			g=1;
	}	
	if(g==1)
		label=gtk_label_new("E' il turno del giocatore Rosso");
	if(g==2)
		label=gtk_label_new("E' il turno del giocatore Giallo");
	
	gtk_misc_set_alignment(GTK_MISC (label),0,0);
	gtk_table_attach(GTK_TABLE (table),label,0,4,0,1,FALSE,FALSE,0,0);
	gtk_widget_show(label);
	
	button=gtk_button_new_with_label("Riavvia");
	g_signal_connect(button,"clicked",G_CALLBACK(riavvia),NULL);
	gtk_table_attach(GTK_TABLE(table),button,5,7,0,1,FALSE,FALSE,0,0);
	gtk_widget_show(button);
	
	controlla_vincitore();
	
	if(win!=0)
	{
		gtk_widget_set_sensitive (table, FALSE);
		vincita();
	}
	GtkWidget *font_desc;
	
	label=gtk_label_new("Created by Carlo Ramponi");
	gtk_misc_set_alignment(GTK_MISC(label),1,1);
	font_desc = pango_font_description_from_string ("Ubuntu 8");
	gtk_widget_modify_font(GTK_WIDGET(label), font_desc);
	gtk_table_attach_defaults(table,label,0,7,8,9);
	gtk_widget_show(label);
	
	gtk_widget_show(table);
	t=0;
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
		{
			if(mat[i][j]==0)
			{
				t=1;
			}
		}
	}
	if(t==0&&win==0)
	{
		gtk_widget_set_sensitive (table, FALSE);
		crea_dialogo2();
	}
	if(s<0)
		crea_dialogo();
}


int main(int argc,char *argv[])
{
	gtk_init(&argc,&argv);
	//GdkPixbuf *icon;
	//icon = gdk_pixbuf_new_from_data("images/icon.png",GDK_COLORSPACE_RGB,TRUE,8,175,175,4,NULL,NULL);
	int i,j;
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
			mat[i][j]=0;
	}
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW (window),"Forza 4");
	gtk_container_set_border_width(GTK_WINDOW (window),25);
	gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
	g_signal_connect(window,"delete-event",G_CALLBACK (delete_event),NULL);
	//gtk_window_set_position (window, GTK_WIN_POS_CENTER_ALWAYS);
	//gtk_window_set_icon (window,icon);
	crea_finestra(8);
	gtk_widget_show(window);
	gtk_main();
	return 0;
}
