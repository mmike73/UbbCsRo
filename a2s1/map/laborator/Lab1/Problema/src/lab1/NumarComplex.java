package lab1;

public class NumarComplex {
    public float re, im;

    public NumarComplex(float real, float imaginar) {
        re = real;
        im = imaginar;
    }

    public NumarComplex adunare(NumarComplex b) {
        this.re = this.re + b.re;
        this.im = this.im + b.im;
        return new NumarComplex(this.re, this.im);
    }

    public NumarComplex scadere(NumarComplex b) {
        float real = this.re - b.re;
        float imaginary = this.im - b.im;
        return new NumarComplex(real, imaginary);
    }

    public NumarComplex inmultire(NumarComplex b) {
        // (a + bi) * (c + di) = a * c + a * di + c * bi + bi + di
        //                     = a * c - b * d + i * ( a * d + c * b );
        float real = this.re * b.re - this.im * b.im;
        float imaginary = this.re * b.im + b.re * this.im;
        this.re = real;
        this.im = imaginary;
        return new NumarComplex(real, imaginary);
    }

    public NumarComplex impartire(NumarComplex b) {
        // (a + bi) / (c + di) =
        float numitor = b.re * b.re + b.im * b.im; // c^2 + d^2
        float real = (this.re * b.re + this.im * b.im) / numitor;  // (a * c + b * d) / (c^2 + d^2)
        float imaginary = (this.im * b.re - this.re * b.im) / numitor;  // (b * c - a * d) / (c^2 + d^2)
        this.re = real;
        this.im = imaginary;
        return new NumarComplex(real, imaginary);
    }

    public NumarComplex conjugat() {
        this.im = -this.im;
        return new NumarComplex(this.re, this.im);
    }

    public String toString() {
        return "Rezultat: " + String.valueOf(re) + " + " + String.valueOf(im) + "i";
    }
}
