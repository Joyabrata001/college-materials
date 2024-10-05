package com.abhiroop.utils;

import java.awt.*;
import java.util.*;
import java.util.List;

public class DrawForm {
    private List<Pixel> pixelList;

    public DrawForm() {
        this.pixelList = new ArrayList<>();
    }

    public void add(Pixel pixel){
        pixelList.add(pixel);
    }

    public void draw(Graphics g, int xOrigin, int yOrigin, Color color){
        var temp = g.getColor();
        g.setColor(color);
        for(var pixel: pixelList)
            pixel.drawPoint(g, xOrigin, yOrigin);
        g.setColor(temp);
    }

    private static class PixelComparator implements Comparator<Pixel>{
        /**
         * Compares its two arguments for order.  Returns a negative integer,
         * zero, or a positive integer as the first argument is less than, equal
         * to, or greater than the second.<p>
         * <p>
         * The implementor must ensure that {@code sgn(compare(x, y)) ==
         * -sgn(compare(y, x))} for all {@code x} and {@code y}.  (This
         * implies that {@code compare(x, y)} must throw an exception if and only
         * if {@code compare(y, x)} throws an exception.)<p>
         * <p>
         * The implementor must also ensure that the relation is transitive:
         * {@code ((compare(x, y)>0) && (compare(y, z)>0))} implies
         * {@code compare(x, z)>0}.<p>
         * <p>
         * Finally, the implementor must ensure that {@code compare(x, y)==0}
         * implies that {@code sgn(compare(x, z))==sgn(compare(y, z))} for all
         * {@code z}.<p>
         * <p>
         * It is generally the case, but <i>not</i> strictly required that
         * {@code (compare(x, y)==0) == (x.equals(y))}.  Generally speaking,
         * any comparator that violates this condition should clearly indicate
         * this fact.  The recommended language is "Note: this comparator
         * imposes orderings that are inconsistent with equals."<p>
         * <p>
         * In the foregoing description, the notation
         * {@code sgn(}<i>expression</i>{@code )} designates the mathematical
         * <i>signum</i> function, which is defined to return one of {@code -1},
         * {@code 0}, or {@code 1} according to whether the value of
         * <i>expression</i> is negative, zero, or positive, respectively.
         *
         * @param o1 the first object to be compared.
         * @param o2 the second object to be compared.
         * @return a negative integer, zero, or a positive integer as the
         * first argument is less than, equal to, or greater than the
         * second.
         * @throws NullPointerException if an argument is null and this
         *                              comparator does not permit null arguments
         * @throws ClassCastException   if the arguments' types prevent them from
         *                              being compared by this comparator.
         */
        @Override
        public int compare(Pixel o1, Pixel o2) {
            if(o1.getY().equals(o2.getY()))
                return o1.getX().compareTo(o2.getX());

            return o1.getY().compareTo(o2.getY());
        }
    }

    public List<Pixel> getPixelList() {
        return pixelList;
    }

    /**
     * Not Perfect yet
     */
    public DrawForm generateFill(){
        pixelList.sort(new PixelComparator());

        var fillPoints = new DrawForm();

        int startIdx = 0;
        int endIdx = 0;

        while(startIdx < pixelList.size() - 1){
            while(endIdx < pixelList.size() - 1 && pixelList.get(endIdx + 1).getY().equals(pixelList.get(startIdx).getY()))
                endIdx++;

            var y = pixelList.get(startIdx).getY();
            for(var x = pixelList.get(startIdx).getX() + 1; x < pixelList.get(endIdx).getX(); x++)
                fillPoints.add(new Pixel(x, y));

            startIdx = endIdx + 1;
        }

        return fillPoints;
    }

    public MatrixForm toMatrix(){
        var res = new double[3][pixelList.size()];

        var row0 = new double[pixelList.size()];
        for(int i=0;i< pixelList.size();i++)
            row0[i] = pixelList.get(i).getX();
        res[0] = row0;

        var row1 = new double[pixelList.size()];
        for(int i=0;i< pixelList.size();i++)
            row1[i] = pixelList.get(i).getY();
        res[1] = row1;

        var row2 = new double[pixelList.size()];
        for(int i=0;i< pixelList.size();i++)
            row2[i] =1;
        res[2] = row2;

        return new MatrixForm(res);
    }

    public DrawForm append(DrawForm other){
        this.pixelList.addAll(other.getPixelList());

        return this;
    }
}
