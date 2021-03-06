#include <gtk/gtk.h>

static void print_hello (GtkWidget *widget,
                         gpointer data)
{
    g_print ("Hello World\n");
}

int main (int argc, char *argv[])
{
    GtkBuilder *builder;
    GObject *window;
    GObject *button;

    gtk_init (&argc, &argv);

    builder = gtk_builder_new ();

    if (argc == 2) {
        gtk_builder_add_from_file (builder, argv[1], NULL);

        window = gtk_builder_get_object (builder, "dialog");
        g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

        gtk_main ();

        g_object_unref (builder);

        return 0;
    }

    gtk_builder_add_from_file (builder, "builder.ui", NULL);

    window = gtk_builder_get_object (builder, "window");
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    button = gtk_builder_get_object (builder, "button1");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

    button = gtk_builder_get_object (builder, "button2");
    g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

    button = gtk_builder_get_object (builder, "quit");
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main ();

    g_object_unref (builder);

    return 0;
}
