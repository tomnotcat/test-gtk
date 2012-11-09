#include <gtk/gtk.h>

static void print_hello (GtkWidget *widget,
                         gpointer data)
{
    g_print ("Hello World\n");
}

static gboolean on_delete_event (GtkWidget *widget,
                                 GdkEvent *event,
                                 gpointer data)
{
    g_print ("delete event occurred\n");

    return TRUE;
}

int main (int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Hello World");

    g_signal_connect (window,
                      "delete-event",
                      G_CALLBACK (on_delete_event),
                      NULL);

    g_signal_connect (window,
                      "destroy",
                      G_CALLBACK (gtk_main_quit),
                      NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

    g_signal_connect_swapped (button,
                              "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                              window);

    gtk_container_add (GTK_CONTAINER (window), button);

    gtk_widget_set_size_request (window, 400, 400);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    gtk_widget_show_all (window);

    gtk_main ();

    return 0;
}
