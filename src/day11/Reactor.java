package day11;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import util.FileUtil;

public class Reactor {
  private Map<String, Device> devices;
  private Device startingDevice;
  private List<String> data;
  private static final String GOAL_STRING = "out";
  private static int count = 0;

  public Reactor(String dataPath) {
    try {
      data = FileUtil.readAllLines(dataPath);
    } catch (IOException e) {
      System.out.println(e);
    }

    initDevices();
  }

  private void initDevices() {
    devices = new HashMap<>();

    for (String info : data) {
      String currentId = info.split(":")[0];
      Device device = devices.computeIfAbsent(currentId, id -> new Device(id));
      String[] connections = info.split(" ");

      for (int i = 1; i < connections.length; i++) {
        String targetId = connections[i];
        Device connectedDevice = devices.computeIfAbsent(targetId, id -> new Device(id));
        device.addConnection(connectedDevice);
      }

      if (device.getId().equals("you")) {
        startingDevice = device;
      }
    }
  }

  public long solve() {
    dfs(startingDevice);
    return count;
  }

  private void dfs(Device current) {
    String currentId = current.getId();

    if(currentId.equals(GOAL_STRING)){
      count++;
      return;
    }

    for (Device conn : current.getConnections()) {
        dfs(conn);
    }
  }
}
