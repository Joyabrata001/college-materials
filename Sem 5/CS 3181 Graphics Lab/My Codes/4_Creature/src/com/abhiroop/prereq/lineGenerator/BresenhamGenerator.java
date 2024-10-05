package com.abhiroop.prereq.lineGenerator;

import com.abhiroop.utils.DrawForm;
import com.abhiroop.utils.Pixel;

public class BresenhamGenerator implements LineGenerator {
    @Override
    public DrawForm generate(int x1, int y1, int x2, int y2) {
        var drawForm = new DrawForm();

        int dx = Math.abs(x2 - x1);
        int dy = Math.abs(y2 - y1);

        int sx = x2 > x1 ? 1 : -1;
        int sy = y2 > y1 ? 1 : -1;

        int bigGradient = Math.max(dx, dy);
        int smallGradient = Math.min(dx, dy);

        int p = 2*smallGradient - bigGradient;

        for(int i= 0; i< bigGradient; i++){
            drawForm.add(new Pixel(x1, y1));
            if(p < 0)
                p = p + 2*smallGradient;
            else{
                p = p + 2*smallGradient - 2*bigGradient;

                if(smallGradient == dy)
                    y1 = y1 + sy;
                else
                    x1 = x1 + sx;
            }

            if(bigGradient == dx)
                x1 = x1 + sx;
            else
                y1 = y1 + sy;
        }
        return drawForm;
    }
}
