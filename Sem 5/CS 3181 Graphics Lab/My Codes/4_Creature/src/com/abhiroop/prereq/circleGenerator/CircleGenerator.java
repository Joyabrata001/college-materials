package com.abhiroop.prereq.circleGenerator;

import com.abhiroop.utils.DrawForm;
import com.abhiroop.utils.Pixel;

public class CircleGenerator {
    public static DrawForm generate(int xCenter, int yCenter, int radius){
        var drawForm = new DrawForm();

        int x = 0;
        int y = radius;

        int p = 1-radius;

        while(x<= y){
            //1st quadrant
            drawForm.add(new Pixel(x + xCenter, y + yCenter));
            drawForm.add(new Pixel(y + xCenter, x + yCenter));

            //2nd quadrant
            drawForm.add(new Pixel(-x + xCenter, y + yCenter));
            drawForm.add(new Pixel(-y + xCenter, x + yCenter));

            //3rd quadrant
            drawForm.add(new Pixel(-x + xCenter, -y + yCenter));
            drawForm.add(new Pixel(-y + xCenter, -x + yCenter));

            //4th quadrant
            drawForm.add(new Pixel(x + xCenter, -y + yCenter));
            drawForm.add(new Pixel(y + xCenter, -x + yCenter));

            if(p < 0)
                p = p+ 2*x + 3;
            else{
                p = p + 2*(x-y) + 5;
                y--;
            }
            x++;
        }
        return drawForm;
    }
}
