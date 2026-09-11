package day12;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import util.FileUtil;

public class ChristmasTreeFarm {
    private List<String> data;
    private List<Present> presents;

    public ChristmasTreeFarm(String path){
        presents = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        int index = 0;
        try{
           data = FileUtil.readAllLines(path); 
        }catch(IOException e){
            System.out.println(e.getMessage());
        }

        System.out.println(data);
        for(int i = 0; i < data.size(); i++){
            if(data.get(i).equals(index + ":")){
                sb.append(data.get(i + 1)).append(data.get(i + 2)).append(data.get(i + 3));
                presents.add(new Present(sb.toString()));
                sb.setLength(0);
                i+=3;
                index += 1;
            }
        }

        System.out.println(presents.toString());
    }

}
