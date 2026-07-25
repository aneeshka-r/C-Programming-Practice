/*
Created by Aneeshka C. Ramoutar on 02/09/2026
Last Updated: 07/25/2026

SVG House Generator

A C program that generates an HTML file containing multiple SVG
house illustrations with decorative smiley faces using reusable
drawing functions, loops, and SVG elements.
*/

#include <stdio.h>

// Global file pointer
FILE *svgFile;

// Function prototypes
void drawHouse(int xOffset, int yOffset);
void drawSmiley(int x, int y, int size,
                const char *faceColor,
                const char *eyeColor,
                const char *mouthColor,
                const char *strokeColor);

// Function to draw a composite SVG house
void drawHouse(int xOffset, int yOffset) {

    // Filled roof and house shape
    fprintf(svgFile,
        "<path d=\"M %d %d A 150 100 0 0 1 %d %d L %d %d L %d %d Z\" fill=\"url(#boxGrid)\" stroke=\"none\"/>\n",
        100 + xOffset, 200 + yOffset,
        400 + xOffset, 200 + yOffset,
        400 + xOffset, 250 + yOffset,
        100 + xOffset, 250 + yOffset);

    // Roof arc
    fprintf(svgFile,
        "<path d=\"M %d %d A 150 100 0 0 1 %d %d\" fill=\"none\" stroke=\"pink\" stroke-width=\"5\"/>\n",
        100 + xOffset, 200 + yOffset,
        400 + xOffset, 200 + yOffset);

    // Roof outline
    fprintf(svgFile,
        "<polyline points=\"%d,%d %d,%d %d,%d %d,%d %d,%d\" fill=\"none\" stroke=\"purple\" stroke-width=\"4\"/>\n",
        100 + xOffset, 200 + yOffset,
        150 + xOffset, 120 + yOffset,
        250 + xOffset, 90 + yOffset,
        350 + xOffset, 120 + yOffset,
        400 + xOffset, 200 + yOffset);

    // House base
    fprintf(svgFile,
        "<rect x=\"%d\" y=\"%d\" width=\"300\" height=\"50\" fill=\"url(#boxGrid)\" stroke=\"black\" stroke-width=\"4\"/>\n",
        100 + xOffset,
        200 + yOffset);

    // Door
    fprintf(svgFile,
        "<rect x=\"%d\" y=\"%d\" width=\"50\" height=\"35\" fill=\"pink\" stroke=\"purple\" stroke-width=\"2\"/>\n",
        225 + xOffset,
        215 + yOffset);
}

// Function to draw a smiley face
void drawSmiley(int x, int y, int size,
                const char *faceColor,
                const char *eyeColor,
                const char *mouthColor,
                const char *strokeColor) {

    // Face
    fprintf(svgFile,
        "<circle cx='%d' cy='%d' r='%d' fill='%s' stroke='%s' stroke-width='3'/>\n",
        x, y, size, faceColor, strokeColor);

    // Left eye
    fprintf(svgFile,
        "<circle cx='%d' cy='%d' r='%d' fill='%s'/>\n",
        x - size / 3,
        y - size / 3,
        size / 8,
        eyeColor);

    // Right eye
    fprintf(svgFile,
        "<circle cx='%d' cy='%d' r='%d' fill='%s'/>\n",
        x + size / 3,
        y - size / 3,
        size / 8,
        eyeColor);

    // Smile
    fprintf(svgFile,
        "<path d='M %d %d Q%d %d %d %d' stroke='%s' stroke-width='3' fill='transparent'/>\n",
        x - size / 2,
        y + size / 4,
        x,
        y + size / 2,
        x + size / 2,
        y + size / 4,
        mouthColor);
}

int main() {

    // Open HTML output file
    svgFile = fopen("house.html", "w");

    if (svgFile == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Begin HTML and SVG document
    fprintf(svgFile, "<!DOCTYPE html>\n<html>\n<body>\n");
    fprintf(svgFile, "<h2>Composite SVG House Shapes</h2>\n");
    fprintf(svgFile, "<svg width=\"1000\" height=\"600\">\n");

    // Create grid pattern once
    fprintf(svgFile, "<defs>\n");
    fprintf(svgFile,
            "<pattern id=\"boxGrid\" width=\"25\" height=\"25\" patternUnits=\"userSpaceOnUse\">\n");
    fprintf(svgFile,
            "<rect x=\"0\" y=\"0\" width=\"25\" height=\"25\" fill=\"none\" stroke=\"darkblue\" stroke-width=\"1\"/>\n");
    fprintf(svgFile, "</pattern>\n");
    fprintf(svgFile, "</defs>\n");


    // Starting position and spacing
    int x, y;

    int xStart = 0;
    int yStart = 0;

    int xSpacing = 450; // horizontal distance between houses
    int ySpacing = 300; // vertical distance between rows


    // Draw multiple houses using nested loops
    for (y = 0; y < 2; y++) {

        for (x = 0; x < 2; x++) {

            int currentX = xStart + x * xSpacing;
            int currentY = yStart + y * ySpacing;


            // Draw house
            drawHouse(currentX, currentY);


            // Draw smiley above each house
            drawSmiley(currentX + 250,
                       currentY + 80,
                       40,
                       "yellow",
                       "black",
                       "black",
                       "black");
        }
    }


    // Close SVG and HTML tags
    fprintf(svgFile, "</svg>\n");
    fprintf(svgFile, "</body>\n");
    fprintf(svgFile, "</html>\n");


    // Close file
    fclose(svgFile);


    printf("house.html successfully created!\n");

    return 0;
}