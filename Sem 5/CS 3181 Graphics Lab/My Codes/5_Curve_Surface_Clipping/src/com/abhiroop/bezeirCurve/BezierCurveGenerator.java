package com.abhiroop.bezeirCurve;

import com.abhiroop.prereq.utils.DrawForm;
import com.abhiroop.prereq.utils.Pixel;

import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class BezierCurveGenerator {

    private static long ncr(int n, int r){
        long ans = 1;

        for(int i = 1; i <= r; i++) {
            ans *= n - r + i;
            ans /= i;
        }
        return ans;
    }

    private static List<Long> generateCombinations(int n){
        List<Long> combinations = new ArrayList<>();
        for(int i = 0; i<=n;i++)
            combinations.add(ncr(n, i));

        return combinations;
    }

    public static DrawForm generateCurve(List<Point> controlPoints){

        var drawForm = new DrawForm();
        int n = controlPoints.size();
        var combinations = generateCombinations(n - 1);

        for(double t = 0; t <= 1; t+= 0.00001){

            double newX = 0;
            double newY = 0;

            for(int i = 0; i < n; i++){
                var bPoly = combinations.get(i) * Math.pow(1-t, n - 1 -i) *  Math.pow(t, i);
                newX += controlPoints.get(i).x * bPoly;
                newY += controlPoints.get(i).y * bPoly;
            }

            drawForm.add(new Pixel((int)Math.round(newX), (int)Math.round(newY)));
        }
        return drawForm;
    }
}
