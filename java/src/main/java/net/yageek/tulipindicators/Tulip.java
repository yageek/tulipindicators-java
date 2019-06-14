/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package net.yageek.tulipindicators;

public class Tulip {
  static {
    System.loadLibrary("tulipjni");
  }
  private native void loadIndicators();
  public native TulipRawResponse call_indicator(String name, double[] inputs,
                                                double[] options);
    Tulip() {
      loadIndicators();
    }

}

class TulipRawResponse {
  final double[] values;
  final int beginIndex;

  TulipRawResponse(int beginIndex, double[] values) {
    this.values = values;
    this.beginIndex = beginIndex;
  }
}