package day11;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Device {

    private String id;
    private List<Device> connections;

    public Device(String id){
        this.id = id;
        connections = new ArrayList<>();
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
