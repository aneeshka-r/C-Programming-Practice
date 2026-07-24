/*
Created by Aneeshka C. Ramoutar on 1/2/26
Heart SVG Generator

Automatically creates svg.html.
Uses math.h for sin, cos, pow and time.h for random seeding.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Global file pointer
FILE* svgFile;

// Function prototypes
void circle(int cx, int cy, int r, const char* color);
void line(float x1, float y1, float x2, float y2, const char* stroke);
void rect(int x, int y, int width, int height, const char* color);
void beginHtmlSVG(int wide, int high, const char* backColor);
void endHtmlSVG();
char* getRGBColor(int red, int green, int blue);

int main() {
    srand(time(NULL));

    // Open the output HTML file
    svgFile = fopen("svg.html", "w");

    if (svgFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    beginHtmlSVG(1000, 1000, getRGBColor(20, 20, 40));

    // Heart center
    int centerX = 500;
    int centerY = 450;

    double t;
    int prevX = 0, prevY = 0;
    int cx, cy;

    /*
    Parametric heart equation:
    x = 16sin^3(t)
    y = 13cos(t)-5cos(2t)-2cos(3t)-cos(4t)
    */

    // Draw heart outline
    for (t = 0; t <= 6.28; t += 0.01) {

        double x = 16 * pow(sin(t), 3);
        double y = 13 * cos(t)
                 - 5 * cos(2 * t)
                 - 2 * cos(3 * t)
                 - cos(4 * t);

        // Scale and center heart
        cx = (int)(x * 20 + centerX);
        cy = (int)(-y * 20 + centerY);

        // Connect points with lines
        if (t > 0) {
            line(prevX, prevY, cx, cy,
                 "stroke:rgb(255,120,160);stroke-width:3");
        }

        prevX = cx;
        prevY = cy;
    }

    // Add colorful lines inside heart
    for (int i = 0; i < 80; i++) {

        // Random angle along heart curve
        double t1 = ((double)rand() / RAND_MAX) * 6.28;

        int x1 = (int)(16 * pow(sin(t1), 3) * 18 + centerX);

        int y1 = (int)(-(13 * cos(t1)
                 - 5 * cos(2 * t1)
                 - 2 * cos(3 * t1)
                 - cos(4 * t1)) * 18 + centerY);

        char color[60];

        snprintf(color, sizeof(color),
                 "stroke:rgb(0,%d,%d);stroke-width:1",
                 140 + rand() % 80,
                 180 + rand() % 70);

        // Draw line from heart edge to center
        line(x1, y1, centerX, centerY, color);
    }

    // Create flowers around heart
    double flowerRadius = 380;

    for (t = 0; t < 6.28; t += 0.5) {

        int fx = (int)(centerX + flowerRadius * cos(t));
        int fy = (int)(centerY + flowerRadius * sin(t));

        // Stem
        rect(fx - 3, fy + 15, 6, 45,
             getRGBColor(0, 150, 0));

        // Flower center
        circle(fx, fy, 6,
               getRGBColor(255, 220, 0));

        // Petals
        for (int i = 0; i < 6; i++) {

            double angle = i * (6.28 / 6);

            int px = fx + (int)(14 * cos(angle));
            int py = fy + (int)(14 * sin(angle));

            circle(px, py, 6,
                   getRGBColor(120 + rand() % 120,
                               120 + rand() % 120,
                               255));
        }
    }

    endHtmlSVG();

    fclose(svgFile);

    printf("svg.html successfully created!\n");

    return 0;
}


// Draw filled circle in SVG
void circle(int cx, int cy, int r, const char* color) {

    fprintf(svgFile,
        "<circle cx='%d' cy='%d' r='%d' fill='%s' />\n",
        cx, cy, r, color);
}


// Draw line in SVG
void line(float x1, float y1, float x2, float y2, const char* stroke) {

    fprintf(svgFile,
        "<line x1='%f' y1='%f' x2='%f' y2='%f' style='%s' />\n",
        x1, y1, x2, y2, stroke);
}


// Draw rectangle in SVG
void rect(int x, int y, int width, int height, const char* color) {

    fprintf(svgFile,
        "<rect x='%d' y='%d' width='%d' height='%d' style='fill:%s;' />\n",
        x, y, width, height, color);
}


// Create HTML and SVG beginning
void beginHtmlSVG(int wide, int high, const char* backColor) {

    fprintf(svgFile,
        "<!DOCTYPE html>\n<html>\n<body>\n");

    fprintf(svgFile,
        "<svg width='%d' height='%d' style='background-color:%s;'>\n",
        wide, high, backColor);
}


// Close SVG and HTML
void endHtmlSVG() {

    fprintf(svgFile,
        "</svg>\n</body>\n</html>\n");
}


// Convert RGB values into SVG color format
char* getRGBColor(int red, int green, int blue) {

    static char result[50];

    sprintf(result,
            "rgb(%d,%d,%d)",
            red, green, blue);

    return result;
}