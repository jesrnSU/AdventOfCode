package day12;

import java.util.Arrays;

public class Present {
    private boolean[] shape;

    public Present(String s){
       shape = new boolean[s.length()]; 
       convertToMatrix(s);
    }

    private void convertToMatrix(String s){
        int i = 0;
        for(char c : s.toCharArray()){
            if(c == '#'){
                shape[i++] = true;
            }else{
                shape[i++] = false;
            }
        }
    }

    @Override
    public String toString() {
        return Arrays.toString(shape);
    }
}
