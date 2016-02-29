#include <gtk/gtk.h>


#define SIZE(x) (sizeof x / sizeof x[0])

static const char *file_menu[] = {
    "New",
    "Open",
    "Open Recent",
    "Save",
    "Save As...",
    "Save Selected as...",
    NULL,
    "Import",
    "Export",
    NULL,
    "Titles and Sheet Setup...",
    "Preview",
    "Print",
    NULL,
    "Schematic Information",
    "Convert to PCB",
    "Back Annotate",
    NULL,
    "Recover Schematic",
    "Recovery Options...",
    NULL,
    "Exit"
};

static const char *edit_menu[] = {
    "Undo",
    "Redo",
    NULL,
    "Cut",
    "Copy",
    "Paste",
    "Delete",
    "Select All",
    "Edit Selection...",
    NULL,
    "Find Object...",
    NULL,
    "Add Sheet",
    "Sheet Type",
    "Copy Matrix",
    NULL,
    "Rotate",
    NULL,
    "Group",
    "Ungroup",
    NULL,
    "Lock Selected",
    "Unlock Selected",
    NULL,
    "Properties..."
};

static const char *view_menu[] = {
    "Toolbars",
    NULL,
    "Part preview",
    "Group Similar Parts",
    "Display Hint",
    NULL,
    "Part Markings",
    "Connection to Bus",
    "Pin Numbers",
    NULL,
    "Hide Power and Grid",
    NULL,
    "Display Titles",
    "Display Sheet",
    NULL,
    "Scale",
    "Line Width...",
    "Colors...",
    "Graphic Mode",
    "Units",
    NULL,
    "Display Origin",
    "Define Origin",
    NULL,
    "Grid",
    "Grid Size",
    "Customize Grid..."
};

static const char *objects_menu[] = {
    "Place Component...",
    "Find Component...",
    NULL,
    "Circuit",
    "High Speed",
    "Hierarchy",
    "Net Classes",
    "Load Classes",
    "Connection Manager",
    NULL,
    "Place Table",
    "Bill of Materials",
    NULL,
    "Place Shape",
    "Place Text",
    "Place Picture",
    "Drawing Properties"
};

static const char *verification_menu[] = {
    "Electrical Rule Check",
    "Electrical Rule Setup",
    "Check Hierarchy"
};

static const char *library_menu[] = {
    "Library Setup",
    NULL,
    "Copy \"{library}\" Library to Another Group",
    NULL,
    "Open \"{library}\" Library in Component Editor"
};

static const char *tools_menu[] = {
    "RefDes Renumbering",
    NULL,
    "Hotkey Settings",
    NULL,
    "PCB Layout",
    "Component Editor",
    "Pattern Editor"
};

static const char *help_menu[] = {
    "Schematic Help",
    "DipTrace Beta Tutorial",
    "Getting Started",
    NULL,
    "Register",
    NULL,
    "Request Support",
    "PCB Design Service",
    "DipTrace Beta Home Page",
    NULL,
    "About..."
};

static GtkWidget *create_submenu(const char *items[], int items_count)
{
    GtkWidget *menu = gtk_menu_new();
    for (int i = 0; i < items_count; ++i) {
	GtkWidget *item = items[i] != NULL ? gtk_menu_item_new_with_label(items[i]) : gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
    }
    return menu;
}

static void create_menu(GtkWidget *menubar)
{
    GtkWidget *item;

    item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(file_menu, SIZE(file_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("Edit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(edit_menu, SIZE(edit_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("View");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(view_menu, SIZE(view_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("Objects");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(objects_menu, SIZE(objects_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("Verification");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(verification_menu, SIZE(verification_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("Library");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(library_menu, SIZE(library_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("Tools");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(tools_menu, SIZE(tools_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    item = gtk_menu_item_new_with_label("Help");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), create_submenu(help_menu, SIZE(help_menu)));
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);
}

static void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *menubar;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Schematic");
	gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
	g_signal_connect (window, "destroy", G_CALLBACK(gtk_widget_destroyed), &window);

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	menubar = gtk_menu_bar_new();
	create_menu(menubar);
	gtk_container_add(GTK_CONTAINER(box), menubar);

	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	int status;
	GtkApplication *app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}
