package com.abhiroop.part1;

import javax.swing.*;
import java.awt.*;

public class LineDisplay extends Canvas {
    //center origin
    private final int xOrigin;
    private final int yOrigin;
    private final JFrame displayWindow;

    public LineDisplay(JFrame displayWindow) {
        //set Background Color
        setBackground(Color.white);

        //get origin of the displayWindow
        xOrigin = (displayWindow.getX() + displayWindow.getWidth()) / 2;
        yOrigin = (displayWindow.getY() + displayWindow.getHeight() / 2);

        this.displayWindow = displayWindow;
    }

    private void drawLineCircle(Graphics g, int length, int xCenter, int yCenter, LineDrawer lineDrawer, String text){
        for(int angle = 0; angle <= 360; angle += 30){
            int x2 = xCenter + (int)Math.round(length * Math.cos(angle * Math.PI /180));
            int y2 = yCenter + (int)Math.round(length * Math.sin(angle * Math.PI /180));
            lineDrawer.draw(g, xCenter, yCenter, x2 , y2);
        }

        g.drawString(text, xOrigin + xCenter - text.length()/2*10, yOrigin - yCenter + length + 30);
    }

    private void drawLine(Graphics graphics, Color color, int x1,int y1, int x2, int y2){
        graphics.setColor(color);
        graphics.drawLine(xOrigin  + x1, yOrigin - y1, xOrigin + x2, yOrigin - y2);
    }

    private void drawString(Graphics g, Color color,  String str, int x, int y) {
        var offset = 4;
        g.setColor(color);
        g.drawString(str, xOrigin + x + offset, yOrigin + y + offset + g.getFont().getSize());
    }

    private void drawGraph(Graphics g){
        //going twice the window size to ensure zoom out works
        var axisColor = new Color(3,133,88);
        var graphLineColor = Color.GRAY;
        var scale = 100;
        var lineDrawer = new Bresenham(xOrigin, yOrigin);

        var leftLimit = -1* (displayWindow.getWidth() - xOrigin) * 2;
        var rightLimit = (displayWindow.getWidth() - xOrigin)*2;
        var topLimit = (displayWindow.getHeight() - yOrigin) * 2;
        var bottomLimit = -1* (displayWindow.getHeight() - yOrigin) * 2;


        //x-axis
        drawLine(g, axisColor,leftLimit, 0, rightLimit, 0);
        //y-axis
        drawLine(g, axisColor, 0,topLimit, 0, bottomLimit);

        //origin
        drawString(g,axisColor,"0", 0, 0);

        //drawing Horizontal lines
        for (int y= scale; y <= topLimit;y+= scale) {
//            drawLine(g, graphLineColor, leftLimit, y, rightLimit, y);
            drawString(g, axisColor,Integer.toString(-y), 0, y);
        }
        for (int y= -scale  ; y >= bottomLimit;y-= scale ) {
//            drawLine(g, graphLineColor, leftLimit, y, rightLimit, y);
            drawString(g, axisColor,Integer.toString(-y), 0, y);
        }

        //drawing vertical lines
        for (int x= scale; x <= rightLimit;x+= scale ) {
//            drawLine(g, graphLineColor, x, topLimit, x, bottomLimit);
            drawString(g, axisColor, Integer.toString(x), x, 0);
        }
        for (int x= -scale; x >= leftLimit;x-= scale ) {
//            drawLine(g, graphLineColor, x, topLimit, x, bottomLimit);
            drawString(g, axisColor, Integer.toString(x), x, 0);
        }
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
        drawGraph(g);
        g.setColor(Color.BLACK);
        drawLineCircle(g, 100, -200, 200, new DDA(xOrigin, yOrigin), "DDA");
        drawLineCircle(g, 100, 200, 200, new Bresenham(xOrigin, yOrigin), "Bresenham");
        drawLineCircle(g, 100, 0, -200, new MidPoint(xOrigin, yOrigin), "Mid Point");
    }
}
