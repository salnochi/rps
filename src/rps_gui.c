#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

FILE *fpt;

enum {
    ROCK = 1,
    PAPER,
    SCISSORS
};

typedef struct {
    GtkWidget *label_result;
    GtkWidget *label_computer_choice;
    GtkWidget *label_user_choice;
} AppWidgets;

int getComputerChoice() {
    return (rand() % 3) + 1;
}

const char* choiceToString(int choice) {
    switch (choice) {
        case ROCK: return "Rock";
        case PAPER: return "Paper";
        case SCISSORS: return "Scissors";
        default: return "Unknown";
    }
}

void logResult(const char *result, int userChoice, int computerChoice) {
    fpt = fopen("logs/rps_gui.csv", "a");
    if (fpt) {
        fprintf(fpt, "\n%s,%d,%d", result, userChoice, computerChoice);
        fclose(fpt);
    }
}

void checkWinner(int userChoice, int computerChoice, AppWidgets *app_wdgts) {
    const char *result_text;
    if (userChoice == computerChoice) {
        result_text = "It's a Tie!";
    } else if ((userChoice == ROCK && computerChoice == SCISSORS) ||
               (userChoice == PAPER && computerChoice == ROCK) ||
               (userChoice == SCISSORS && computerChoice == PAPER)) {
        result_text = "You Win!";
    } else {
        result_text = "You Lose :(";
    }

    gtk_label_set_text(GTK_LABEL(app_wdgts->label_result), result_text);
    gtk_label_set_text(GTK_LABEL(app_wdgts->label_user_choice), choiceToString(userChoice));
    gtk_label_set_text(GTK_LABEL(app_wdgts->label_computer_choice), choiceToString(computerChoice));

    logResult(result_text, userChoice, computerChoice);
}

void on_choice_button_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *app_wdgts = (AppWidgets *)user_data;
    int userChoice = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "choice"));
    int computerChoice = getComputerChoice();

    checkWinner(userChoice, computerChoice, app_wdgts);
}

void on_play_again_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *app_wdgts = (AppWidgets *)user_data;
    gtk_label_set_text(GTK_LABEL(app_wdgts->label_result), "");
    gtk_label_set_text(GTK_LABEL(app_wdgts->label_user_choice), "");
    gtk_label_set_text(GTK_LABEL(app_wdgts->label_computer_choice), "");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    srand(time(NULL));

    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    fpt = fopen("logs/rps_gui.csv", "a");
    if (fpt) {
        fprintf(fpt, "\nNew GAME!!: %s", asctime(timeinfo));
        fclose(fpt);
    }

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Rock Paper Scissors");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label_title = gtk_label_new("<b>Please Make a Selection:</b>");
    gtk_label_set_use_markup(GTK_LABEL(label_title), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), label_title, FALSE, FALSE, 0);

    GtkWidget *hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);

    GtkWidget *btn_rock = gtk_button_new_with_label("Rock");
    GtkWidget *btn_paper = gtk_button_new_with_label("Paper");
    GtkWidget *btn_scissors = gtk_button_new_with_label("Scissors");

    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_rock, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_paper, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_buttons), btn_scissors, TRUE, TRUE, 0);

    AppWidgets *app_wdgts = g_slice_new(AppWidgets);

    GtkWidget *label_user = gtk_label_new("Your Choice: ");
    app_wdgts->label_user_choice = gtk_label_new("");
    GtkWidget *hbox_user = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox_user), label_user, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_user), app_wdgts->label_user_choice, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_user, FALSE, FALSE, 0);

    GtkWidget *label_computer = gtk_label_new("Computer's Choice: ");
    app_wdgts->label_computer_choice = gtk_label_new("");
    GtkWidget *hbox_computer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox_computer), label_computer, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_computer), app_wdgts->label_computer_choice, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_computer, FALSE, FALSE, 0);

    GtkWidget *label_result_title = gtk_label_new("Result: ");
    app_wdgts->label_result = gtk_label_new("");
    GtkWidget *hbox_result = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox_result), label_result_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox_result), app_wdgts->label_result, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_result, FALSE, FALSE, 0);

    GtkWidget *btn_play_again = gtk_button_new_with_label("Clear Selections");
    gtk_box_pack_start(GTK_BOX(vbox), btn_play_again, FALSE, FALSE, 0);

    g_object_set_data(G_OBJECT(btn_rock), "choice", GINT_TO_POINTER(ROCK));
    g_object_set_data(G_OBJECT(btn_paper), "choice", GINT_TO_POINTER(PAPER));
    g_object_set_data(G_OBJECT(btn_scissors), "choice", GINT_TO_POINTER(SCISSORS));

    g_signal_connect(btn_rock, "clicked", G_CALLBACK(on_choice_button_clicked), app_wdgts);
    g_signal_connect(btn_paper, "clicked", G_CALLBACK(on_choice_button_clicked), app_wdgts);
    g_signal_connect(btn_scissors, "clicked", G_CALLBACK(on_choice_button_clicked), app_wdgts);
    g_signal_connect(btn_play_again, "clicked", G_CALLBACK(on_play_again_clicked), app_wdgts);

    gtk_widget_show_all(window);
    gtk_main();

    g_slice_free(AppWidgets, app_wdgts);

    return 0;
}
