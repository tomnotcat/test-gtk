#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *grid;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Hello Theming");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "theming.ui", NULL);

    grid = (GtkWidget *)gtk_builder_get_object (builder, "grid");
    gtk_container_add (GTK_CONTAINER (window), grid);

    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all (window);

    gtk_main ();

    g_object_unref (builder);

    return 0;
}
