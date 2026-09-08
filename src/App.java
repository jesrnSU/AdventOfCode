import day10.Factory;
import day11.Reactor;
import day7.Laboratories1;
import day7.Laboratories2;
import day8.Playground1;
import day9.MovieTheater1;

public class App {
  public static void main(String[] args) throws Exception {
    Reactor reactor = new Reactor("src/day11/data.txt");
    System.out.println(reactor.solve());
  }
}
