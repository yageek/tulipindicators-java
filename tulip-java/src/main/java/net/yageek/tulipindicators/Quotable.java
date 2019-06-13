public interface Quotable {

  public default double getHigh() { return 0.0; }
  public default double getLow() { return 0.0; }
  public default double getOpen() { return 0.0; }
  public default double getClose() { return 0.0; }
  public default int getVolume() { return 0; }
}