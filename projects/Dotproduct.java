import java.util.Locale;
import java.util.Random;

public final class Dotproduct {
    private static final int[] SIZES = new int[] {10, 100, 1_000, 10_000, 100_000, 1_000_000};

    private static volatile long checksumInt = 0;
    private static volatile double checksumFp = 0.0;

    private static int repsForN(int n) {
        // Mirror the C-side policy: target ~20M multiply-adds.
        long targetOps = 20_000_000L;
        long reps = targetOps / Math.max(1, n);
        if (reps < 3) reps = 3;
        if (reps > 2_000_000L) reps = 2_000_000L;
        return (int) reps;
    }

    private static void printHeader() {
        System.out.println("lang,type,N,reps,total_ns,avg_ns,checksum");
    }

    private static void fill(byte[] a, byte[] b, int n, long seed) {
        Random r = new Random(seed);
        for (int i = 0; i < n; i++) {
            // Small range [-15, 15].
            a[i] = (byte) (r.nextInt(31) - 15);
            b[i] = (byte) (r.nextInt(31) - 15);
        }
    }

    private static void fill(short[] a, short[] b, int n, long seed) {
        Random r = new Random(seed);
        for (int i = 0; i < n; i++) {
            a[i] = (short) (r.nextInt(2001) - 1000);
            b[i] = (short) (r.nextInt(2001) - 1000);
        }
    }

    private static void fill(int[] a, int[] b, int n, long seed) {
        Random r = new Random(seed);
        for (int i = 0; i < n; i++) {
            a[i] = r.nextInt(2_000_001) - 1_000_000;
            b[i] = r.nextInt(2_000_001) - 1_000_000;
        }
    }

    private static void fill(float[] a, float[] b, int n, long seed) {
        Random r = new Random(seed);
        for (int i = 0; i < n; i++) {
            // Roughly [-1, 1).
            a[i] = (float) (r.nextDouble() * 2.0 - 1.0);
            b[i] = (float) (r.nextDouble() * 2.0 - 1.0);
        }
    }

    private static void fill(double[] a, double[] b, int n, long seed) {
        Random r = new Random(seed);
        for (int i = 0; i < n; i++) {
            a[i] = r.nextDouble() * 2.0 - 1.0;
            b[i] = r.nextDouble() * 2.0 - 1.0;
        }
    }

    private static long dotOnce(byte[] a, byte[] b, int n) {
        long acc = 0;
        for (int i = 0; i < n; i++) acc += (long) a[i] * (long) b[i];
        return acc;
    }

    private static long dotOnce(short[] a, short[] b, int n) {
        long acc = 0;
        for (int i = 0; i < n; i++) acc += (long) a[i] * (long) b[i];
        return acc;
    }

    private static long dotOnce(int[] a, int[] b, int n) {
        long acc = 0;
        for (int i = 0; i < n; i++) acc += (long) a[i] * (long) b[i];
        return acc;
    }

    private static double dotOnce(float[] a, float[] b, int n) {
        double acc = 0.0;
        for (int i = 0; i < n; i++) acc += (double) a[i] * (double) b[i];
        return acc;
    }

    private static double dotOnce(double[] a, double[] b, int n) {
        double acc = 0.0;
        for (int i = 0; i < n; i++) acc += a[i] * b[i];
        return acc;
    }

    private static void warmupByte() {
        int n = 100_000;
        byte[] a = new byte[n];
        byte[] b = new byte[n];
        fill(a, b, n, 0xC0FFEE + n);
        for (int i = 0; i < 10; i++) checksumInt += dotOnce(a, b, n);
    }

    private static void warmupShort() {
        int n = 100_000;
        short[] a = new short[n];
        short[] b = new short[n];
        fill(a, b, n, 0xBADC0DE + n);
        for (int i = 0; i < 10; i++) checksumInt += dotOnce(a, b, n);
    }

    private static void warmupInt() {
        int n = 100_000;
        int[] a = new int[n];
        int[] b = new int[n];
        fill(a, b, n, 0x12345678L + n);
        for (int i = 0; i < 10; i++) checksumInt += dotOnce(a, b, n);
    }

