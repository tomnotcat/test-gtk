#include <gtk/gtk.h>

int main (int argc, char *argv[])
{
    GdkScreen *screen;
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *grid;
    GtkCssProvider *provider;
    GError *error = NULL;

    gtk_init (&argc, &argv);

    provider = gtk_css_provider_new ();

    if (!gtk_css_provider_load_from_path (provider, "style.css", &error)) {
        g_object_unref (provider);
        g_clear_error (&error);
        return 0;
    }

    screen = gdk_screen_get_default ();

    gtk_style_context_add_provider_for_screen (
        screen, GTK_STYLE_PROVIDER (provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref (provider);

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
