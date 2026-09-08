package day11;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Device {
    private boolean visited = false;
    private int correctPaths = 0;
    private String id;
    private List<Device> connections;

    public Device(String id){
        this.id = id;
        connections = new ArrayList<>();
    }

    public void setVisited(boolean visited) {
        this.visited = visited;
    }

    public int getCorrectPaths() {
        if(visited){
            return correctPaths;
        }
        return 0;
    }

    public void setCorrectPaths(int correctPaths) {
        this.correctPaths = correctPaths;
    }

    public void addConnection(Device device){
        connections.add(device);
    }

    public List<Device> getConnections() {
        return connections;
    }

    public String getId() {
        return id;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this){
            return true;
        }
        
        if(!(obj instanceof Device)){
            return false;
        }

        Device d = (Device) obj;
        return this.id.equals(d.getId());
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.id);
    }

    @Override
    public String toString() {
        return id;
    }
}