    private static void warmupFloat() {
        int n = 100_000;
        float[] a = new float[n];
        float[] b = new float[n];
        fill(a, b, n, 0x31415926L + n);
        for (int i = 0; i < 10; i++) checksumFp += dotOnce(a, b, n);
    }

    private static void warmupDouble() {
        int n = 100_000;
        double[] a = new double[n];
        double[] b = new double[n];
        fill(a, b, n, 0x27182818L + n);
        for (int i = 0; i < 10; i++) checksumFp += dotOnce(a, b, n);
    }

    private static void benchByte(int n) {
        byte[] a = new byte[n];
        byte[] b = new byte[n];
        fill(a, b, n, 0xC0FFEE + n);

        int reps = repsForN(n);
        long sum = 0;
        long t0 = System.nanoTime();
        for (int r = 0; r < reps; r++) sum += dotOnce(a, b, n);
        long t1 = System.nanoTime();

        checksumInt += sum;
        long total = t1 - t0;
        double avg = (double) total / (double) reps;
        System.out.printf(Locale.ROOT, "Java,signed_char,%d,%d,%d,%.2f,%d%n",
                n, reps, total, avg, checksumInt);
    }

    private static void benchShort(int n) {
        short[] a = new short[n];
        short[] b = new short[n];
        fill(a, b, n, 0xBADC0DE + n);

        int reps = repsForN(n);
        long sum = 0;
        long t0 = System.nanoTime();
        for (int r = 0; r < reps; r++) sum += dotOnce(a, b, n);
        long t1 = System.nanoTime();

        checksumInt += sum;
        long total = t1 - t0;
        double avg = (double) total / (double) reps;
        System.out.printf(Locale.ROOT, "Java,short,%d,%d,%d,%.2f,%d%n",
                n, reps, total, avg, checksumInt);
    }

    private static void benchInt(int n) {
        int[] a = new int[n];
        int[] b = new int[n];
        fill(a, b, n, 0x12345678L + n);

        int reps = repsForN(n);
        long sum = 0;
        long t0 = System.nanoTime();
        for (int r = 0; r < reps; r++) sum += dotOnce(a, b, n);
        long t1 = System.nanoTime();

        checksumInt += sum;
        long total = t1 - t0;
        double avg = (double) total / (double) reps;
        System.out.printf(Locale.ROOT, "Java,int,%d,%d,%d,%.2f,%d%n",
                n, reps, total, avg, checksumInt);
    }

    private static void benchFloat(int n) {
        float[] a = new float[n];
        float[] b = new float[n];
        fill(a, b, n, 0x31415926L + n);

        int reps = repsForN(n);
        double sum = 0.0;
        long t0 = System.nanoTime();
        for (int r = 0; r < reps; r++) sum += dotOnce(a, b, n);
        long t1 = System.nanoTime();

        checksumFp += sum;
        long total = t1 - t0;
        double avg = (double) total / (double) reps;
        System.out.printf(Locale.ROOT, "Java,float,%d,%d,%d,%.2f,%.6f%n",
                n, reps, total, avg, checksumFp);
    }

    private static void benchDouble(int n) {
        double[] a = new double[n];
        double[] b = new double[n];
        fill(a, b, n, 0x27182818L + n);

        int reps = repsForN(n);
        double sum = 0.0;
        long t0 = System.nanoTime();
        for (int r = 0; r < reps; r++) sum += dotOnce(a, b, n);
        long t1 = System.nanoTime();

        checksumFp += sum;
        long total = t1 - t0;
        double avg = (double) total / (double) reps;
        System.out.printf(Locale.ROOT, "Java,double,%d,%d,%d,%.2f,%.6f%n",
                n, reps, total, avg, checksumFp);
    }

    public static void main(String[] args) {
        printHeader();

        // Warm-up to encourage JIT compilation before real measurements.
        warmupByte();
        warmupShort();
        warmupInt();
        warmupFloat();
        warmupDouble();

        for (int n : SIZES) benchByte(n);
        for (int n : SIZES) benchShort(n);
        for (int n : SIZES) benchInt(n);
        for (int n : SIZES) benchFloat(n);
        for (int n : SIZES) benchDouble(n);

        System.err.printf(Locale.ROOT, "checksum_int=%d checksum_fp=%.6f%n", checksumInt, checksumFp);
    }
}

