package com.abhiroop.prereq.ellipseGenerator;

import com.abhiroop.prereq.utils.DrawForm;
import com.abhiroop.prereq.utils.Pixel;

public class EllipseGenerator {
    public static DrawForm generate(int xCenter, int yCenter, int radX, int radY) {
        var drawFrom = new DrawForm();

        int x = 0;
        int y = radY;

        double d1 = radX * radY - (radX * radX * radY) + (0.25 * radX * radX);
        int dx = 0;
        int dy = 2 * radX * radX * y;

        //region 1
        while (dx < dy) {
            drawFrom.add(new Pixel(x + xCenter, y + yCenter));
            drawFrom.add(new Pixel(-x + xCenter, y + yCenter));
            drawFrom.add(new Pixel(-x + xCenter, -y + yCenter));
            drawFrom.add(new Pixel(x + xCenter, -y + yCenter));

            if (d1 < 0) {
                x++;
                dx = dx + (2 * radY * radY);
                d1 = d1 + dx + (radY * radY);
            } else {
                x++;
                y--;
                dx = dx + (2 * radY * radY);
                dy = dy - (2 * radX * radX);
                d1 = d1 + dx - dy + (radX * radY);
            }
        }

        double d2 = ((radY * radY) * ((x + 0.5) * (x + 0.5)))
                + ((radX * radX) * ((y - 1) * (y - 1)))
                - (radX * radX * radY * radY);

        while (y >= 0) {
            drawFrom.add(new Pixel(x + xCenter, y + yCenter));
            drawFrom.add(new Pixel(-x + xCenter, y + yCenter));
            drawFrom.add(new Pixel(-x + xCenter, -y + yCenter));
            drawFrom.add(new Pixel(x + xCenter, -y + yCenter));

            if (d2 > 0) {
                y--;
                dy = dy - (2 * radX * radX);
                d2 = d2 + (radX * radX) - dy;
            } else {
                y--;
                x++;
                dx = dx + (2 * radY * radY);
                dy = dy - (2 * radX * radX);
                d2 = d2 + dx - dy + (radX * radX);
            }
        }
        return drawFrom;
    }
}
