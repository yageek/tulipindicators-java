
package net.yageek.tulipindicators;

/**
 * API around tulip
 */
public class Tulip {
  /**
   * Simple moving average
   * @param inputs The inputs
   * @param period The Period
   */
  public static Bindings.Response sma(double[] inputs, int period) {
    return Bindings.shared().call_indicator("sma", inputs,
                                            new double[] {period});
  }
}