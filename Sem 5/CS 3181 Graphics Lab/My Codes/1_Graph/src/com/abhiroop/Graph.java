package com.abhiroop;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.awt.geom.AffineTransform;

public class Graph extends Canvas implements MouseWheelListener {
    private final JFrame displayWindow;

    //center origin
    private final int xOrigin;
    private final int yOrigin;

    //colors
    private final Color graphLineColor;
    private final Color axisColor;

    // for zooming
    private double zoomFactor;
    private double prevZoomFactor;
    private boolean zoomer;
    private double xOffset;
    private double yOffset;

    //for scaling
    private final int scale;


    public Graph(JFrame displayWindow, Color backgroundColor, Color graphLineColor, int scale) {
        //set displayWindow
        this.displayWindow = displayWindow;

        //get origin of the displayWindow
        xOrigin = (displayWindow.getX() + displayWindow.getWidth()) / 2;
        yOrigin = (displayWindow.getY() + displayWindow.getHeight() / 2);

        //set Background Color
        setBackground(backgroundColor);

        //set graphLineGround Color
        this.graphLineColor = graphLineColor;

        //set axisColor
        axisColor = new Color(3,133,88);

        //set zoom specifics
        addMouseWheelListener(this);
        zoomFactor = 1;
        prevZoomFactor = 1;
        xOffset = 0;
        yOffset = 0;
        zoomer = false;

        //scale stuff
        this.scale = scale;

    }

    /**
     * Invoked when the mouse wheel is rotated.
     *
     * @param e the event to be processed
     * @see MouseWheelEvent
     */
    @Override
    public void mouseWheelMoved(MouseWheelEvent e) {
        zoomer = true;

        //zoom in
        if(e.getWheelRotation() < 0)
            zoomFactor *=1.1;
            //zoom out
        else if(e.getWheelRotation() > 0)
            zoomFactor /=1.1;

        repaint();
    }

    /**
     * Draws line in the mathematical form with center in middle.
     * Draws line form (x1,y1) to (x2,y2)
     * @param color the color of the drawn line
     */
    private void drawLine(Graphics graphics, Color color, int x1,int y1, int x2, int y2){
        graphics.setColor(color);
        graphics.drawLine(xOrigin  + x1, yOrigin - y1, xOrigin + x2, yOrigin - y2);
    }

    private void drawString(Graphics g, Color color,  String str, int x, int y) {
        var offset = 4;
        g.setColor(color);
        g.drawString(str, xOrigin + x + offset, yOrigin + y + offset + g.getFont().getSize());
    }

    /**
     * generates the graph lines and indices
     */
    private void drawGraph(Graphics g){
        //going twice the window size to ensure zoom out works

        var leftLimit = -1* (displayWindow.getWidth() - xOrigin) * 2;
        var rightLimit = (displayWindow.getWidth() - xOrigin)*2;
        var topLimit = (displayWindow.getHeight() - yOrigin) * 2;
        var bottomLimit = -1* (displayWindow.getHeight() - yOrigin) * 2;

        //x-axis
        drawLine(g, axisColor, leftLimit, 0, rightLimit, 0);
        //y-axis
        drawLine(g, axisColor, 0,topLimit, 0, bottomLimit);

        //origin
        drawString(g,axisColor,"0", 0, 0);

        //drawing Horizontal lines
        for (int y= 100; y <= topLimit;y+= 100 ) {
            drawLine(g, graphLineColor, leftLimit, y, rightLimit, y);
            drawString(g, axisColor,Integer.toString(-y/100), 0, y);
        }
        for (int y= -100; y >= bottomLimit;y-= 100 ) {
            drawLine(g, graphLineColor, leftLimit, y, rightLimit, y);
            drawString(g, axisColor,Integer.toString(-y/100), 0, y);
        }

        //drawing vertical lines
        for (int x= 100; x <= rightLimit;x+= 100 ) {
            drawLine(g, graphLineColor, x, topLimit, x, bottomLimit);
            drawString(g, axisColor, Integer.toString(x/100), x, 0);
        }
        for (int x= -100; x >= leftLimit;x-= 100 ) {
            drawLine(g, graphLineColor, x, topLimit, x, bottomLimit);
            drawString(g, axisColor, Integer.toString(x/100), x, 0);
        }
    }

    /**
     * draws line in graph according to scale from (x1,y1) to (x2,y2)
     * @param graphics the Graphics object
     * @param color color of the line
     */
    private void drawLineScaled(Graphics graphics, Color color, int x1,int y1, int x2, int y2){
        graphics.setColor(color);
        graphics.drawLine(xOrigin  + x1*scale, yOrigin - y1*scale, xOrigin + x2*scale, yOrigin - y2*scale);
    }

    /**
     * draws a rectangle with (x,y) as center
     * @param g the Graphics object
     * @param color color of rectangle
     * @param height height of the rectangle
     * @param width width of the rectangle
     */
    private void drawRectangleScaled(Graphics g, Color color,int x, int y, int height, int width){
        g.setColor(color);
        g.drawRect(xOrigin + x*scale - width*scale/2, yOrigin - y*scale + y*scale/2 - height*scale, height*scale, width*scale );
    }

    /**
     * draws a Filled Oval with (x,y) as center enclosed in rectangle of height*weight
     * @param g the Graphics object
     * @param color color of Circle Drawn
     */
    private void drawOvalScaled(Graphics g, Color color,int x, int y, int height, int width){
        g.setColor(color);
        g.drawOval(xOrigin + x*scale - width*scale/2, yOrigin - y*scale - height*scale/2 , height*scale, width*scale);
    }

    /**
     * this function handles the zooming capability of the displayWindow
     * @param g the Graphics Object
     */
    void zoom(Graphics g){
        Graphics2D g2 = (Graphics2D)g;
        AffineTransform at = new AffineTransform();

        double xRel = MouseInfo.getPointerInfo().getLocation().getX() - getLocationOnScreen().getX();
        double yRel = MouseInfo.getPointerInfo().getLocation().getY() - getLocationOnScreen().getY();
        double zoomDiv = zoomFactor / prevZoomFactor; //will be 1.1 or 0.9

        xOffset = (zoomDiv) * (xOffset) + (1 - zoomDiv) * xRel;
        yOffset = (zoomDiv) * (yOffset) + (1 - zoomDiv) * yRel;

        at.translate(xOffset, yOffset);
        at.scale(zoomFactor, zoomFactor);
        prevZoomFactor = zoomFactor;
        g2.transform(at);
        zoomer = false;
    }

    /**
     * Paints this canvas.
     * <p>
     * Most applications that subclass {@code Canvas} should
     * override this method in order to perform some useful operation
     * (typically, custom painting of the canvas).
     * The default operation is simply to clear the canvas.
     * Applications that override this method need not call
     * super.paint(g).
     *
     * @param g the specified Graphics context
     * @see #update(Graphics)
     * @see Component#paint(Graphics)
     */
    @Override
    public void paint(Graphics g) {
        if(zoomer)
            zoom(g);

        g.setFont(new Font("Arial", Font.PLAIN, 20));
        drawGraph(g);

        drawLineScaled(g,Color.BLACK, 0,1,5,5);
        drawRectangleScaled(g,Color.BLACK,2,1,1,1 );
        drawOvalScaled(g, Color.black, 0,0,5,5);
    }
}
