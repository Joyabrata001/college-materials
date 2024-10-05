package com.abhiroop.bird.utils;

import java.awt.*;

public interface Shape {
    /**
     * Draws the shape
     * @param g     the Graphics Object
     * @param startX    start x-position of the Shape
     * @param startY    start y-position of the Shape
     */
    void drawShape(Graphics g, int startX, int startY);
}
