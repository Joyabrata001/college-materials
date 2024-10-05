package com.abhiroop.part3;

import java.awt.*;

public class TopRightTriangleWithHair extends Shape{
    int baseLength;
    int heightLength;
    int hairLength;

    public TopRightTriangleWithHair(int xOrigin, int yOrigin, int baseLength,
                                    int heightLength, int hairLength) {
        super(xOrigin, yOrigin);
        this.baseLength = baseLength;
        this.heightLength = heightLength;
        this.hairLength= hairLength;
    }

    @Override
    void draw(Graphics g, int startX, int startY) {
        drawLine(g, startX, startY, startX + baseLength, startY);
        drawLine(g,startX + baseLength, startY,
                startX + baseLength, startY + heightLength);
        drawLine(g, startX + baseLength, startY + heightLength,
                startX, startY);

        for(var i = startX + hairLength; i < startX + baseLength; i += hairLength) {
            drawLine(g,i, startY, i, startY - hairLength);
        }
    }
}
