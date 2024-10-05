package com.abhiroop;

import javax.swing.*;
import java.awt.*;

public class Painter extends Canvas {

    private final int originX;
    private final int originY;
    public Painter(JFrame displayWindow) {
        // changes the screen center to center
        originX = (displayWindow.getX() + displayWindow.getWidth())/2;
        originY = (displayWindow.getY() + displayWindow.getHeight())/2;
    }

    /**
     * Draws a Line in human axis from (x1,y1) to (x2,y2)
     * @param graphics Graphics class object
     * @param color foreground color of graphic drawn
     */
    private void drawLine(Graphics graphics, Color color, int x1, int y1, int x2, int y2){
        // Graphics method to set foreground method, will be persistent if not changed
        graphics.setColor(color);
        // -ve y to counteract reverted y-axis
        graphics.drawLine(originX + x1, originY - y1, originX + x2, originY - y2);
    }

    /**
     * draws rectangle  with (x,y) bottom-left corner and (x+ width, y+height) as top-right corner
     * @param graphics Graphics class object
     * @param color foreground color of graphic drawn
     */
    private void drawRectangle(Graphics graphics, Color color, int x, int y, int width , int height){
        graphics.setColor(color);
        //this function draws from (x,y) and goes bottom right, but we want to go top-left
        graphics.drawRect(originX + x, originY - y - height,width, height);

    }

    /**
     * draws Filled rectangle  with (x,y) bottom-left corner and (x+ width, y+height) as top-right corner
     * @param graphics Graphics class object
     * @param color foreground color of graphic drawn
     */
    private void drawFillRectangle(Graphics graphics, Color color, int x, int y, int width , int height){
        graphics.setColor(color);
        //this function draws from (x,y) and goes bottom right, but we want to go top-left
        graphics.fillRect(originX + x, originY - y - height,width, height);

    }

    /**
     * draws an oval with is enclosed in a rectangle with bottom-right corner (x,y) and top-right corner (x+width, y + height)
     * @param graphics Graphics class object
     * @param color foreground color of graphic drawn
     */
    private void drawOval(Graphics graphics, Color color,int x, int y, int width, int height){
        graphics.setColor(color);
        graphics.drawOval(originX + x, originY + y - height, width, height);
    }

    /**
     * draws an Filled Oval with is enclosed in a rectangle with bottom-right corner (x,y) and top-right corner (x+width, y + height)
     * @param graphics Graphics class object
     * @param color foreground color of graphic drawn
     */
    private void drawFillOval(Graphics graphics, Color color,int x, int y, int width, int height){
        graphics.setColor(color);
        graphics.fillOval(originX + x, originY + y - height, width, height);
    }

    private void drawString(Graphics graphics, Color color, Font font, String text, int x, int y){
        graphics.setFont(font);
        graphics.setColor(color);

        graphics.drawString(text, originX + x, originY + y);
    }

    @Override
    public void paint(Graphics g) {
        //Canvas Inbuilt method to set background
        setBackground(Color.WHITE);


        drawFillRectangle(g, Color.GREEN, 0,0,100, 100);
        drawOval(g, Color.BLUE, 0,0,100,100);
        drawLine(g,Color.BLACK,0, 0, 100, 100);

        drawString(g, Color.ORANGE, new Font("Times New Roman", Font.ITALIC,18),
                "Hello World", 0,0);


    }
}
