
package net.yageek.tulipindicators;

/**
 * API around tulip
 */
public class Tulip {
  /**
   * Simple moving average
   * @param inputs The inputs
   * @param period The period to compute
   */
  public static Bindings.Response sma(double[] inputs, int period) {
    return Bindings.shared().callIndicator("sma", inputs,
                                           new double[] {period});
  }

  /**
   * Weighted moving average
   * @param inputs The inputs
   * @param period The period to compute
   */
  public static Bindings.Response wma(double[] inputs, int period) {
    return Bindings.shared().callIndicator("wma", inputs,
                                           new double[] {period});
  }

  /**
   * Exponential moving average
   * @param inputs The inputs
   * @param period The period to compute
   */
  public static Bindings.Response ema(double[] inputs, int period) {
    return Bindings.shared().callIndicator("wma", inputs,
                                           new double[] {period});
  }

  
}