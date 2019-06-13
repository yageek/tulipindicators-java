/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package net.yageek.tulipindicators;

public class Tulip {
  static {
    System.loadLibrary("tulipjni");
  }
  public native void loadIndicators();
  public native TulipRawResponse call_indicator(String name, double[] inputs,
                                                double[] options);
}

class TulipRawResponse {
  final double[] result;
  final int beginIdx;

  TulipRawResponse(double[] result, int beginIdx) {
    this.result = result;
    this.beginIdx = beginIdx;
  }
}
