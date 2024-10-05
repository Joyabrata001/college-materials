package com.abhiroop.utils;

public class MatrixForm {
    private final double[][] matrix;

    public MatrixForm(double[][] matrix) {
        this.matrix = matrix;
    }

    public double[][] getMatrix() {
        return matrix;
    }

    /**
     * return first*this multiplication
     * @param first the first matrix
     * @return result of first*this
     */
    private MatrixForm revMultiply(MatrixForm first){
        var firstMatrix = first.getMatrix();

        int row1 = firstMatrix.length;
        int col1 = firstMatrix[0].length;

        int row2 = matrix.length;
        int col2 = matrix[0].length;


        if (row2 != col1) {
            throw new IllegalArgumentException("Matrix Multiplication not Possible");
        }

        var result = new double[row1][col2];

        for(var i = 0; i<row1;i++){
            for(var j = 0; j< col2; j++){
                result[i][j] = 0;
                for(var k = 0; k< row2; k++)
                    result[i][j] += firstMatrix[i][k] * matrix[k][j];
            }
        }

        return new MatrixForm(result);
    }

    private static MatrixForm getTranslationMatrix(double tx, double ty){
        return new MatrixForm(new double[][]   {
                                                {1,0,tx},
                                                {0,1,ty},
                                                {0,0,1}
                                            });
    }

    private static MatrixForm getRotationMatrix(double degree){
        return new MatrixForm(new double[][]   {
                {Math.cos(degree),-Math.sin(degree),0},
                {Math.sin(degree),Math.cos(degree),0},
                {0,0,1}
        });
    }

    private double avg(double[] arr){
        double sum = 0;

        for(var e: arr)
            sum += e;

        return sum/arr.length;
    }

    public MatrixForm rotateInPlace(double degree){
        degree = -degree * 180/Math.PI;
        var avgX = avg(matrix[0]);
        var avgY = avg(matrix[1]);

        return this
                .revMultiply(getTranslationMatrix(-avgX, -avgY))
                .revMultiply(getRotationMatrix(degree))
                .revMultiply(getTranslationMatrix(avgX, avgY));

    }

    public MatrixForm rotateInPlace(double degree, int xAnchor, int yAnchor){
        degree = -degree * 180/Math.PI;

        return this
                .revMultiply(getTranslationMatrix(-xAnchor, -yAnchor))
                .revMultiply(getRotationMatrix(degree))
                .revMultiply(getTranslationMatrix(xAnchor, yAnchor));

    }

    public MatrixForm translate(int tx, int ty){
        return this.revMultiply(getTranslationMatrix(tx, ty));
    }

    public DrawForm toDrawForm(){
        var drawForm = new DrawForm();
        for(int j = 0; j < matrix[0].length; j++){
            drawForm.add(
                    new Pixel(
                            (int)Math.round(matrix[0][j]),
                            (int)Math.round(matrix[1][j])
                    )
            );
        }
        return drawForm;
    }
}
