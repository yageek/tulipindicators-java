package net.yageek.tulipindicators;

import java.util.List;

public interface Quotable {
  public default double getHigh() { return 0.0; }
  public default double getLow() { return 0.0; }
  public default double getOpen() { return 0.0; }
  public default double getClose() { return 0.0; }
  public default int getVolume() { return 0; }
}

class Helper {
  static <T extends Quotable> double[] HLV(List<T> inputs) {
    double rawInputs[] = new double[values.size()*2];

    for (int i = 0; i<rawInputs.length; i++) {
      rawInputs[i] = inputs[i].high;
      rawInputs[i+inputs.length] = inputs[i].low;
    }
    return rawInputs;
  }
}