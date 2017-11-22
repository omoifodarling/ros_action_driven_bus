#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include <gtk/gtk.h>
unsigned char * views[5];
int main_view;
float lidar_angle_min;
float lidar_angle_increment;
float * lidar_ranges;
int lidar_ranges_num = 32;
std::string topic_base;
ros::NodeHandle * node;
ros::Publisher * p;
ros::Subscriber * s0, * s1, * s2, * s3, * s4;
GtkWidget * window;
gint timeout;
gdouble steering;
gdouble speed;
void turn_off_view(int i, int size) {
    int k = 0;
    while (k < size) {
        views[i][k + 0] = 255; // blue
        views[i][k + 1] = 200; // green
        views[i][k + 2] = 200; // red
        k += 4;
    }
}
void turn_off_views() {
    turn_off_view(0, 100 * 100 * 4);
    turn_off_view(1, 100 * 100 * 4);
    turn_off_view(2, 100 * 100 * 4);
    turn_off_view(3, 100 * 100 * 4);
    turn_off_view(4, 400 * 400 * 4);
    for (int i = 0; i < lidar_ranges_num; i++) {
        lidar_ranges[i] = 0;
    }
}
gboolean on_click(GtkWidget * widget, gpointer data) {
    gint x, y;
    gdk_window_get_pointer(gtk_widget_get_window(widget), &x, &y, NULL);
    if (y > 55 && y < 155) {
        if (x > 10 && x < 110) {
            main_view = 0;
        }
        else if (x > 110 && x < 210) {
            main_view = 1;
        }
        else if (x > 210 && x < 310) {
            main_view = 2;
        }
        else if (x > 310 && x < 410) {
            main_view = 3;
        }
    }
}
void on_camera_msg(const sensor_msgs::Image::ConstPtr & msg, int view_num) {
    const unsigned char * d = &(msg->data)[0];
    int i = 0;
    int k = 0;
    while (i < 400 * 400 * 3) {
        views[view_num][k + 0] = d[i + 0]; // blue
        views[view_num][k + 1] = d[i + 1]; // green
        views[view_num][k + 2] = d[i + 2]; // red
        i += 12;
        k += 4;
        if (i % (400 * 3) == 0) {
            i += 400 * 3 * 3;
        }
    }
    if (view_num == main_view) {
        i = 0;
        k = 0;
        while (i < 400 * 400 * 3) {
            views[4][k + 0] = d[i + 0]; // blue
            views[4][k + 1] = d[i + 1]; // green
            views[4][k + 2] = d[i + 2]; // red
            i += 3;
            k += 4;
        }
    }
}
void on_camera_msg_0(const sensor_msgs::Image::ConstPtr & msg) {
    on_camera_msg(msg, 0);
}
void on_camera_msg_1(const sensor_msgs::Image::ConstPtr & msg) {
    on_camera_msg(msg, 1);
}
void on_camera_msg_2(const sensor_msgs::Image::ConstPtr & msg) {
    on_camera_msg(msg, 2);
}
void on_camera_msg_3(const sensor_msgs::Image::ConstPtr & msg) {
    on_camera_msg(msg, 3);
}
void on_lidar_msg(const sensor_msgs::LaserScan::ConstPtr & msg) {
    lidar_angle_min = msg->angle_min;
    lidar_angle_increment = msg->angle_increment;
    memcpy(lidar_ranges, &(msg->ranges)[0], lidar_ranges_num * sizeof(float));
}
gboolean on_timer(GtkWidget * widget) {
    ros::spinOnce();
    gtk_widget_queue_draw(widget);
    return TRUE;
}
void on_connect_cameras(GtkToggleButton * button) {
    if (button->active) {
        s0 = new ros::Subscriber(node->subscribe(topic_base + "/left_camera/image_raw", 1, on_camera_msg_0));
        s1 = new ros::Subscriber(node->subscribe(topic_base + "/front_camera/image_raw", 1, on_camera_msg_1));
        s2 = new ros::Subscriber(node->subscribe(topic_base + "/right_camera/image_raw", 1, on_camera_msg_2));
        s3 = new ros::Subscriber(node->subscribe(topic_base + "/rear_camera/image_raw", 1, on_camera_msg_3));
        s4 = new ros::Subscriber(node->subscribe(topic_base + "/lidar", 1, on_lidar_msg));
        timeout = g_timeout_add(10, (GSourceFunc)on_timer, (gpointer)window);
    }
    else {
        delete s0;
        delete s1;
        delete s2;
        delete s3;
        delete s4;
        s0 = NULL;
        s1 = NULL;
        s2 = NULL;
        s3 = NULL;
        s4 = NULL;
        turn_off_views();
        g_source_remove(timeout);
        gtk_widget_queue_draw(window);
    }
}
gboolean on_expose(GtkWidget * widget, GdkEventExpose * event, gpointer data) {
    cairo_t * cr;
    cr = gdk_cairo_create(widget->window);
    cairo_surface_t * s0 = cairo_image_surface_create_for_data(views[0], CAIRO_FORMAT_RGB24, 100, 100, 100 * 4);
    cairo_surface_t * s1 = cairo_image_surface_create_for_data(views[1], CAIRO_FORMAT_RGB24, 100, 100, 100 * 4);
    cairo_surface_t * s2 = cairo_image_surface_create_for_data(views[2], CAIRO_FORMAT_RGB24, 100, 100, 100 * 4);
    cairo_surface_t * s3 = cairo_image_surface_create_for_data(views[3], CAIRO_FORMAT_RGB24, 100, 100, 100 * 4);
    cairo_surface_t * s4 = cairo_image_surface_create_for_data(views[4], CAIRO_FORMAT_RGB24, 400, 400, 400 * 4);
    cairo_set_source_surface(cr, s0, 1, 1);
    cairo_paint(cr);
    cairo_set_source_surface(cr, s1, 101, 1);
    cairo_paint(cr);
    cairo_set_source_surface(cr, s2, 201, 1);
    cairo_paint(cr);
    cairo_set_source_surface(cr, s3, 301, 1);
    cairo_paint(cr);
    cairo_set_source_surface(cr, s4, 1, 111);
    cairo_paint(cr);
    cairo_set_line_width(cr, 2);
    cairo_set_source_rgb(cr, 1, 0.75, 0.75);
    cairo_move_to(cr, 101, 1);
    cairo_line_to(cr, 101, 101);
    cairo_move_to(cr, 201, 0);
    cairo_line_to(cr, 201, 101);
    cairo_move_to(cr, 301, 0);
    cairo_line_to(cr, 301, 101);
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0.25, 0.25, 1);
    cairo_move_to(cr, main_view * 100 + 1, 1);
    cairo_line_to(cr, main_view * 100 + 101, 1);
    cairo_line_to(cr, main_view * 100 + 101, 101);
    cairo_line_to(cr, main_view * 100 + 1, 101);
    cairo_line_to(cr, main_view * 100 + 1, 1);
    cairo_stroke(cr);
    cairo_destroy(cr);
    return FALSE;
}
gboolean on_expose_2(GtkWidget * widget, GdkEventExpose * event, gpointer data) {
    cairo_t * cr;
    cr = gdk_cairo_create(widget->window);
    cairo_set_line_width(cr, 1);
    cairo_set_source_rgb(cr, 0.25, 0.25, 1);
    cairo_move_to(cr, 2, 112);
    cairo_line_to(cr, 400, 112);
    cairo_line_to(cr, 400, 510);
    cairo_line_to(cr, 2, 510);
    cairo_line_to(cr, 2, 112);
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0.5, 0.5, 1);
    cairo_move_to(cr, 200, 510);
    for (int i = 0; i < lidar_ranges_num; i++) {
        float x;
        if (isinf(lidar_ranges[lidar_ranges_num - 1 - i])) {
            x = 250;
        }
        else {
            x = 10 * lidar_ranges[lidar_ranges_num - 1 - i];
        }
        cairo_line_to(
            cr,
            200 - (x * cosf((M_PI / 2) + lidar_angle_min + (i * lidar_angle_increment))),
            510 - (x * sinf((M_PI / 2) + lidar_angle_min + (i * lidar_angle_increment))));
    }
    cairo_close_path(cr);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);
    cairo_destroy(cr);
    return FALSE;
}
void publish() {
    geometry_msgs::Twist msg;
    msg.linear.x = speed;
    msg.linear.y = 0;
    msg.linear.z = 0;
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = steering;
    p->publish(msg);
}
void on_steering(GtkAdjustment * adj) {
    steering = adj->value;
    publish();
}
void on_speed(GtkAdjustment * adj) {
    speed = adj->value;
    publish();
}
int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: control_center <prefix>\n");
        return 0;
    }
    main_view = 0;
    views[0] = (unsigned char *)malloc(100 * 100 * 4);
    views[1] = (unsigned char *)malloc(100 * 100 * 4);
    views[2] = (unsigned char *)malloc(100 * 100 * 4);
    views[3] = (unsigned char *)malloc(100 * 100 * 4);
    views[4] = (unsigned char *)malloc(400 * 400 * 4);
    lidar_ranges = (float *)malloc(sizeof(float) * lidar_ranges_num);
    turn_off_views();

    topic_base = argv[1];
    ros::init(argc, argv, "control_center");
    node = new ros::NodeHandle();
    p = new ros::Publisher(node->advertise<geometry_msgs::Twist>("/bus/vel", 1));

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget * box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget * box2 = gtk_hbox_new(FALSE, 0);
    GtkWidget * connect_cameras = gtk_check_button_new_with_label("Connect cameras");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(connect_cameras), FALSE);
    gtk_box_pack_start(GTK_BOX(box2), connect_cameras, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 10);

    box2 = gtk_hbox_new(FALSE, 0);
    GtkWidget * area = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(area), 402, 512);
    gtk_box_pack_start(GTK_BOX(box2), area, FALSE, FALSE, 10);
    GtkWidget * area2 = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(area2), 402, 512);
    gtk_box_pack_start(GTK_BOX(box2), area2, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 10);

    steering = 0;
    box2 = gtk_hbox_new(FALSE, 0);
    GtkWidget * label = gtk_label_new("Steering:");
    GtkObject * adj = gtk_adjustment_new(0.0, -2.5, 2.6, 0.1, 0.1, 0.1);
    GtkWidget * hscale = gtk_hscale_new(GTK_ADJUSTMENT(adj));
    gtk_widget_set_size_request(hscale, 300, -1);
    gtk_scale_set_digits(GTK_SCALE(hscale), 2);
    gtk_scale_set_value_pos(GTK_SCALE(hscale), GTK_POS_TOP);
    gtk_box_pack_start(GTK_BOX(box2), label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box2), hscale, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 10);

    speed = 0;
    box2 = gtk_hbox_new(FALSE, 0);
    label = gtk_label_new("Speed:");
    GtkObject * adj2 = gtk_adjustment_new(0.0, 0.0, 5.1, 0.1, 0.1, 0.1);
    hscale = gtk_hscale_new(GTK_ADJUSTMENT(adj2));
    gtk_widget_set_size_request(hscale, 300, -1);
    gtk_scale_set_digits(GTK_SCALE(hscale), 2);
    gtk_scale_set_value_pos(GTK_SCALE(hscale), GTK_POS_TOP);
    gtk_box_pack_start(GTK_BOX(box2), label, FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(box2), hscale, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, FALSE, FALSE, 10);

    gtk_widget_set_events(window, GDK_BUTTON_RELEASE_MASK);
    g_signal_connect(window, "button_release_event", G_CALLBACK(on_click), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(connect_cameras, "toggled", G_CALLBACK(on_connect_cameras), NULL);
    g_signal_connect(area, "expose-event", G_CALLBACK(on_expose), NULL);
    g_signal_connect(area2, "expose-event", G_CALLBACK(on_expose_2), NULL);
    g_signal_connect(adj, "value_changed", G_CALLBACK(on_steering), NULL);
    g_signal_connect(adj2, "value_changed", G_CALLBACK(on_speed), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 850, 750);
    gtk_window_set_title(GTK_WINDOW(window), "Control Center");
    gtk_widget_show_all(window);
    gtk_main();

    if (s0) {
        delete s0;
        delete s1;
        delete s2;
        delete s3;
        delete s4;
    }
    delete p;
    delete node;

    free(views[0]);
    free(views[1]);
    free(views[2]);
    free(views[3]);
    free(views[4]);
    free(lidar_ranges);
    return 0;
}
